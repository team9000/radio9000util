#include "prec.h"
#include "guievents.h"

wxDEFINE_EVENT(wEVT_DEAL_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(wEVT_DEAL_NEWITEM, wxCommandEvent);
wxDEFINE_EVENT(wEVT_DEAL_LOWSTOCK, wxCommandEvent);
wxDEFINE_EVENT(wEVT_DEALLIST_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(wEVT_STATUS_CHANGED, wxCommandEvent);
wxDEFINE_EVENT(wEVT_IMAGE_CHANGED, wxCommandEvent);

wxDEFINE_EVENT(wEVT_SETTINGS_UPGRADED, wxCommandEvent);

wxEvtHandler wEvents;

void wCallEvent(const wxEventType &event, void* data) {
	// wxQueueEvent takes ownership of the event
	// be careful to not shallow copy anything into event
	// We must not have ownership over any of it!
	// see http://docs.wxwidgets.org/trunk/classwx_evt_handler.html

	// TODO: change this to wxQueueEvent and wEvents.QueueEvent
	// as soon as we upgrade to wx2.9
	// keep in mind that QueueEvent takes ownership of the object, but this doesn't
	//
	// be sure to find AddPendingEvent in ALL project files, because we use it in other places too
	wxCommandEvent MyEvent(event);
	if(data) MyEvent.SetClientData(data);
	wEvents.AddPendingEvent(MyEvent);
}
