#pragma once
#include "wDealStore.h"

// Fetches a deal, adjusts the selection if nessicary, and locks the deal for access
// until the safe is destroyed
class wDealSafe
{
public:
	wDealSafe(wDeal* target);
	wDealSafe(wDeal*& target, wDealStoreAdjustment adjust, wDealStoreRequirement require=wDEAL_REQUIRE_NONE);
	void Init(wDeal*& target, wDealStoreAdjustment adjust=wDEAL_ADJUST_NONE, wDealStoreRequirement require=wDEAL_REQUIRE_NONE);
	~wDealSafe();
	wDeal* operator->() { return data; };
	wDeal* GetData() { return data; }
private:
	wDeal* data;
};

class wDealSetSafe
{
public:
	wDealSetSafe();
	~wDealSetSafe();
	wDealSet* operator->() { return data; };
	wDeal* operator[](size_t i) { return data->operator[](i); }
private:
	wDealSet* data;
};
