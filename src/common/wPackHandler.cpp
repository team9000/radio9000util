#include "prec.h"
#include "wPackHandler.h"
#include "wNetData.h"

wPackHandler wPackHandler::instance;

wPackHandler::~wPackHandler()
{
	int count = backlog.Count();
	for(int i = 0; i < count; i++)
	{
		delete backlog[i];
	}
	backlog.Clear();
}

void wPackHandler::ProcessMessage(wxString pack)
{
	wxJSONValue root;
	wxJSONReader reader;
	int numErrors = reader.Parse(pack, &root);
	if(numErrors > 0) {
		WLOG(wxT("PACKAGE DROPPED - JSON is not well-formed\n")+pack+wxT("\n"));
		return;
	}

	// We don't want two packs being processed at the same time
	// from fetch and push (just in case), so lock here
	SafeMutexLocker locker(processlock);

	if(root.IsArray())
	{
		for(int i = 0; i < root.Size(); i++)
		{
			ProcessMessage(root[i]);
		}
	} else {
		ProcessMessage(root);
	}

	ProcessBacklog();
}

void wPackHandler::ProcessMessage(wxJSONValue& pack, bool frombacklog)
{
	// this should have already been checked, but just in case
	if(!SanityCheck(pack))
		return;

	wxString type = pack["type"].AsString();
	wxJSONValue content = pack["content"];
	WLOG(wxString::Format("Received Package type=%s", type));

	if(!pack["sid"].IsInt())
	{
		ProcessMessageNow(content, type);
		return;
	}

	wxString channel = pack["channel"].AsString();
	int sid = pack["sid"].AsInt();
	int lastsid = GetLastSid(channel);
	bool full = pack["full"].IsInt() && pack["full"].AsInt() != 0;

	WLOG(wxString::Format(wxT("Checking pack sequence channel=%d sid=%d lastsid=%d full=%d"), channel, sid, lastsid, full));

	if(sid <= lastsid)
	{
		// old pack :(
	} else if(full || sid == lastsid+1) {
		// next in sequence! (or, a full pack from the future)
		SetLastSid(channel, sid);
		ProcessMessageNow(content, type, channel, full);
	} else {
		// This package is in the future!
		if(!frombacklog)
		{
			AppendBacklog(pack);
			WLOG(wxT("Package Added to Backlog"));
		}
	}
}

void wPackHandler::ProcessMessageNow(wxJSONValue& content, wxString type, wxString channel, bool full)
{
	WLOG(wxString::Format("Processing Package type=%s channel=%s full=%d", type, channel, full));

	if(type == "net")
	{
		wNetDataSafe net;
		ProcessNet(content, wxT("fetch_timeout"), net->fetch_timeout);
		ProcessNet(content, wxT("fetch_speedlimit"), net->fetch_speedlimit);
		ProcessNet(content, wxT("fetch_url"), net->fetch_url);

		ProcessNet(content, wxT("push_timeout_c"), net->push_timeout[0]);
		ProcessNet(content, wxT("push_timeout_w"), net->push_timeout[1]);
		ProcessNet(content, wxT("push_timeout_r"), net->push_timeout[2]);
		ProcessNet(content, wxT("push_speedlimit"), net->push_speedlimit);
		ProcessNet(content, wxT("push_host"), net->push_host);
		ProcessNet(content, wxT("push_port"), net->push_port);
	} else {
		WLOG(wxT("PACKAGE DROPPED - Unhandled package type: ")+type);
	}
}

void wPackHandler::CleanupBacklog()
{
	long thetime = wxGetUTCTime();
	for(int i = 0; i < (int)backlog.Count(); i++)
	{
		wxJSONValue& pack = *backlog[i];

		int lastsid = GetLastSid(pack["channel"].AsString());
		if(pack["sid"].AsInt() <= lastsid) {
			delete backlog[i];
			backlog.RemoveAt(i);
			i--;
			continue;
		}

		long recvtime = pack["recvtime"].AsLong();
		if(thetime > recvtime + BACKLOG_EXPIRE)
		{
			delete backlog[i];
			backlog.RemoveAt(i);
			i--;
			continue;
		}
	}

	while(backlog.Count() > BACKLOG_MAX_SIZE)
	{
		delete backlog[0];
		backlog.RemoveAt(0);
	}
}

void wPackHandler::ProcessBacklog()
{
	for(int i = 0; i < (int)backlog.Count(); i++)
	{
		WLOG("Processing Backlog Package");
		ProcessMessage(*backlog[i], true);
	}
	CleanupBacklog();
}
void wPackHandler::AppendBacklog(wxJSONValue& package)
{
	wxJSONValue* backlogitem = new wxJSONValue(package);
	(*backlogitem)[wxT("recvtime")] = wxGetUTCTime();
	backlog.Add(backlogitem);
}

void wPackHandler::ProcessNet(wxJSONValue& pack, wxString name, int& target)
{
	if(pack[name].AsInt(target))
		WLOG(wxT("NET - Set ")+name);
}
void wPackHandler::ProcessNet(wxJSONValue& pack, wxString name, wxString& target)
{
	if(pack[name].AsString(target))
		WLOG(wxT("NET - Set ")+name);
}
