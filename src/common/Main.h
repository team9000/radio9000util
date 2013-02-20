#pragma once
#include "RadioIcon.h"
#include "MainFrame.h"

class Main : public wxApp
{
public:
    bool OnInit();
	int OnExit();

	RadioIcon* tray;
	MainFrame* frame;

private:
	void onHotkey(wxKeyEvent& event);
};

DECLARE_APP(Main)
