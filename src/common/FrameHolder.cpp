#include "prec.h"
#include "FrameDeal.h"
#include "FrameHolder.h"
#include "FrameAbout.h"
#include "FrameSettings.h"

// todo: get rid of
#include "rickroll.h"

FrameHolder::FrameHolder(wxWindow* parent, wLayout type, int num)
: FrameHolderGui(parent)
{
#ifdef __WXMSW__
	SetIcon(wxICON(wicon));
#endif
//	SetTransparent(170);

	holder_type = type;
	holder_num = 0;
	for(int i = 0; i < MAX_HOLDER_DLGS; i++) {
		children[i] = NULL;
	}

	flashalternate = false;
	flashtimer.Connect(wxEVT_TIMER, wxTimerEventHandler(FrameHolder::OnTimerFlash), NULL, this);
	flashtimer.Start(500);

	ChangeLayout(type, num);
}

FrameHolder::~FrameHolder()
{
	wxGetApp().ExitMainLoop();
}

void FrameHolder::ChangeLayout(wLayout type, int num)
{
	if(num > MAX_DEALPANES)
		num = MAX_DEALPANES;
	if(num < 1)
		num = 1;

	if(holder_num == num && holder_type == type)
		return;

	for(int i = 0; i < MAX_HOLDER_DLGS; i++) {
		wDeal* oldsite = NULL;
		if(i >= num || holder_type != type) {
			if(children[i] != NULL) {
				oldsite = children[i]->GetDeal();
				children[i]->Destroy();
				children[i] = NULL;
			}
		}
		if(i < num && children[i] == NULL) {
			children[i] = new FrameDeal(this, type);
			children[i]->SetDeal(oldsite);
			bSizer1->Add(children[i], 1, wxEXPAND);
		}
	}
	wxSize sizeofone = children[0]->GetSize();
	this->SetClientSize(sizeofone.x, sizeofone.y*num);
	
	holder_num = num;
	holder_type = type;
}


void FrameHolder::OnClose(wxCloseEvent& event)
{
	// TODO: calling this without closing windows causes the windows
	// to not close until the app terminates (which could be up to 5 seconds)
	// so we need to close all windows here
	this->Destroy(); // TODO: if this is the only window we're going to close, EVERY other window needs to be
	// a child of this window
}

void FrameHolder::OnTimerFlash(wxTimerEvent& event)
{
	flashalternate = !flashalternate;
	for(int i = 0; i < holder_num; i++) {
		children[i]->OnTimerFlash(flashalternate);
	}
}

void FrameHolder::OnMenuHide(wxCommandEvent& event)
{
	rickroll();
}

void FrameHolder::OnMenuExit(wxCommandEvent& event)
{
	Close();
}

void FrameHolder::OnMenuStandard(wxCommandEvent& event)
{
	ChangeLayout(WLAYOUT_STANDARD, holder_num);
}
void FrameHolder::OnMenuCompact(wxCommandEvent& event)
{
	ChangeLayout(WLAYOUT_COMPACT, holder_num);
}
void FrameHolder::OnMenuJumbo(wxCommandEvent& event)
{
	ChangeLayout(WLAYOUT_JUMBO, holder_num);
}
void FrameHolder::OnMenuTrackerAdd(wxCommandEvent& event)
{
	ChangeLayout(holder_type, holder_num+1);
}
void FrameHolder::OnMenuTrackerSubtract(wxCommandEvent& event)
{
	ChangeLayout(holder_type, holder_num-1);
}

void FrameHolder::OnMenuAbout(wxCommandEvent& event)
{
	FrameAbout::OpenSingle();
}

void FrameHolder::OnMenuSettings(wxCommandEvent& event)
{
	FrameSettings::OpenSingle();
}
