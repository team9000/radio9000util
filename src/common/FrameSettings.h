#pragma once

#include "layout.h"

class FrameSettings : public FrameSettingsGui
{
public:
	FrameSettings( wxWindow* parent );
	~FrameSettings();
	static FrameSettings* single;
	static void OpenSingle();

private:
	void RenderBox();

protected:
	void OnViewLog( wxCommandEvent &event );
	void OnStatusChange( wxCommandEvent &event );
};
