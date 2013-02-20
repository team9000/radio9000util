#include "prec.h"
#include "StoppableThread.h"

StoppableThread::StoppableThread() : wxThread(wxTHREAD_JOINABLE)
{
	shutdown = false;
}

void StoppableThread::Shutdown()
{
	shutdown = true;
	OnShutdown();
}

bool StoppableThread::TestShutdown()
{
	return shutdown;
}

void StoppableThread::SleepOrShutdown(long milliseconds)
{
	wxStopWatch sw;
	while(sw.Time() < milliseconds)
	{
		wxThread::Sleep(50);
		if(TestShutdown()) return;
	}
}
