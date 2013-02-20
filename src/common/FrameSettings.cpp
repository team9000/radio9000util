#include "prec.h"
#include "FrameSettings.h"
#include "FrameLog.h"
#include "guievents.h"

FrameSettings::FrameSettings(wxWindow* parent)
: FrameSettingsGui(parent)
{
	wEvents.Connect(wEVT_STATUS_CHANGED, wxCommandEventHandler(FrameSettings::OnStatusChange), NULL, this);
	RenderBox();

	single = this;
}

FrameSettings::~FrameSettings()
{
	wEvents.Disconnect(wEVT_STATUS_CHANGED, wxCommandEventHandler(FrameSettings::OnStatusChange), NULL, this);

	single = NULL;
}

FrameSettings* FrameSettings::single = NULL;
void FrameSettings::OpenSingle()
{
	if(!wxGetApp().mainwnd) return;
	if(!single)
		single = new FrameSettings(wxGetApp().mainwnd);
	single->Show();
	single->SetFocus();
}

void FrameSettings::OnViewLog( wxCommandEvent &event )
{
	FrameLog::Open();
}

void FrameSettings::OnStatusChange(wxCommandEvent &event)
{
	event.Skip();

	{
		// TODO
//		int status = wxGetApp().netmanager.GetStatus();
//		m_connStat->SetLabel(wxString::Format(wxT("%d"), status));
	}
}

void FrameSettings::RenderBox()
{
	m_checkXButMin->Enable(m_checkMinTray->IsChecked());
}
