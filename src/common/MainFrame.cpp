#include "prec.h"
#include "MainFrame.h"
#include "ProtoHTTP.h"
#include "Main.h"
#include <wx/notifmsg.h>

wxDEFINE_EVENT(EVT_META, wxCommandEvent);

void ProcessMetaData(MainFrame *frame, const char* meta) {
	if(!meta) return;
	while(true) {
		size_t len = strlen(meta);
		if(len == 0) break;

		wxString header = meta;
		meta += strlen(meta)+1;

		wxString search = "StreamTitle='";
		int start = header.Find(search);
		if(start == wxNOT_FOUND) continue;
		wxString title = header.SubString(search.Len(), header.Len()-3);
		
		wxCommandEvent* metaUpdate = new wxCommandEvent(EVT_META);
		metaUpdate->SetString(title);
		frame->GetEventHandler()->QueueEvent(metaUpdate);
	}
}
void CALLBACK MyMetaSyncProc(HSYNC handle, DWORD channel, DWORD data, void *user)
{
	if(!handle) return;
	MainFrame* frame = (MainFrame*)user;
	ProcessMetaData(frame, BASS_ChannelGetTags(handle, BASS_TAG_HTTP));
	ProcessMetaData(frame, BASS_ChannelGetTags(handle, BASS_TAG_ICY));
	ProcessMetaData(frame, BASS_ChannelGetTags(handle, BASS_TAG_META));
}

// frame constructor
MainFrame::MainFrame(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title)
{
	Connect(wxEVT_TIMER, wxTimerEventHandler(MainFrame::onTimer));
	Connect(wxEVT_HOTKEY, wxKeyEventHandler(MainFrame::onHotkey));
	Connect(EVT_META, wxCommandEventHandler(MainFrame::onMeta));

	for(int i = 0; i <= 9; i++) {
		RegisterHotKey(0, wxMOD_CONTROL, VK_NUMPAD0+i);
	}
	RegisterHotKey(0, 0, VK_MEDIA_PLAY_PAUSE);
	RegisterHotKey(0, 0, VK_MEDIA_STOP);
	RegisterHotKey(0, 0, VK_MEDIA_PREV_TRACK);
	RegisterHotKey(0, 0, VK_MEDIA_NEXT_TRACK);

	ding = BASS_StreamCreateFile(false, "ding.wav", 0, 0, NULL);
	BASS_ChannelSetAttribute(ding, BASS_ATTRIB_VOL, 0.2f);

	volume = 1;
	stream = NULL;
}

void MainFrame::onMeta(wxCommandEvent& event)
{
	wxString title = event.GetString();

	if(title != oldTitle) {
		oldTitle = title;
		wxGetApp().tray->ShowBalloon("Cloudsdale Radio", title);
	}
}

void MainFrame::onTimer(wxTimerEvent& event)
{
	MyMetaSyncProc(stream, 0, 0, this);
}

void MainFrame::onHotkey(wxKeyEvent& event)
{
	int modifiers = event.GetModifiers();
	int keyCode = event.GetRawKeyCode();

	if(modifiers == wxMOD_CONTROL) {

#define DEVELOPER 1

#ifndef DEVELOPER

		if(keyCode == VK_NUMPAD0) {
			wxGetApp().tray->ShowBalloon("Cloudsdale Radio", oldTitle);
			BASS_ChannelPlay(ding, true);
			return;
		}
		
#else
		
		
		BASS_ChannelPlay(ding, true);
		ProtoHTTP http;

		wxString url =
			"https://api.radio9000.net/?key=aaoe847gg4e3ag&do="
			+ProtoHTTP::URLEncode(wxString::Format("%d", keyCode-VK_NUMPAD0));

		wxString output;
		http.DownloadText(url, output);
		http.SetTimeout(2);
//		wxMessageBox(output, "Alert!");

		wxString body;
		wxString title = output.BeforeFirst('\n', &body);

		wxGetApp().tray->ShowBalloon(title, body);
#endif
	} else {
		switch(keyCode) {
		case VK_MEDIA_PLAY_PAUSE:
			if(stream) {
				BASS_ChannelStop(stream);
				BASS_StreamFree(stream);
				stream = NULL;
				oldTitle = "";
			} else {
				stream = BASS_StreamCreateURL("http://direct.radio9000.net/1/mlp-radio.mp3", 0, 0, NULL, NULL);
				BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
				BASS_ChannelPlay(stream, true);
				initTimer = new wxTimer(this);
				initTimer->Start(1.0);
			}
			break;

		case VK_MEDIA_STOP:
			BASS_ChannelStop(stream);
			BASS_StreamFree(stream);
			stream = NULL;
			oldTitle = "";
			break;

		case VK_MEDIA_NEXT_TRACK:
			volume += 0.1f;
			if(volume > 1) volume = 1;
			BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
			break;
		
		case VK_MEDIA_PREV_TRACK:
			volume -= 0.1f;
			if(volume < 0) volume = 0;
			BASS_ChannelSetAttribute(stream, BASS_ATTRIB_VOL, volume);
			break;
		}
	}
}
