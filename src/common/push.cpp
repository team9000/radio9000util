#include "prec.h"
#include "push.h"
#include "wNetData.h"
#include "wPackHandler.h"

void* tPush::Entry()
{
/*	booster_num = 5;
	while(true)
	{
		// All our socket ops will fail if the thread is shutting down
		if(TestShutdown()) return 0;

		wxStopWatch iterationtime;

		DoPush();

		while(iterationtime.Time() < REFRESH_LOOP_SAFETYTIME)
		{
			SleepOrShutdown(100);
		}
	}
	*/

	push.Connect("uploads.team9000.net", 8084);
	while(true) {
		if(TestShutdown()) return 0;

		boolean hasError = push.HasError();

		push.Process();
		wxJSONValue data = push.ReadJson();
		if(data.IsValid()) {
			wxString command = data["command"].AsString();
			if(command == "welcome") {
				wxMessageBox("The server has sent you a welcome!");
			} else if(command == "message") {
				wxMessageBox("New message: "+data["data"].AsString());
			}
		}
		SleepOrShutdown(50);
	}

	return 0;
}

void tPush::OnShutdown()
{
	push.Stop();
}
/*
// returns true on server change
bool tPush::GetNetVars()
{
	wNetDataSafe data;

	bool changed = false;
	if(data->push_reset || data->push_host != host || data->push_port != port)
	{
		last_complete = 0;
		last_attempt = 0;
		changed = true;
	}

	host = data->push_host;
	port = data->push_port;
	speedlimit = data->push_speedlimit;
	// TODO: add timeouts?
//	stomp.SetTimeout(data->push_timeout[0], data->push_timeout[1], data->push_timeout[2]);
	return changed;
}

void tPush::DoPush()
{
	GetNetVars();
//	stomp.SetTimeout(30, 30, 30); // TODO

	// TOTO: Remove all this
	host = "surge.wootalyzer.com";
	port = 61613;
	speedlimit=10;

// TODO: push servers should run on port 443

	// are we READY for push?
	if(!(host != wxT("") && port != 0 && speedlimit != 0))
		return;
	// are we over the speed limit?
	bool booster = (booster_num != 0);
	if(!(booster || wxGetUTCTime() >= last_attempt + speedlimit))
		return;
	booster_num = wxMax(0, booster_num-1);

	last_attempt = wxGetUTCTime();

	WLOG(wxT("PUSH - Connecting to push system..."));

	stomp.Connect(host, port);
	stomp.Subscribe(1);
	if(stomp.HasError())
	{
		WLOG(wxT("PUSH - ERROR\n")+stomp.GetError()+wxT("\n"));
		return;
	} else {
		WLOG(wxT("PUSH - Connected"));
	}

//	wxGetApp().netmanager.SetPushConnected(true);

	wxString body;
	while(true)
	{
//		if(GetNetVars()) break; // TODO

		stomp.ReadMessage(&body);
		last_attempt = wxGetUTCTime();
		if(stomp.HasError())
		{
			WLOG(wxT("PUSH - ERROR\n")+stomp.GetError()+wxT("\n"));
			break;
		}

		wPackHandler::Get()->ProcessMessage(body);
//		wxGetApp().netmanager.SetLastFetch(wxGetUTCTime());

		last_complete = wxGetUTCTime();
	}

	WLOG(wxT("PUSH - Disconnected"));
//	wxGetApp().netmanager.SetPushConnected(false);
}
*/