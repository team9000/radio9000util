#pragma once

wxDECLARE_EVENT(EVT_META, wxCommandEvent);

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);
	void onHotkey(wxKeyEvent& event);
	void onTimer(wxTimerEvent& event);
	void onMeta(wxCommandEvent& event);

private:
	HSTREAM ding;
	HSTREAM stream;
	float volume;
	wxTimer* initTimer;

	wxString oldTitle;
};
