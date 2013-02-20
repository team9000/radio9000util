#include "prec.h"
#include "wDealStore.h"

wDeal* wDealStore::AdjustHelper(wDealSetSafe &dealSet, bool countup, int startindex, wDealStoreRequirement require)
{
	// WARNING!!! because this deal is not locked between the return and when the parent locks it, 
	// require may not be fulfilled during a rare race condition (if the deal changes
	// between these two points in time)
	// To prevent this race condition, you must pass in a pre-locked deal set
	// Then, after this function is called, you can lock the deal, and unlock the set

	int count = dealSet->Count();
	for(int i = startindex; countup ? (i < count) : (i >= 0); countup ? (i++) : (i--))
	{
		wDealSafe deal(dealSet[i]);
		if(require == wDEAL_REQUIRE_TRACKED && !(true /*deal->IsTracked()*/)) // TODO:
			continue;
		if(require == wDEAL_REQUIRE_IMAGEDL && 
			!(
				!deal->image_downloaded && 
				!deal->image_downloading && 
				deal->image != wxT("") && 
				deal->image_dlattempts < IMAGE_DOWNLOAD_ATTEMPTS
			)
		)
			continue;
		return deal.GetData();
	}
	return NULL;
}
bool wDealStore::Adjust(wDeal*& target, wDealStoreAdjustment adjust, wDealStoreRequirement require)
{
	if(adjust == wDEAL_ADJUST_NONE) return false;

	wDealSetSafe dealSet;

	wDeal* olddeal = target;
	int pos = dealSet->Index(target);
	if(target == NULL || pos == wxNOT_FOUND)
	{
		if(adjust == wDEAL_ADJUST_FIX)
		{
			target = AdjustHelper(dealSet, true, 0, require);
		} else {
			WLOG(wxT("Non-fix adjustment applied to NULL deal pack!"));
			target = NULL;
		}
	} else {
		if(adjust == wDEAL_ADJUST_FIX) {
			// we already have a good deal!
		} else if(adjust == wDEAL_ADJUST_UP) {
			wDeal* newtarget = AdjustHelper(dealSet, true, pos+1, require);
			if(newtarget) target = newtarget;
		} else if(adjust == wDEAL_ADJUST_DOWN) {
			wDeal* newtarget = AdjustHelper(dealSet, false, pos-1, require);
			if(newtarget) target = newtarget;
		} else {
			target = NULL;
		}
	}

	return (olddeal != target);
}


wDeal* wDealStore::Lookup(int siteid)
{
	wDealSetSafe dealSet;

	int count = dealSet->Count();
	for(int i = 0; i < count; i++)
	{
		if(dealSet[i]->siteid == siteid) return dealSet[i];
	}
	return NULL;
}

void wDealStore::Resort(bool cat, wDealStoreSortMethod method)
{
	SafeMutexLocker sortlocker(ms_sortLock);
	ms_sortCat = cat;
	ms_sortMethod = method;
	Sort();
}

void wDealStore::Sort()
{
	// TODO: call this when the list needs resorted
	SafeMutexLocker sortlocker(ms_sortLock);
	wDealSetSafe dealSet;
	dealSet->Sort(wDealStore::SortHandler);
}

SafeMutex wDealStore::ms_sortLock;
bool wDealStore::ms_sortCat;
wDealStoreSortMethod wDealStore::ms_sortMethod;
int wDealStore::SortHandler(wDeal** _first, wDeal** _second)
{
	wDeal* first = *_first;
	wDeal* second = *_second;

	if(ms_sortCat)
	{
		int compare = first->category.Cmp(second->category);
		if(compare != 0) return compare;
	}

	if(ms_sortMethod == wDEAL_SORT_RECOMMENDED)
	{
		int compare = first->sortid - second->sortid;
		if(compare != 0) return compare;
	}

	int compare = first->title.Cmp(second->title);
	return compare;
}
