#pragma once

wxDECLARE_EVENT(wEVT_DEAL_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(wEVT_DEAL_NEWITEM, wxCommandEvent);
wxDECLARE_EVENT(wEVT_DEAL_LOWSTOCK, wxCommandEvent);
wxDECLARE_EVENT(wEVT_DEALLIST_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(wEVT_STATUS_CHANGED, wxCommandEvent);
wxDECLARE_EVENT(wEVT_IMAGE_CHANGED, wxCommandEvent);

wxDECLARE_EVENT(wEVT_SETTINGS_UPGRADED, wxCommandEvent);


extern wxEvtHandler wEvents;

void wCallEvent(const wxEventType &event, void* data=NULL);
