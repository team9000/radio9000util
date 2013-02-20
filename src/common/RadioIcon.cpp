#include "prec.h"
#include "RadioIcon.h"
#include "version.h"
#include "Main.h"

wxMenu* RadioIcon::CreatePopupMenu()
{
	wxMenuItem* about = new wxMenuItem(NULL,3,wxString("Radio9000 Helper v")+APP_VERSION_STR);
	about->Enable(false);

	wxMenu* mnu = new wxMenu();
	mnu->Append(about);
	mnu->Append(2, "Play / Pause");
	mnu->AppendSeparator();
	mnu->Append(1, "Exit");
	mnu->Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(RadioIcon::OnClickMenu), NULL, this);
	return mnu;
}

void RadioIcon::OnClickMenu(wxCommandEvent &event)
{
	int id = event.GetId();
	if(id == 1)
		wxGetApp().ExitMainLoop();
	if(id == 2) {
		wxKeyEvent* event = new wxKeyEvent(wxEVT_HOTKEY);
		event->m_rawCode = VK_MEDIA_PLAY_PAUSE;
		wxGetApp().frame->GetEventHandler()->QueueEvent(event);
	}
}