#pragma once
#include "wDeal.h"

WX_DEFINE_ARRAY(wDeal*, wDealSet);
WX_DECLARE_HASH_MAP(wxThreadIdType, wDeal*, wxIntegerHash, wxIntegerEqual, dealHoldMapType);

class wDealStoreInternal {
public:
	~wDealStoreInternal();
	void DeleteDeal(wDeal*& target);

protected:
	void AquireSet();
	void ReleaseSet();
	void AquireDeal(wDeal*&);
	void ReleaseDeal(wDeal*&);
	friend class wDealSafe;
	friend class wDealSetSafe;

private:
	wDeal* GetDealHold();
	void SetDealHold(wDeal*);
	dealHoldMapType m_dealHoldMap;
	SafeMutex m_dealHoldMapLock;

	wDealSet m_dealSet;
	SafeMutex m_dealSetLock;
};
