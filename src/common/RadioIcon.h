#pragma once

#include <wx/taskbar.h>

class RadioIcon : public wxTaskBarIcon
{
public:
	wxMenu* CreatePopupMenu();
	void OnClickMenu(wxCommandEvent &event);
};
