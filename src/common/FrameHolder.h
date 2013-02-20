#pragma once

#include "layout.h"
#include "FrameDeal.h"

class FrameHolder : public FrameHolderGui
{
public:
	FrameHolder(wxWindow* parent, wLayout type=WLAYOUT_STANDARD, int num=1);
	~FrameHolder();
	void ChangeLayout(wLayout type, int num);
	void OnClose(wxCloseEvent& event);
	void OnTimerFlash(wxTimerEvent& event);
	void OnMenuHide(wxCommandEvent& event);
	void OnMenuExit(wxCommandEvent& event);
	void OnMenuStandard(wxCommandEvent& event);
	void OnMenuCompact(wxCommandEvent& event);
	void OnMenuJumbo(wxCommandEvent& event);
	void OnMenuTrackerAdd(wxCommandEvent& event);
	void OnMenuTrackerSubtract(wxCommandEvent& event);
	void OnMenuAbout(wxCommandEvent& event);
	void OnMenuSettings(wxCommandEvent& event);
private:
	wLayout holder_type;
	int holder_num;
	FrameDeal* children[MAX_HOLDER_DLGS];
	wxTimer flashtimer;
	bool flashalternate;
};
