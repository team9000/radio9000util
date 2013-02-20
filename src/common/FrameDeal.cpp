#include "prec.h"
#include "FrameDeal.h"
#include "guievents.h"

FrameDeal::FrameDeal(wxWindow* parent, int type) : wxPanel(parent)
{
	wEvents.Connect(wEVT_DEAL_CHANGED, wxCommandEventHandler(FrameDeal::OnDealChanged), NULL, this);
	wEvents.Connect(wEVT_DEALLIST_CHANGED, wxCommandEventHandler(FrameDeal::OnDealListChanged), NULL, this);
	wEvents.Connect(wEVT_IMAGE_CHANGED, wxCommandEventHandler(FrameDeal::OnImageChanged), NULL, this);

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	if(type == WLAYOUT_STANDARD) {
		dealframe = new FrameDealStdGui(this);
	} else {
		dealframe = new FrameDealStdGui(this);
	}
	wxSize dealsize = dealframe->GetSize();
	sizer->Add(dealframe, 1, wxEXPAND);
	this->SetSizer(sizer);
	this->SetClientSize(dealframe->GetSize());

	DealDlgLink();

	// Put all hooks here!
	// They don't have to be disconnected
	// because the children will always be
	// killed first

	Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(FrameDeal::OnScroll));
	m_image->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(FrameDeal::OnClickImage), NULL, this);
	m_view->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameDeal::OnClickView), NULL, this);
	m_checkout->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameDeal::OnClickCheckout), NULL, this);
	m_itemchoice->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FrameDeal::OnClickChoice), NULL, this);

	RenderDeal();
}

FrameDeal::~FrameDeal()
{
	wEvents.Disconnect(wEVT_DEAL_CHANGED, wxCommandEventHandler(FrameDeal::OnDealChanged), NULL, this);
	wEvents.Disconnect(wEVT_DEALLIST_CHANGED, wxCommandEventHandler(FrameDeal::OnDealListChanged), NULL, this);
	wEvents.Disconnect(wEVT_IMAGE_CHANGED, wxCommandEventHandler(FrameDeal::OnImageChanged), NULL, this);
}

void FrameDeal::OnScroll(wxMouseEvent &event)
{
	int change = event.m_wheelRotation / event.m_wheelDelta;
	if(change == 0) return;
	if(wxGetApp().dealstore.Adjust(selected, (change > 0) ? wDEAL_ADJUST_DOWN : wDEAL_ADJUST_UP), wDEAL_REQUIRE_TRACKED)
		RenderDeal();
}

void FrameDeal::OnClickView(wxCommandEvent &event)
{
	wDealSafe dealsafe(selected);
	if(selected != NULL && selected->url != wxT(""))
	{
		wxLaunchDefaultBrowser(selected->url);
	}
}

void FrameDeal::OnClickCheckout(wxCommandEvent &event)
{
	wDealSafe dealsafe(selected);
	if(selected != NULL && selected->url_buy != wxT(""))
	{
		wxLaunchDefaultBrowser(selected->url_buy);
	}
}

void FrameDeal::OnClickImage(wxMouseEvent &event)
{
	wDealSafe dealsafe(selected);
	if(selected != NULL && selected->url != wxT(""))
	{
		wxLaunchDefaultBrowser(selected->url);
	}
}

// This gets called by parent
void FrameDeal::OnTimerFlash(bool toggle)
{
	if(toggle) {
//		dealframe->SetBackgroundColour(wxColour(255, 0, 0));
	} else {
//		dealframe->SetBackgroundColour(wxColour(255, 255, 0));
	}
//	this->Refresh();
	RenderETA();
}

void FrameDeal::SetDeal(wDeal* newdeal)
{
	if(selected == newdeal) return;
	selected = newdeal;
	RenderDeal();
}

wDeal* FrameDeal::GetDeal()
{
	return selected;
}

void FrameDeal::OnDealChanged(wxCommandEvent &event)
{
	event.Skip();

	if(selected == event.GetClientData())
		RenderDeal();
}

void FrameDeal::OnDealListChanged(wxCommandEvent &event)
{
	event.Skip();

	if(wxGetApp().dealstore.Adjust(selected, wDEAL_ADJUST_FIX, wDEAL_REQUIRE_TRACKED))
		RenderDeal();
}

void FrameDeal::OnImageChanged(wxCommandEvent &event)
{
	event.Skip();

	if(selected == event.GetClientData())
		RenderImage(true);
}

void FrameDeal::RenderDeal()
{
	wDealSafe dealsafe(selected, wDEAL_ADJUST_FIX, wDEAL_REQUIRE_TRACKED);

	if(selected != NULL)
	{
		SmartLabel(m_title, selected->title);
		SmartLabel(m_price, selected->PrettyPrice());
		SmartLabel(m_stock, selected->PrettyPercent());
		m_gauge->SetValue(selected->PrettyPercentPos());
		m_itemchoice->SetText(selected->sitename);
		if(selected->url == wxT(""))
			m_view->Disable();
		else
			m_view->Enable();
		if(selected->url_buy == wxT(""))
			m_checkout->Disable();
		else
			m_checkout->Enable();
	} else {
		SmartLabel(m_title, wxT("No Deal Selected"));
		SmartLabel(m_price, wxT(""));
		SmartLabel(m_stock, wxT(""));
		m_gauge->SetValue(0);
		m_itemchoice->SetText(wxT(""));
		m_view->Disable();
		m_checkout->Disable();
	}
	RenderETA();
	RenderImage();
}

void FrameDeal::SmartLabel(wxTextCtrl* area, wxString newstr)
{
	if(area->GetLabel() != newstr)
		area->SetLabel(newstr);
}
// TODO: no deal at this time deals are getting image url's of "http://"
void FrameDeal::RenderETA()
{
	wDealSafe dealsafe(selected);

	if(selected == NULL)
	{
		SmartLabel(m_time, wxT(""));
	} else {
		SmartLabel(m_time, selected->PrettyETA());
	}
}

void FrameDeal::RenderImage(bool forceredraw)
{
	wxString newpath = wxT(FILE_IMAGE_NOIMAGE);

	{
		wDealSafe dealsafe(selected);
		if(selected != NULL && selected->image_downloaded)
			newpath = selected->image_localfile;
	}

	if(newpath == m_imagepath && !forceredraw) return;
	m_imagepath = newpath;

	if(RenderImageHelper(newpath)) return;
	if(RenderImageHelper(wxT(FILE_IMAGE_NOIMAGE))) return;
	RenderImageHelper(wxT(""));
}

bool FrameDeal::RenderImageHelper(wxString path)
{
	// TODO: put this in a thread because it's slowwwww

	if(path == wxT("")) m_image->SetBitmap(wxNullBitmap);

	wxImage itemimage(path);
	if(!itemimage.Ok()) return false;

	wxSize boxsize = m_image->GetSize();
	wxSize imagesize;
	imagesize.SetWidth(itemimage.GetWidth());
	imagesize.SetHeight(itemimage.GetHeight());

	wxSize resizebox;
	if((double)boxsize.GetWidth()/boxsize.GetHeight() > (double)imagesize.GetWidth()/imagesize.GetHeight())
	{
		resizebox.SetHeight(boxsize.GetHeight());
		resizebox.SetWidth(resizebox.GetHeight() * imagesize.GetWidth() / imagesize.GetHeight());
	} else {
		resizebox.SetWidth(boxsize.GetWidth());
		resizebox.SetHeight(resizebox.GetWidth() * imagesize.GetHeight() / imagesize.GetWidth());
	}
	itemimage.Rescale(resizebox.x, resizebox.y, wxIMAGE_QUALITY_BILINEAR);
//	itemimage.Rescale(resizebox.x, resizebox.y);
	itemimage.Resize(boxsize, wxPoint((boxsize.x-resizebox.x)/2,(boxsize.y-resizebox.y)/2));

	wxBitmap itembitmap(itemimage);
	if(!itembitmap.Ok()) return false;
	m_image->SetBitmap(itembitmap);

	return true;
}

// TODO: find glitch from scrolling a lot

void FrameDeal::OnClickChoice(wxCommandEvent &event)
{
	wxMenu mnu;
	mnu.Append(1, "Do something", "HELP", wxITEM_RADIO);
	mnu.Append(2, "Do something else", "HELP", wxITEM_RADIO);
	mnu.Connect(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(FrameDeal::OnClickPopup), NULL, this);
	wxPoint menupos = m_itemchoice->GetPosition();
	menupos.y += m_itemchoice->GetSize().y;
	PopupMenu(&mnu, menupos);

	// TODO: remove test
	int displaycount = wxDisplay::GetCount();
	for(int i = 0; i < displaycount; i++) {
		wxDisplay display(i);
		wxRect res = display.GetGeometry();
		wxMessageBox(wxString::Format("%d %d %d %d", res.x, res.y, res.width, res.height));
	}
}

void FrameDeal::OnClickPopup(wxCommandEvent &event)
{

}
