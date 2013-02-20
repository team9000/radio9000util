#pragma once

#include "wDeal.h"

enum wLayout
{
	WLAYOUT_STANDARD,
	WLAYOUT_COMPACT,
	WLAYOUT_JUMBO
};

class FrameDeal : public wxPanel
{
public:
	FrameDeal(wxWindow* parent, int type);
	~FrameDeal();
	void OnScroll(wxMouseEvent &event);
	void OnClickView(wxCommandEvent &event);
	void OnClickCheckout(wxCommandEvent &event);
	void OnClickImage(wxMouseEvent &event);
	void OnClickChoice(wxCommandEvent &event);
	void OnClickPopup(wxCommandEvent &event);
	void OnTimerFlash(bool toggle);
	void SetDeal(wDeal* newdeal);
	wDeal* GetDeal();
	void OnDealChanged(wxCommandEvent &event);
	void OnDealListChanged(wxCommandEvent &event);
	void OnImageChanged(wxCommandEvent &event);
private:
	void RenderDeal();
	void SmartLabel(wxTextCtrl* area, wxString newstr);
	void RenderETA();
	void RenderImage(bool forceredraw = false);
	bool RenderImageHelper(wxString path);
	wDeal* selected;
	wxPanel* dealframe;

	wxString m_imagepath;
	wxStaticBitmap* m_image;
	wxTextCtrl* m_title;
	wxTextCtrl* m_price;
	wxTextCtrl* m_stock;
	wxTextCtrl* m_time;
	wxGauge* m_gauge;
	wxButton* m_view;
	wxButton* m_checkout;
	wxButton* m_stopalarm;
	wxComboCtrlButton* m_itemchoice;
	void DealDlgLink()
	{
		m_image = (wxStaticBitmap*)dealframe->FindWindow(ID_ITEMIMAGE);
		m_title = (wxTextCtrl*)dealframe->FindWindow(ID_ITEMTITLE);
		m_price = (wxTextCtrl*)dealframe->FindWindow(ID_ITEMPRICE);
		m_stock = (wxTextCtrl*)dealframe->FindWindow(ID_ITEMSTOCK);
		m_time = (wxTextCtrl*)dealframe->FindWindow(ID_ITEMTIME);
		m_gauge = (wxGauge*)dealframe->FindWindow(ID_ITEMGAUGE);
		m_view = (wxButton*)dealframe->FindWindow(ID_BUTVIEW);
		m_checkout = (wxButton*)dealframe->FindWindow(ID_BUTCHECKOUT);
		m_stopalarm = (wxButton*)dealframe->FindWindow(ID_BUTSTOP);
		m_itemchoice = (wxComboCtrlButton*)dealframe->FindWindow(ID_ITEMCHOICE);
		wxASSERT(m_image && m_title && m_price && m_stock && m_time && m_gauge && m_view && m_checkout && m_stopalarm && m_itemchoice);
	}

};
