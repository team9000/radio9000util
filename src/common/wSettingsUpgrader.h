#pragma once

#include "layout.h"

class wSettingsUpgrader {
public:
	static int Upgrade();

private:
	static void Show();
	static void Close();
	static bool Prompt();
};

class FrameSettingsUpgrader : public FrameSettingsUpgraderGui
{
public:
	FrameSettingsUpgrader( wxWindow* parent );
	~FrameSettingsUpgrader();
	void OnClose(wxCloseEvent& event);
	void OnUpgradeDone(wxCommandEvent &event);
};
