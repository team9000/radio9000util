#pragma once

#include "StoppableThread.h"
#include "ProtoJsonNL.h"

class tPush : public StoppableThread
{
public:
	void* Entry();
	void OnShutdown();

private:
//	bool GetNetVars();
//	void DoPush();

	ProtoJsonNL push;
//	int booster_num;
//	long last_attempt;
//	long last_complete;

//	wxString host;
//	int port, speedlimit;
};
