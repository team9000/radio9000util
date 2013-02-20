#include "prec.h"
#include "wDealStore.h"
#include "wDealSafe.h"

wDealSafe::wDealSafe(wDeal* target)
{
	Init(target);
}
wDealSafe::wDealSafe(wDeal*& target, wDealStoreAdjustment adjust, wDealStoreRequirement require)
{
	Init(target, adjust, require);
}
void wDealSafe::Init(wDeal*& target, wDealStoreAdjustment adjust, wDealStoreRequirement require)
{

	// Not doing any fixes, and we already have a lock? We can bypass
	// locking the set, and just aquire.
	// Previously, when we tried to lock the same set twice, we would break the
	// Mutex policy by trying to lock the set on the second run.
	if(adjust == wDEAL_ADJUST_NONE && target == NULL) {
		data = NULL;
		return;
	}
	if(adjust == wDEAL_ADJUST_NONE && target->lock.HeldByMe()) {
		wxGetApp().dealstore.AquireDeal(target);
		data = target;
		return;
	}

	wDealSetSafe dealSetSafe;
	wxGetApp().dealstore.Adjust(target, adjust, require);
	if(target) {
		wxGetApp().dealstore.AquireDeal(target);
		data = target;
	} else {
		data = NULL;
	}
}
wDealSafe::~wDealSafe()
{
	if(data) wxGetApp().dealstore.ReleaseDeal(data);
}

wDealSetSafe::wDealSetSafe()
{
	wxGetApp().dealstore.AquireSet();
	data = &wxGetApp().dealstore.m_dealSet;
}
wDealSetSafe::~wDealSetSafe()
{
	wxGetApp().dealstore.ReleaseSet();
}