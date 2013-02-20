#pragma once

#include "layout.h"

class FrameAbout : public FrameAboutGui
{
public:
	static FrameAbout* single;
	static void OpenSingle();

	FrameAbout( wxWindow* parent );
	~FrameAbout();
	void OnOK(wxCommandEvent& event);
	void OnWebsite(wxCommandEvent& event);

private:
	void hitlink(wxHtmlLinkEvent &event);
};
