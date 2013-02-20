#pragma once

enum wDealStoreSortMethod
{
	wDEAL_SORT_RECOMMENDED,
	wDEAL_SORT_NAME
};
enum wDealStoreRequirement
{
	wDEAL_REQUIRE_NONE,
	wDEAL_REQUIRE_TRACKED,
	wDEAL_REQUIRE_IMAGEDL
};
enum wDealStoreAdjustment
{
	wDEAL_ADJUST_NONE,
	wDEAL_ADJUST_FIX,
	wDEAL_ADJUST_UP,
	wDEAL_ADJUST_DOWN
};

#include "wDealStoreInternal.h"
#include "wDealSafe.h"

// wDealStore is a 100% Thread-Safe class for managing and handling
// deal storage in Wootalyzer. Use wDealSafe for aquiring a wDeal class.

class wDealStore : public wDealStoreInternal {
public:
	// adjusts the deal selection, locks set and deal appropriately
	bool Adjust(wDeal*& target, wDealStoreAdjustment adjust=wDEAL_ADJUST_NONE, wDealStoreRequirement require=wDEAL_REQUIRE_NONE);
	void Resort(bool cat, wDealStoreSortMethod method);
	wDeal* Lookup(int siteid);

private:
	friend class wDealSafe;

	wDeal* AdjustHelper(wDealSetSafe &dealSet, bool countup, int startindex, wDealStoreRequirement require);
	void Sort();

	static SafeMutex ms_sortLock;
	static bool ms_sortCat;
	static wDealStoreSortMethod ms_sortMethod;
	static int SortHandler(wDeal** _first, wDeal** _second);
};
