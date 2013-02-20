#include "prec.h"
#include "wDealStoreInternal.h"

/*************************
Important, to prevent deadlock, this Mutex policy MUST be followed!

Regarding wDeal's and the master deal set inside wDealManager
- While the set is locked, you may lock a specific deal, and unlock the set
- While the set is not locked, you may NOT lock a specific deal
- If any specific deal is locked >> YOU MAY NOT LOCK THE SET <<

This final point is extremely important, and means that you may not call a deal lookup on the same deal twice
(because the second lookup will try to put a lock on the list, while the first lookup already has the deal locked).

Here's the race condition:
Thread A locks list, locks deal D, unlocks list
Thread B locks list, trys to lock deal D (and halts)
Thread A trys to lock list again (and halts)

This class (wDealStoreInternal) detects this deadlock condition and asserts
************************/

wDealStoreInternal::~wDealStoreInternal()
{
	// Don't release the locks from here on out
	// If a thread gets hung up on them - too bad
	// We don't want to release locks on objects that are getting deleted

	m_dealSetLock.Enter();
	int count = m_dealSet.Count();
	for(int i = 0; i < count; i++)
	{
		m_dealSet[i]->lock.Enter();
		delete m_dealSet[i];
	}
	m_dealSet.Clear();
}

wDeal* wDealStoreInternal::GetDealHold()
{
	SafeMutexLocker locker(m_dealHoldMapLock);
	wxThreadIdType myid = wxThread::GetCurrentId();
	if(m_dealHoldMap.find(myid) == m_dealHoldMap.end())
		return NULL;
	return m_dealHoldMap[myid];
}
void wDealStoreInternal::SetDealHold(wDeal* target)
{
	SafeMutexLocker locker(m_dealHoldMapLock);
	wxThreadIdType myid = wxThread::GetCurrentId();
	m_dealHoldMap[myid] = target;
}
void wDealStoreInternal::AquireSet()
{
	if(!m_dealSetLock.HeldByMe())
		wxASSERT_MSG(GetDealHold() == NULL, "Thread attempted to lock set while holding a deal (breaks mutex policy)");
	m_dealSetLock.Enter();
}
void wDealStoreInternal::ReleaseSet()
{
	m_dealSetLock.Leave();
}
void wDealStoreInternal::AquireDeal(wDeal*& target)
{
	wxASSERT_MSG(target != NULL, "Thread attempted to aquire NULL deal pack");
	wxASSERT_MSG(target->lock.HeldByMe() || m_dealSetLock.HeldByMe(), "Thread attempted to aquire deal without holding deal set");

	// Check for existing deal holds
	{
		SafeMutexLocker locker(m_dealHoldMapLock);
		wDeal* held = GetDealHold();
		wxASSERT_MSG(held == NULL || held == target, "Thread attempted to aquire second deal pack");
		SetDealHold(target);
	}

	target->lock.Enter();
}
void wDealStoreInternal::ReleaseDeal(wDeal*& target)
{
	wxASSERT_MSG(target != NULL, "Thread attempted to release NULL deal pack");
	// Check for existing deal holds
	{
		SafeMutexLocker locker(m_dealHoldMapLock);
		wDeal* held = GetDealHold();
		wxASSERT_MSG(held == target, "Thread attempted to release deal pack it did not hold");
	}

	target->lock.Leave();

	// Only remove the hold from the map if we actually don't hold the lock anymore (some locks are held multiple levels)
	if(!target->lock.HeldByMe()) {
		SafeMutexLocker locker(m_dealHoldMapLock);
		SetDealHold(NULL);
	}
}
void wDealStoreInternal::DeleteDeal(wDeal*& target)
{
	wxASSERT_MSG(target != NULL, "Thread attempted to delete NULL deal pack");
	wxASSERT_MSG(m_dealSetLock.HeldByMe(), "Thread attempted to delete deal without holding deal set");
	wxASSERT_MSG(!target->lock.HeldByMe(), "Thread attempted to delete deal while holding its lock");
	target->lock.Enter();
	m_dealSet.Remove(target);
	delete target;
}