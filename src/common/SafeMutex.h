#pragma once

#include "wx/thread.h"

/**
A critical section that can be nested safely --
a thread can enter the CS twice, then leave it twice safely
**/
class SafeMutex {
public:
	SafeMutex() {
		m_heldby = 0;
	}

	void Enter() {
		wxThreadIdType myid = wxThread::GetCurrentId();
		{
			wxCriticalSectionLocker checklocker(m_checklock);
			if(m_heldby == myid)
			{
				m_heldCount++;
				return;
			}
		}
		m_lock.Enter();
		{
			wxCriticalSectionLocker checklocker(m_checklock);
			m_heldby = myid;
			m_heldCount = 1;
		}
	}
	void Leave() {
		wxThreadIdType myid = wxThread::GetCurrentId();
		{
			wxCriticalSectionLocker checklocker(m_checklock);
			wxASSERT_MSG(m_heldby == myid, "Thread attempted to leave critical section that it did not hold");
			m_heldCount--;
			if(m_heldCount != 0) return;
			m_lock.Leave();
			m_heldby = 0;
		}
	}
	bool HeldByMe() {
		wxCriticalSectionLocker checklocker(m_checklock);
		return (wxThread::GetCurrentId() == m_heldby);
	}

private:
	wxThreadIdType m_heldby;
	unsigned int m_heldCount;
	wxCriticalSection m_lock;
	wxCriticalSection m_checklock;
};

/**
Locker for the above safe CS
**/
class SafeMutexLocker {
public:
	SafeMutexLocker(SafeMutex& lock) {
		m_myLock = &lock;
		m_myLock->Enter();
	}
	~SafeMutexLocker() {
		m_myLock->Leave();
	}
private:
	SafeMutex* m_myLock;
};
