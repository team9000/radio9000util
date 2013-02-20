///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "prec.h"

#include "layout.h"

///////////////////////////////////////////////////////////////////////////

FrameHolderGui::FrameHolderGui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxMenuBar* m_menubar1;
	m_menubar1 = new wxMenuBar( 0 );
	wxMenu* m_menu1;
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Hide") ) , wxT("Minimize this window"), wxITEM_NORMAL );
	m_menu1->Append( m_menuItem1 );
	
	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( m_menu1, wxID_EXIT, wxString( wxT("Exit") ) , wxT("Quit Wootalyzer"), wxITEM_NORMAL );
	m_menu1->Append( m_menuItem2 );
	
	m_menubar1->Append( m_menu1, wxT("File") ); 
	
	wxMenu* m_menu2;
	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Standard") ) , wxT("Switch to Standard Mode"), wxITEM_NORMAL );
	m_menu2->Append( m_menuItem3 );
	
	wxMenuItem* m_menuItem4;
	m_menuItem4 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Compact") ) , wxT("Switch to Compact Mode"), wxITEM_NORMAL );
	m_menu2->Append( m_menuItem4 );
	
	wxMenuItem* m_menuItem5;
	m_menuItem5 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Jumbo") ) , wxT("Switch to Jumbo Mode"), wxITEM_NORMAL );
	m_menu2->Append( m_menuItem5 );
	
	wxMenuItem* m_separator1;
	m_separator1 = m_menu2->AppendSeparator();
	
	wxMenuItem* m_menuItem7;
	m_menuItem7 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Add Tracker") ) , wxT("Add an Additional Tracker"), wxITEM_NORMAL );
	m_menu2->Append( m_menuItem7 );
	
	wxMenuItem* m_menuItem8;
	m_menuItem8 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Subtract Tracker") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem8 );
	
	wxMenuItem* m_separator2;
	m_separator2 = m_menu2->AppendSeparator();
	
	wxMenuItem* m_menuItem9;
	m_menuItem9 = new wxMenuItem( m_menu2, wxID_ANY, wxString( wxT("Temporarily Disable Popups") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu2->Append( m_menuItem9 );
	
	m_menubar1->Append( m_menu2, wxT("View") ); 
	
	wxMenu* m_menu3;
	m_menu3 = new wxMenu();
	wxMenuItem* m_menuItem10;
	m_menuItem10 = new wxMenuItem( m_menu3, wxID_PREFERENCES, wxString( wxT("Settings") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuItem10 );
	
	m_menubar1->Append( m_menu3, wxT("Tools") ); 
	
	wxMenu* m_menu4;
	m_menu4 = new wxMenu();
	wxMenuItem* m_menuItem12;
	m_menuItem12 = new wxMenuItem( m_menu4, wxID_ABOUT, wxString( wxT("About") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu4->Append( m_menuItem12 );
	
	wxMenuItem* m_menuItem11;
	m_menuItem11 = new wxMenuItem( m_menu4, wxID_ANY, wxString( wxT("Install Updates") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu4->Append( m_menuItem11 );
	m_menuItem11->Enable( false );
	
	m_menubar1->Append( m_menu4, wxT("Help") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrameHolderGui::OnClose ) );
	this->Connect( m_menuItem1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuHide ) );
	this->Connect( m_menuItem2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuExit ) );
	this->Connect( m_menuItem3->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuStandard ) );
	this->Connect( m_menuItem4->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuCompact ) );
	this->Connect( m_menuItem5->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuJumbo ) );
	this->Connect( m_menuItem7->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuTrackerAdd ) );
	this->Connect( m_menuItem8->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuTrackerSubtract ) );
	this->Connect( m_menuItem10->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuSettings ) );
	this->Connect( m_menuItem12->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuAbout ) );
}

FrameHolderGui::~FrameHolderGui()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrameHolderGui::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuHide ) );
	this->Disconnect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuExit ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuStandard ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuCompact ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuJumbo ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuTrackerAdd ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuTrackerSubtract ) );
	this->Disconnect( wxID_PREFERENCES, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuSettings ) );
	this->Disconnect( wxID_ABOUT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( FrameHolderGui::OnMenuAbout ) );
	
}

FrameDealStdGui::FrameDealStdGui( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	this->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	bSizer8->SetMinSize( wxSize( 130,-1 ) ); 
	m_bitmap6 = new wxStaticBitmap( this, ID_ITEMIMAGE, wxNullBitmap, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER );
	m_bitmap6->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	bSizer8->Add( m_bitmap6, 1, wxALL|wxEXPAND, 3 );
	
	bSizer29->Add( bSizer8, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	wxTextCtrl* m_itemtitle;
	m_itemtitle = new wxTextCtrl( this, ID_ITEMTITLE, wxT("TEST Test test"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	m_itemtitle->SetFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer9->Add( m_itemtitle, 1, wxALL|wxEXPAND, 3 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	wxTextCtrl* m_itemprice;
	m_itemprice = new wxTextCtrl( this, ID_ITEMPRICE, wxT("???"), wxDefaultPosition, wxSize( 0,0 ), wxTE_READONLY );
	m_itemprice->SetFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer10->Add( m_itemprice, 1, wxEXPAND|wxALL, 3 );
	
	wxTextCtrl* m_itemstock;
	m_itemstock = new wxTextCtrl( this, ID_ITEMSTOCK, wxT("???"), wxDefaultPosition, wxSize( 0,0 ), wxTE_READONLY );
	m_itemstock->SetFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer10->Add( m_itemstock, 1, wxALL|wxEXPAND, 3 );
	
	wxTextCtrl* m_itemeta;
	m_itemeta = new wxTextCtrl( this, ID_ITEMTIME, wxT("???"), wxDefaultPosition, wxSize( 0,0 ), wxTE_READONLY );
	m_itemeta->SetFont( wxFont( 12, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer10->Add( m_itemeta, 1, wxALL|wxEXPAND, 3 );
	
	wxGauge* m_itemgauge;
	m_itemgauge = new wxGauge( this, ID_ITEMGAUGE, 1000, wxDefaultPosition, wxSize( 125,20 ), wxGA_HORIZONTAL|wxGA_SMOOTH );
	bSizer10->Add( m_itemgauge, 0, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 3 );
	
	bSizer9->Add( bSizer10, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	wxButton* m_butview;
	m_butview = new wxButton( this, ID_BUTVIEW, wxT("View"), wxDefaultPosition, wxDefaultSize, 0 );
	m_butview->SetFont( wxFont( 10, 70, 90, 90, false, wxEmptyString ) );
	m_butview->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_butview->SetMinSize( wxSize( 0,0 ) );
	
	bSizer11->Add( m_butview, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 3 );
	
	wxButton* m_butcheckout;
	m_butcheckout = new wxButton( this, ID_BUTCHECKOUT, wxT("Checkout"), wxDefaultPosition, wxDefaultSize, 0 );
	m_butcheckout->SetFont( wxFont( 10, 70, 90, 90, false, wxEmptyString ) );
	m_butcheckout->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_butcheckout->SetMinSize( wxSize( 0,0 ) );
	
	bSizer11->Add( m_butcheckout, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 3 );
	
	wxButton* m_butstop;
	m_butstop = new wxButton( this, ID_BUTSTOP, wxT("Stop Alarm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_butstop->SetFont( wxFont( 10, 70, 90, 90, false, wxEmptyString ) );
	m_butstop->SetForegroundColour( wxColour( 0, 0, 0 ) );
	m_butstop->SetMinSize( wxSize( 0,0 ) );
	
	bSizer11->Add( m_butstop, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 3 );
	
	m_itemlist = new wxComboCtrlButton( this, ID_ITEMCHOICE, wxT("???"), wxDefaultPosition, wxSize( 125,-1 ), wxCB_READONLY|wxCC_STD_BUTTON );
	m_itemlist->SetFont( wxFont( 11, 70, 90, 90, false, wxEmptyString ) );
	
	bSizer11->Add( m_itemlist, 0, wxALIGN_CENTER_VERTICAL|wxALL, 3 );
	
	bSizer9->Add( bSizer11, 1, wxEXPAND, 5 );
	
	bSizer29->Add( bSizer9, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer29 );
	this->Layout();
}

FrameDealStdGui::~FrameDealStdGui()
{
}

FrameSettingsGui::FrameSettingsGui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	wxPanel* m_panel61;
	m_panel61 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer251;
	bSizer251 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook3 = new wxNotebook( m_panel61, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNB_FIXEDWIDTH );
	wxSize m_notebook3ImageSize = wxSize( 30,30 );
	int m_notebook3Index = 0;
	wxImageList* m_notebook3Images = new wxImageList( m_notebook3ImageSize.GetWidth(), m_notebook3ImageSize.GetHeight() );
	m_notebook3->AssignImageList( m_notebook3Images );
	wxBitmap m_notebook3Bitmap;
	wxImage m_notebook3Image;
	m_panel1 = new wxPanel( m_notebook3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("System Options") ), wxVERTICAL );
	
	m_checkMinTray = new wxCheckBox( m_panel1, wxID_ANY, wxT("Minimize to Tray"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_checkMinTray, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer191;
	bSizer191 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer191->Add( 20, 0, 0, 0, 5 );
	
	m_checkXButMin = new wxCheckBox( m_panel1, wxID_ANY, wxT("X Button Minimizes"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	bSizer191->Add( m_checkXButMin, 0, wxALL, 5 );
	
	sbSizer5->Add( bSizer191, 1, wxEXPAND, 5 );
	
	m_checkAlwaysTop = new wxCheckBox( m_panel1, wxID_ANY, wxT("Always on Top"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_checkAlwaysTop, 0, wxALL, 5 );
	
	m_checkStartWithWin = new wxCheckBox( m_panel1, wxID_ANY, wxT("Start with Windows"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_checkStartWithWin, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer201;
	bSizer201 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer201->Add( 20, 0, 0, 0, 5 );
	
	m_checkBox29 = new wxCheckBox( m_panel1, wxID_ANY, wxT("Minimized"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer201->Add( m_checkBox29, 0, wxALL, 5 );
	
	sbSizer5->Add( bSizer201, 1, wxEXPAND, 5 );
	
	m_checkBox30 = new wxCheckBox( m_panel1, wxID_ANY, wxT("Portable Mode (Store Settings in Program Directory)"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer5->Add( m_checkBox30, 0, wxALL, 5 );
	
	bSizer21->Add( sbSizer5, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Frontend") ), wxVERTICAL );
	
	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText19 = new wxStaticText( m_panel1, wxID_ANY, wxT("Popup Duration (Seconds)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	bSizer18->Add( m_staticText19, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrl1 = new wxSpinCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), wxSP_ARROW_KEYS, 0, 30, 0 );
	bSizer18->Add( m_spinCtrl1, 0, wxALL, 5 );
	
	sbSizer6->Add( bSizer18, 1, wxEXPAND, 5 );
	
	bSizer21->Add( sbSizer6, 0, wxALL|wxEXPAND, 5 );
	
	bSizer14->Add( bSizer21, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer91;
	sbSizer91 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Software Updates") ), wxVERTICAL );
	
	m_radioBtn1 = new wxRadioButton( m_panel1, wxID_ANY, wxT("Automatically install new updates"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	sbSizer91->Add( m_radioBtn1, 0, wxALL, 5 );
	
	m_radioBtn2 = new wxRadioButton( m_panel1, wxID_ANY, wxT("Let me choose when to install updates"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer91->Add( m_radioBtn2, 0, wxALL, 5 );
	
	m_checkBox31 = new wxCheckBox( m_panel1, wxID_ANY, wxT("Download Beta Updates (May be Unstable)"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer91->Add( m_checkBox31, 0, wxALL, 5 );
	
	bSizer32->Add( sbSizer91, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer81;
	sbSizer81 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Troubleshooting") ), wxVERTICAL );
	
	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBox9 = new wxCheckBox( m_panel1, wxID_ANY, wxT("Enable Debug Logging"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer33->Add( m_checkBox9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button12 = new wxButton( m_panel1, wxID_ANY, wxT("View Log"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer33->Add( m_button12, 0, wxALL, 5 );
	
	sbSizer81->Add( bSizer33, 1, wxEXPAND, 5 );
	
	bSizer32->Add( sbSizer81, 0, wxEXPAND, 5 );
	
	bSizer14->Add( bSizer32, 1, wxEXPAND, 5 );
	
	m_panel1->SetSizer( bSizer14 );
	m_panel1->Layout();
	bSizer14->Fit( m_panel1 );
	m_notebook3->AddPage( m_panel1, wxT("Interface"), true );
	m_notebook3Bitmap = wxBitmap( wxT("images/interface.png"), wxBITMAP_TYPE_ANY );
	if ( m_notebook3Bitmap.Ok() )
	{
		m_notebook3Image = m_notebook3Bitmap.ConvertToImage();
		m_notebook3Images->Add( m_notebook3Image.Scale( m_notebook3ImageSize.GetWidth(), m_notebook3ImageSize.GetHeight() ) );
		m_notebook3->SetPageImage( m_notebook3Index, m_notebook3Index );
		m_notebook3Index++;
	}
	m_panel6 = new wxPanel( m_notebook3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticText* m_staticText1;
	m_staticText1 = new wxStaticText( m_panel6, wxID_ANY, wxT("Select which sounds are enabled"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer25->Add( m_staticText1, 0, wxALL, 5 );
	
	wxCheckListBox* m_checkList2;
	wxString m_checkList2Choices[] = { wxT("New Item Alert"), wxT("Low Stock Alarm"), wxT("New Item Popup"), wxT("Software Update Popup") };
	int m_checkList2NChoices = sizeof( m_checkList2Choices ) / sizeof( wxString );
	m_checkList2 = new wxCheckListBox( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_checkList2NChoices, m_checkList2Choices, 0 );
	bSizer25->Add( m_checkList2, 0, wxALL, 5 );
	
	bSizer24->Add( bSizer25, 0, 0, 5 );
	
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );
	
	wxChoice* m_choice4;
	wxString m_choice4Choices[] = { wxT("Default Sound File"), wxT("Custom Sound File") };
	int m_choice4NChoices = sizeof( m_choice4Choices ) / sizeof( wxString );
	m_choice4 = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice4NChoices, m_choice4Choices, 0 );
	m_choice4->SetSelection( 0 );
	bSizer26->Add( m_choice4, 0, wxALL|wxEXPAND, 5 );
	
	wxFilePickerCtrl* m_filePicker1;
	m_filePicker1 = new wxFilePickerCtrl( m_panel6, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer26->Add( m_filePicker1, 0, wxALL, 5 );
	
	bSizer24->Add( bSizer26, 0, 0, 5 );
	
	m_panel6->SetSizer( bSizer24 );
	m_panel6->Layout();
	bSizer24->Fit( m_panel6 );
	m_notebook3->AddPage( m_panel6, wxT("Audio"), false );
	m_notebook3Bitmap = wxBitmap( wxT("images/audio.png"), wxBITMAP_TYPE_ANY );
	if ( m_notebook3Bitmap.Ok() )
	{
		m_notebook3Image = m_notebook3Bitmap.ConvertToImage();
		m_notebook3Images->Add( m_notebook3Image.Scale( m_notebook3ImageSize.GetWidth(), m_notebook3ImageSize.GetHeight() ) );
		m_notebook3->SetPageImage( m_notebook3Index, m_notebook3Index );
		m_notebook3Index++;
	}
	m_panel7 = new wxPanel( m_notebook3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( m_panel7, wxID_ANY, wxT("Network Options") ), wxVERTICAL );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticText* m_staticText10;
	m_staticText10 = new wxStaticText( m_panel7, wxID_ANY, wxT("Proxy Setup:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer17->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxChoice* m_choice41;
	wxString m_choice41Choices[] = { wxT("Use Internet Explorer Settings"), wxT("Disable Proxy Support"), wxT("Custom Proxy Settings") };
	int m_choice41NChoices = sizeof( m_choice41Choices ) / sizeof( wxString );
	m_choice41 = new wxChoice( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice41NChoices, m_choice41Choices, 0 );
	m_choice41->SetSelection( 0 );
	bSizer17->Add( m_choice41, 0, wxALL, 5 );
	
	sbSizer4->Add( bSizer17, 0, 0, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( m_panel7, wxID_ANY, wxT("Custom Proxy Config") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer2->AddGrowableCol( 1 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticText* m_staticText111;
	m_staticText111 = new wxStaticText( m_panel7, wxID_ANY, wxT("Server Host:Port"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	fgSizer2->Add( m_staticText111, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxTextCtrl* m_textCtrl5;
	m_textCtrl5 = new wxTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl5, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer2->Add( 0, 0, 0, 0, 5 );
	
	wxCheckBox* m_checkBox27;
	m_checkBox27 = new wxCheckBox( m_panel7, wxID_ANY, wxT("Use Authentication"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_checkBox27, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxStaticText* m_staticText121;
	m_staticText121 = new wxStaticText( m_panel7, wxID_ANY, wxT("Username"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText121->Wrap( -1 );
	fgSizer2->Add( m_staticText121, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxTextCtrl* m_textCtrl6;
	m_textCtrl6 = new wxTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl6, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticText* m_staticText131;
	m_staticText131 = new wxStaticText( m_panel7, wxID_ANY, wxT("Password"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText131->Wrap( -1 );
	fgSizer2->Add( m_staticText131, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxTextCtrl* m_textCtrl7;
	m_textCtrl7 = new wxTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer2->Add( m_textCtrl7, 0, wxALL|wxEXPAND, 5 );
	
	sbSizer8->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	sbSizer4->Add( sbSizer8, 0, wxEXPAND, 5 );
	
	bSizer15->Add( sbSizer4, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	wxStaticBoxSizer* sbSizer51;
	sbSizer51 = new wxStaticBoxSizer( new wxStaticBox( m_panel7, wxID_ANY, wxT("Connection Status") ), wxVERTICAL );
	
	m_connStat = new wxTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_connStat->Enable( false );
	
	sbSizer51->Add( m_connStat, 0, wxALL|wxEXPAND, 5 );
	
	bSizer16->Add( sbSizer51, 0, wxALL|wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer61;
	sbSizer61 = new wxStaticBoxSizer( new wxStaticBox( m_panel7, wxID_ANY, wxT("Wootalyzer Network Status") ), wxVERTICAL );
	
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 0, 2, 0, 0 );
	
	wxStaticText* m_staticText17;
	m_staticText17 = new wxStaticText( m_panel7, wxID_ANY, wxT("Users Online"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	gSizer2->Add( m_staticText17, 0, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticText* m_staticText18;
	m_staticText18 = new wxStaticText( m_panel7, wxID_ANY, wxT("Network Capacity"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	gSizer2->Add( m_staticText18, 0, wxALL|wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_usersOnline = new wxTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_usersOnline->Enable( false );
	
	gSizer2->Add( m_usersOnline, 0, wxALL, 5 );
	
	m_networkCap = new wxTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_networkCap->Enable( false );
	
	gSizer2->Add( m_networkCap, 0, wxALL, 5 );
	
	sbSizer61->Add( gSizer2, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	m_gauge2 = new wxGauge( m_panel7, wxID_ANY, 100, wxDefaultPosition, wxSize( -1,30 ), wxGA_HORIZONTAL|wxGA_SMOOTH );
	m_gauge2->SetValue( 80 ); 
	sbSizer61->Add( m_gauge2, 0, wxALL|wxEXPAND, 5 );
	
	bSizer16->Add( sbSizer61, 1, wxALL|wxEXPAND, 5 );
	
	bSizer15->Add( bSizer16, 1, wxEXPAND, 5 );
	
	m_panel7->SetSizer( bSizer15 );
	m_panel7->Layout();
	bSizer15->Fit( m_panel7 );
	m_notebook3->AddPage( m_panel7, wxT("Network"), false );
	m_notebook3Bitmap = wxBitmap( wxT("images/network.png"), wxBITMAP_TYPE_ANY );
	if ( m_notebook3Bitmap.Ok() )
	{
		m_notebook3Image = m_notebook3Bitmap.ConvertToImage();
		m_notebook3Images->Add( m_notebook3Image.Scale( m_notebook3ImageSize.GetWidth(), m_notebook3ImageSize.GetHeight() ) );
		m_notebook3->SetPageImage( m_notebook3Index, m_notebook3Index );
		m_notebook3Index++;
	}
	
	bSizer251->Add( m_notebook3, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	bSizer22->SetMinSize( wxSize( -1,40 ) ); 
	
	bSizer22->Add( 5, 0, 0, wxEXPAND, 5 );
	
	m_button15 = new wxButton( m_panel61, wxID_ANY, wxT("Reset Preferences"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( m_button15, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer22->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button13 = new wxButton( m_panel61, wxID_ANY, wxT("Save"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( m_button13, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button14 = new wxButton( m_panel61, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( m_button14, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer22->Add( 5, 0, 0, wxEXPAND, 5 );
	
	bSizer251->Add( bSizer22, 0, wxEXPAND, 5 );
	
	m_panel61->SetSizer( bSizer251 );
	m_panel61->Layout();
	bSizer251->Fit( m_panel61 );
	bSizer10->Add( m_panel61, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer10 );
	this->Layout();
	
	// Connect Events
	m_button12->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrameSettingsGui::OnViewLog ), NULL, this );
}

FrameSettingsGui::~FrameSettingsGui()
{
	// Disconnect Events
	m_button12->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrameSettingsGui::OnViewLog ), NULL, this );
	
}

FrameAboutGui::FrameAboutGui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );
	
	m_panel10 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel10->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	wxBoxSizer* bSizer43;
	bSizer43 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer261;
	bSizer261 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer261->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_bitmap3 = new wxStaticBitmap( m_panel10, wxID_ANY, wxBitmap( wxT("images/wootabout.png"), wxBITMAP_TYPE_ANY ), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer261->Add( m_bitmap3, 0, wxALIGN_CENTER_HORIZONTAL|wxTOP, 10 );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText13 = new wxStaticText( m_panel10, wxID_ANY, wxT("Wootalyzer"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	m_staticText13->SetFont( wxFont( 24, 70, 90, 92, false, wxEmptyString ) );
	m_staticText13->SetForegroundColour( wxColour( 255, 255, 255 ) );
	
	bSizer27->Add( m_staticText13, 0, wxTOP, 15 );
	
	versionbox = new wxStaticText( m_panel10, wxID_ANY, wxT("Version ????"), wxDefaultPosition, wxDefaultSize, 0 );
	versionbox->Wrap( -1 );
	versionbox->SetFont( wxFont( 10, 70, 90, 90, false, wxEmptyString ) );
	versionbox->SetForegroundColour( wxColour( 158, 158, 158 ) );
	
	bSizer27->Add( versionbox, 0, 0, 5 );
	
	bSizer261->Add( bSizer27, 0, wxEXPAND, 5 );
	
	
	bSizer261->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizer43->Add( bSizer261, 0, wxEXPAND, 5 );
	
	aboutbox = new wxHtmlWindow( m_panel10, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_NO_SELECTION|wxHW_SCROLLBAR_AUTO );
	aboutbox->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	bSizer43->Add( aboutbox, 1, wxEXPAND|wxALL, 5 );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer31->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button81 = new wxButton( m_panel10, wxID_ANY, wxT("Visit Website"), wxDefaultPosition, wxSize( -1,30 ), 0 );
	m_button81->SetForegroundColour( wxColour( 0, 0, 0 ) );
	
	bSizer31->Add( m_button81, 0, wxALL, 5 );
	
	m_button8 = new wxButton( m_panel10, wxID_ANY, wxT("OK"), wxDefaultPosition, wxSize( -1,30 ), 0 );
	m_button8->SetForegroundColour( wxColour( 0, 0, 0 ) );
	
	bSizer31->Add( m_button8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer31->Add( 0, 0, 1, wxEXPAND, 5 );
	
	bSizer43->Add( bSizer31, 0, wxEXPAND, 5 );
	
	m_panel10->SetSizer( bSizer43 );
	m_panel10->Layout();
	bSizer43->Fit( m_panel10 );
	bSizer40->Add( m_panel10, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer40 );
	this->Layout();
	
	// Connect Events
	m_button81->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrameAboutGui::OnWebsite ), NULL, this );
	m_button8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrameAboutGui::OnOK ), NULL, this );
}

FrameAboutGui::~FrameAboutGui()
{
	// Disconnect Events
	m_button81->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrameAboutGui::OnWebsite ), NULL, this );
	m_button8->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FrameAboutGui::OnOK ), NULL, this );
	
}

FramePopupGui::FramePopupGui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxVERTICAL );
	
	m_panel8 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );
	
	m_bitmap6 = new wxStaticBitmap( m_panel8, ID_ITEMIMAGE, wxNullBitmap, wxDefaultPosition, wxSize( 80,80 ), wxSIMPLE_BORDER );
	bSizer28->Add( m_bitmap6, 0, 0, 5 );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxVERTICAL );
	
	m_panel9 = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText17 = new wxStaticText( m_panel9, wxID_ANY, wxT("dh ghsd fgs dfg sdf ghsdfhgs fdghs dfg hsd fhs dfgh sdf hsd fh sd fhsa sdf asasdf asdf asdf asdfdf sad fas dfdfghsd fh sdf hsd fhs dfgh "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( 180 );
	bSizer34->Add( m_staticText17, 1, wxALL|wxEXPAND, 5 );
	
	m_panel9->SetSizer( bSizer34 );
	m_panel9->Layout();
	bSizer34->Fit( m_panel9 );
	bSizer29->Add( m_panel9, 1, wxEXPAND, 5 );
	
	m_staticText16 = new wxStaticText( m_panel8, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	bSizer29->Add( m_staticText16, 0, wxALL, 5 );
	
	bSizer28->Add( bSizer29, 1, wxEXPAND, 5 );
	
	bSizer30->Add( bSizer28, 1, wxEXPAND, 5 );
	
	m_panel8->SetSizer( bSizer30 );
	m_panel8->Layout();
	bSizer30->Fit( m_panel8 );
	bSizer32->Add( m_panel8, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer32 );
	this->Layout();
}

FramePopupGui::~FramePopupGui()
{
}

FrameSettingsUpgraderGui::FrameSettingsUpgraderGui( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxVERTICAL );
	
	m_panel7 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel7->SetBackgroundColour( wxColour( 255, 6, 13 ) );
	
	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxVERTICAL );
	
	m_panel8 = new wxPanel( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel8->SetBackgroundColour( wxColour( 0, 0, 0 ) );
	
	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText13 = new wxStaticText( m_panel8, wxID_ANY, wxT("Please wait while Wootalyzer transfers your settings to the new version..."), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText13->Wrap( -1 );
	m_staticText13->SetFont( wxFont( 30, 70, 90, 90, false, wxEmptyString ) );
	m_staticText13->SetForegroundColour( wxColour( 255, 255, 255 ) );
	
	bSizer33->Add( m_staticText13, 1, wxALL|wxEXPAND, 5 );
	
	m_panel8->SetSizer( bSizer33 );
	m_panel8->Layout();
	bSizer33->Fit( m_panel8 );
	bSizer36->Add( m_panel8, 1, wxALL|wxEXPAND, 5 );
	
	m_panel7->SetSizer( bSizer36 );
	m_panel7->Layout();
	bSizer36->Fit( m_panel7 );
	bSizer32->Add( m_panel7, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer32 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrameSettingsUpgraderGui::OnClose ) );
}

FrameSettingsUpgraderGui::~FrameSettingsUpgraderGui()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( FrameSettingsUpgraderGui::OnClose ) );
	
}
