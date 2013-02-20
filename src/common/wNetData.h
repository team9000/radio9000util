#pragma once

#include "SafeMutex.h"

class wNetData {
public:
	wNetData();

	// Fetch
	int fetch_timeout;
	int fetch_speedlimit;
	wxString fetch_url;
	bool fetch_reset;
	int fetch_turbo;
	int fetch_lastattempt;
	int fetch_lastsuccess;

	// Push
	int push_timeout[3]; // c, w, r // TODO: use timeout!
	int push_speedlimit;
	wxString push_host;
	int push_port;
	bool push_reset;
	int push_turbo;
	int push_lastattempt;
	int push_lastsuccess;
	bool push_connecting;
	bool push_connected;

	SafeMutex lock;
};

class wNetDataSafe
{
public:
	wNetDataSafe()
	{
		data.lock.Enter();
	}
	~wNetDataSafe()
	{
		data.lock.Leave();
	}
	wNetData* operator->() { return &data; };
	wNetData* GetData() { return &data; }
private:
	static wNetData data;
};
