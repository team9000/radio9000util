#pragma once

#include "SafeMutex.h"

class wDeal
{
public:

	wDeal();
	wxString PrettyPrice();
	wxString PrettyPercent();
	int PrettyPercentPos();
	wxString PrettyETA();

	int siteid;
	wxString sitename;
	double sortid;
	wxString category;
	bool deftrack;
	wxString marathon_name;
	wxString special1_name;
	wxString special2_name;

	wxString dealid;
	wxString url;
	wxString url_buy;

	wxString title;
	wxString condition;
	double price;
	double percent;
	bool marathon;
	bool special1;
	bool special2;
	wxString image;

	int etaid;
	int eta;
	long eta_time;

	bool popupnow;
	bool image_downloaded;
	bool image_downloading;
	int image_dlattempts;
	wxString image_localfile;
	wxString flashtext;
	long flashexpire;
	bool alarmon;
	bool refreshed;

private:
	SafeMutex lock; // used by dealmanager class ONLY
	friend class wDealSafe;
	friend class wDealStoreInternal;
};
