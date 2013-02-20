#pragma once

#include "wx/thread.h"

class StoppableThread : public wxThread
{
public:
	StoppableThread();
	void Shutdown();

protected:
	// test for shutdown just BEFORE all sleeps / blocking thread ops
	bool TestShutdown();
	virtual void OnShutdown() { };
	void SleepOrShutdown(long milliseconds);

private:
	bool shutdown;
};
