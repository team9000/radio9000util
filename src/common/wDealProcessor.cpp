#include "prec.h"
#include "wDealProcessor.h"
#include "guievents.h"

bool wDealProcessor::ProcessPack(wxJSONValue& datapack)
{
	// TODO: put a mutex on this entire function just to be safe

	if(!datapack[wxT("deals")].IsArray()) return true;
	wxJSONValue newdealspack = datapack[wxT("deals")];

	wxString mode;
	if(!datapack[wxT("mode")].AsString(mode))
	{
		WLOG(wxT("No Deal Command Mode in packet!"));
		return true;
	}
	WLOG(wxT("Deal Command Mode: ")+mode);
	if(mode != wxT("update") && mode != wxT("full") && mode != wxT("add") && mode != wxT("remove"))
	{
		WLOG(wxT("Unhandled Deal Command Mode"));
		return true;
	}

	// TODO: deal dialogs should listen for the listchanged event and
	// check to see if their deal is still valid

	if(mode == wxT("full"))
	{
		wDealSetSafe dealSet;
		int count = dealSet->Count();
		for(int i = 0; i < count; i++)
		{
			wDealSafe deal(dealSet[i]);
			deal->refreshed = false;
		}
	}

	bool listchanged = false;
	wxJSONValue newdealjson;
	for(int i = 0; i < newdealspack.Size(); i++)
	{
		newdealjson = newdealspack[i];

		bool alert_newsite = false;
		bool alert_dealchanged = false;
		bool alert_newdeal = false;
		bool alert_lowstock = false;

		int siteid = 0;
		if(!newdealjson[wxT("site_id")].AsInt(siteid)) return true;
		WLOG(wxString::Format(wxT("Site ID: %d"), siteid));

		wDeal* target = NULL;
		{
			// Do set related stuffs
			wDealSetSafe dealSet;

			target = wxGetApp().dealstore.Lookup(siteid);
			if(target)
			{
				if(mode == wxT("remove"))
				{
					wxGetApp().dealstore.DeleteDeal(target);
					listchanged = true;
					continue;
				}
			} else {
				// Not Found
				if(mode == wxT("full") || mode == wxT("add"))
				{
					// TODO: EXTREMELY IMPORTANT! Move this into the processing loop, these deals need to be LOCKED
					// in between being created and added, or else other threads might see them empty!
					target = new wDeal();
					target->siteid = siteid;
					dealSet->Add(target);
					alert_newsite = true;
					listchanged = true;
				} else {
					WLOG(wxT("ERROR - New siteid during mode: ")+mode);
					return false;
				}
			}
		}

		if(mode == "remove") return true;

		{
			// wDealSafe will lock down the deal for us while we process the update
			wDealSafe dealsafe(target);
			if(target != dealsafe.GetData())
			{
				// Although deals may change, causing the dealsafe to return NULL,
				// it should NOT happen here, because this is the only class that can
				// change the deal set!
				WLOG(wxT("ERROR - UPDATE called on changed deal pack"));
				return false;
			}

			target->refreshed = true;

			listchanged |= JSONChangeParse(newdealjson[wxT("site_n")], target->sitename);
			listchanged |= JSONChangeParse(newdealjson[wxT("sort_id")], target->sortid);
			listchanged |= JSONChangeParse(newdealjson[wxT("cat")], target->category);
			listchanged |= JSONChangeParse(newdealjson[wxT("def")], target->deftrack);
			// TODO: is the |= going to optimize out our function calls?

			if(JSONChangeParse(newdealjson[wxT("deal_id")], target->dealid))
			{
				alert_dealchanged = true;
				alert_newdeal = true;
			}

			if(JSONChangeParse(newdealjson[wxT("eta_id")], target->etaid))
			{
				newdealjson[wxT("eta")].AsInt(target->eta);
				target->eta_time = wxGetUTCTime();
				alert_dealchanged = true;
			}

			double oldpercent = target->percent;
			if(JSONChangeParse(newdealjson[wxT("percent")], target->percent))
			{
				alert_dealchanged = true;
				if(oldpercent > 0.05 && target->percent <= 0.05 && target->percent > 0) {
					alert_lowstock = true;
				} else if(oldpercent != 0 && target->percent == 0) {
					alert_lowstock = true;
				}
			}

			if(JSONChangeParse(newdealjson[wxT("image")], target->image))
			{
				alert_dealchanged = true;

				target->image_downloaded = false;
				target->image_downloading = false;
				target->image_dlattempts = 0;

				wCallEvent(wEVT_IMAGE_CHANGED, target);
			}

			alert_dealchanged |= JSONChangeParse(newdealjson[wxT("url")], target->url);
			alert_dealchanged |= JSONChangeParse(newdealjson[wxT("url_buy")], target->url_buy);
			alert_dealchanged |= JSONChangeParse(newdealjson[wxT("title")], target->title);
			alert_dealchanged |= JSONChangeParse(newdealjson[wxT("condition")], target->condition);
			alert_dealchanged |= JSONChangeParse(newdealjson[wxT("price")], target->price);
			alert_dealchanged |= JSONChangeParse(newdealjson[wxT("m_n")], target->marathon_name);
			alert_dealchanged |= JSONChangeParse(newdealjson[wxT("s1_n")], target->special1_name);
			alert_dealchanged |= JSONChangeParse(newdealjson[wxT("s2_n")], target->special2_name);
			alert_dealchanged |= JSONChangeParse(newdealjson[wxT("m")], target->marathon);
			alert_dealchanged |= JSONChangeParse(newdealjson[wxT("s1")], target->special1);
			alert_dealchanged |= JSONChangeParse(newdealjson[wxT("s2")], target->special2);
			alert_dealchanged |= JSONChangeParse(newdealjson[wxT("image")], target->image);

			if(alert_newsite || alert_dealchanged)
			{
				wCallEvent(wEVT_DEAL_CHANGED, target);
			}
			if(!alert_newsite)
			{
				if(alert_newdeal) {}
				else if(alert_lowstock) {}
			}
		}
	}

	if(mode == wxT("full"))
	{
		wDealSetSafe dealSet;

		int count = dealSet->Count();
		for(int i = 0; i < count; i++)
		{
			wDeal* target = dealSet[i];
			bool deleteit = false;
			{
				wDealSafe deal(target);
				if(!deal->refreshed) deleteit = true;
			}
			if(deleteit)
			{
				// TODO: test this
				wxGetApp().dealstore.DeleteDeal(target);
				listchanged = true;
				i--;
				count--;
			}
		}
	}

	if(listchanged)
	{
		// TODO:
		wCallEvent(wEVT_DEALLIST_CHANGED);
	}

	return true;
}

bool wDealProcessor::JSONChangeParse(wxJSONValue& json, wxString& target)
{
	wxString newval;
	if(json.AsString(newval))
	{
		if(newval != target)
		{
			target = newval;
			return true;
		}
	}
	return false;
}

bool wDealProcessor::JSONChangeParse(wxJSONValue& json, int& target)
{
	int newval;
	if(json.AsInt(newval))
	{
		if(newval != target)
		{
			target = newval;
			return true;
		}
	}
	return false;
}

bool wDealProcessor::JSONChangeParse(wxJSONValue& json, bool& target)
{
	bool newval;
	if(json.AsBool(newval))
	{
		if(newval != target)
		{
			target = newval;
			return true;
		}
	}
	return false;
}

bool wDealProcessor::JSONChangeParse(wxJSONValue& json, double& target)
{
	double newval;
	if(json.AsDouble(newval))
	{
		if(newval != target)
		{
			target = newval;
			return true;
		}
	}
	return false;
}
