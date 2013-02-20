#pragma once

WX_DEFINE_ARRAY(wxJSONValue*, wxJSONValueArray);
WX_DECLARE_STRING_HASH_MAP(int, wxStringIntMap);

class wPackHandler {
public:
	~wPackHandler();
	void ProcessMessage(wxString pack);
	static wPackHandler* Get() { return &instance; };

private:
	static wPackHandler instance;

	SafeMutex processlock;
	wxStringIntMap sidcache;
	wxJSONValueArray backlog;

	void ProcessMessage(wxJSONValue& pack, bool frombacklog=false);
	void ProcessMessageNow(wxJSONValue& content, wxString type, wxString channel="", bool full=false);

	int GetLastSid(wxString channel) {
		if(sidcache.find(channel) == sidcache.end()) return -1;
		return sidcache[channel];
	}
	void SetLastSid(wxString channel, int sid) {
		sidcache[channel] = sid;
	}
	bool SanityCheck(wxJSONValue& pack) {
		if(!pack["content"].IsValid()) {
			WLOG("PACKAGE SANITY ERROR - Missing content"); return false;
		}
		if(!pack["type"].IsString()) {
			WLOG("PACKAGE SANITY ERROR - Missing type"); return false;
		}

		wxString type = pack["type"].AsString();
		if(type == "deal") {
			if(!pack["sid"].IsInt()) {
				WLOG("PACKAGE SANITY ERROR - Missing SID"); return false;
			}
			if(!pack["full"].IsBool()) {
				WLOG("PACKAGE SANITY ERROR - Missing full flag"); return false;
			}
		}
		if(pack["sid"].IsInt())
		{
			if(!pack["channel"].IsInt() && !pack["channel"].IsString()) {
				WLOG("PACKAGE SANITY ERROR - Missing channel"); return false;
			}
		}

		return true;
	}

	void CleanupBacklog();
	void ProcessBacklog();
	void AppendBacklog(wxJSONValue& package);
	void ProcessNet(wxJSONValue& pack, wxString name, int& target);
	void ProcessNet(wxJSONValue& pack, wxString name, wxString& target);
};
