///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __layout__
#define __layout__

#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/statbmp.h>
#include <wx/textctrl.h>
#include <wx/gauge.h>
#include <wx/button.h>
#include "wxComboCtrlButton.h"
#include <wx/panel.h>
#include <wx/checkbox.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/radiobut.h>
#include <wx/checklst.h>
#include <wx/choice.h>
#include <wx/filepicker.h>
#include <wx/notebook.h>
#include <wx/imaglist.h>
#include <wx/html/htmlwin.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define ID_ITEMIMAGE 1000
#define ID_ITEMTITLE 1001
#define ID_ITEMPRICE 1002
#define ID_ITEMSTOCK 1003
#define ID_ITEMTIME 1004
#define ID_ITEMGAUGE 1005
#define ID_BUTVIEW 1006
#define ID_BUTCHECKOUT 1007
#define ID_BUTSTOP 1008
#define ID_ITEMCHOICE 1009

///////////////////////////////////////////////////////////////////////////////
/// Class FrameHolderGui
///////////////////////////////////////////////////////////////////////////////
class FrameHolderGui : public wxFrame 
{
	private:
	
	protected:
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnMenuHide( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuExit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuStandard( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuCompact( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuJumbo( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuTrackerAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuTrackerSubtract( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuSettings( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuAbout( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxBoxSizer* bSizer1;
		
		FrameHolderGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Wootalyzer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
		~FrameHolderGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class FrameDealStdGui
///////////////////////////////////////////////////////////////////////////////
class FrameDealStdGui : public wxPanel 
{
	private:
	
	protected:
		wxStaticBitmap* m_bitmap6;
		wxComboCtrlButton* m_itemlist;
	
	public:
		
		FrameDealStdGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 521,115 ), long style = wxTAB_TRAVERSAL );
		~FrameDealStdGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class FrameSettingsGui
///////////////////////////////////////////////////////////////////////////////
class FrameSettingsGui : public wxFrame 
{
	private:
	
	protected:
		wxNotebook* m_notebook3;
		wxPanel* m_panel1;
		wxCheckBox* m_checkMinTray;
		
		wxCheckBox* m_checkXButMin;
		wxCheckBox* m_checkAlwaysTop;
		wxCheckBox* m_checkStartWithWin;
		
		wxCheckBox* m_checkBox29;
		wxCheckBox* m_checkBox30;
		wxStaticText* m_staticText19;
		wxSpinCtrl* m_spinCtrl1;
		wxRadioButton* m_radioBtn1;
		wxRadioButton* m_radioBtn2;
		wxCheckBox* m_checkBox31;
		wxCheckBox* m_checkBox9;
		wxButton* m_button12;
		wxPanel* m_panel6;
		wxPanel* m_panel7;
		wxTextCtrl* m_connStat;
		wxTextCtrl* m_usersOnline;
		wxTextCtrl* m_networkCap;
		wxGauge* m_gauge2;
		
		wxButton* m_button15;
		
		wxButton* m_button13;
		wxButton* m_button14;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnViewLog( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		FrameSettingsGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Wootalyzer Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 686,443 ), long style = wxCAPTION|wxCLOSE_BOX|wxMINIMIZE_BOX|wxSYSTEM_MENU|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
		~FrameSettingsGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class FrameAboutGui
///////////////////////////////////////////////////////////////////////////////
class FrameAboutGui : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel10;
		
		wxStaticBitmap* m_bitmap3;
		wxStaticText* m_staticText13;
		wxStaticText* versionbox;
		
		wxHtmlWindow* aboutbox;
		
		wxButton* m_button81;
		wxButton* m_button8;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnWebsite( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOK( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		FrameAboutGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("About Wootalyzer"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 330,397 ), long style = wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
		~FrameAboutGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class FramePopupGui
///////////////////////////////////////////////////////////////////////////////
class FramePopupGui : public wxFrame 
{
	private:
	
	protected:
		wxPanel* m_panel8;
		wxStaticBitmap* m_bitmap6;
		wxPanel* m_panel9;
		wxStaticText* m_staticText17;
		wxStaticText* m_staticText16;
	
	public:
		
		FramePopupGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 280,108 ), long style = wxCAPTION|wxCLOSE_BOX|wxSYSTEM_MENU|wxCLIP_CHILDREN|wxTAB_TRAVERSAL );
		~FramePopupGui();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class FrameSettingsUpgraderGui
///////////////////////////////////////////////////////////////////////////////
class FrameSettingsUpgraderGui : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_panel7;
		wxPanel* m_panel8;
		wxStaticText* m_staticText13;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		
	
	public:
		
		FrameSettingsUpgraderGui( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 564,178 ), long style = 0 );
		~FrameSettingsUpgraderGui();
	
};

#endif //__layout__
