#pragma once
#include <wx/combo.h>

class wxComboCtrlButton : public wxComboCtrl
{
public:
    wxComboCtrlButton(wxWindow *parent,
                        wxWindowID id = wxID_ANY,
                        const wxString& value = wxEmptyString,
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxDefaultSize,
                        long style = 0,
                        const wxValidator& validator = wxDefaultValidator,
                        const wxString& name = wxComboBoxNameStr)
        : wxComboCtrl()
    {
        Create(parent,id,value,
               pos,size,
               // Style flag wxCC_STD_BUTTON makes the button
               // behave more like a standard push button.
               style | wxCC_STD_BUTTON,
               validator,name);
    }

    virtual void OnButtonClick()
    {
		wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED, GetId());
		event.SetEventObject(this);
		ProcessCommand(event);
    }
    virtual void DoSetPopupControl(wxComboPopup* WXUNUSED(popup))
    {
    }
};
