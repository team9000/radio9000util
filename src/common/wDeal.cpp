#include "prec.h"
#include "wDeal.h"

wDeal::wDeal()
{
	siteid = 0;
	sitename = wxT("");
	sortid = 0;
	category = wxT("");
	deftrack = true;
	special1_name = wxT("");
	special2_name = wxT("");
	marathon_name = wxT("");

	dealid = wxT("");
	url = wxT("");
	url_buy = wxT("");

	title = wxT("");
	condition = wxT("");
	price = -1;
	percent = -1;
	marathon = false;
	special1 = false;
	special2 = false;
	image = wxT("");

	etaid = 0;
	eta = -1;
	eta_time = 0;

	popupnow = false;
	image_downloaded = false;
	image_downloading = false;
	image_dlattempts = 0;
	image_localfile = wxT("");
	flashtext = wxT("");
	flashexpire = 0;
	alarmon = false;
	refreshed = false;
}

wxString wDeal::PrettyPrice()
{
	if(price == -1) {
		return wxT("???");
	} else if(price == 0) {
		return wxT("FREE");
	}

	return wxString::Format(wxT("$%.02f"), price);
}

wxString wDeal::PrettyPercent()
{
	if(percent == 0.0) {
		return wxT("Sold Out");
	} else if(percent >= 0.0) {
		return wxString::Format(wxT("%.1f%%"), percent*100);
	} else if(percent == -2.0) {
		return wxT("Low Stock");
	} else {
		return wxT("In Stock");
	}
}

int wDeal::PrettyPercentPos()
{
	if(percent == 0.0) {
		return 0;
	} else if(percent >= 0.0) {
		return (int)(percent*1000);
	} else if(percent == -2.0) {
		return 80;
	} else {
		return 1000;
	}
}

wxString wDeal::PrettyETA()
{
	if(eta == -1)
	{
		return wxT("???");
	}

	long temp = eta-(wxGetUTCTime()-eta_time);
	if(temp < 0) {
		temp = 0;
	}
	int days, hours, minutes, seconds;
	days = temp/(60*60*24);
	temp -= days*(60*60*24);
	hours = temp/(60*60);
	temp -= hours*(60*60);
	minutes = temp/60;
	temp -= minutes*60;
	seconds = temp;

	if(days >= 1) {
		return wxString::Format(wxT("%dd %d:%02d:%02d"), days, hours, minutes, seconds);
	} else if(hours >= 1) {
		return wxString::Format(wxT("%d:%02d:%02d"), hours, minutes, seconds);
	} else {
		return wxString::Format(wxT("%d:%02d"), minutes, seconds);
	}
}