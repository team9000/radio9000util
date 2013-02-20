#include "prec.h"
#include "FrameLog.h"

FrameLog::FrameLog(wxWindow* parent)
: wxLogWindow(parent, wxT("Debug Log"), false, false)
{
	GetFrame()->Move(20,20);
	GetFrame()->SetSize(600,700);

	single = this;
}

FrameLog::~FrameLog()
{
	single = NULL;
}

FrameLog* FrameLog::single = NULL;
void FrameLog::Start()
{
	if(!wxGetApp().mainwnd) return;
	if(!single)
		single = new FrameLog(wxGetApp().mainwnd);
	single->GetFrame()->Hide();
	wxLog::EnableLogging(true);
}
void FrameLog::Stop()
{
	wxLog::EnableLogging(false);
	if(!single) return;
	single->GetFrame()->Destroy();
	single = false;
}
void FrameLog::Open()
{
	if(!single) return;
	single->GetFrame()->Show();
	single->GetFrame()->SetFocus();
}