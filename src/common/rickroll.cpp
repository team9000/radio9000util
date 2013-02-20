#include "prec.h"
#include "rickroll.h"

thread_rickroll::thread_rickroll()
: wxThread()
{
}

void* thread_rickroll::Entry()
{
	if(rickstream == 0)
	{
//		rickstream = BASS_StreamCreateURL("http://jon.oberheide.org/blog/wp-content/uploads/2008/03/rickroll.mp3",0,NULL, NULL, NULL);
		rickstream = BASS_StreamCreateURL("http://relay3.slayradio.org:8000/", 0, 0, NULL, NULL);
//		rickstream = BASS_StreamCreateURL("http://slayradio.org/tune_in.php/128kbps/listen.m3u",0,NULL, NULL, NULL);
	}
	BASS_ChannelPlay(rickstream,TRUE);

	return 0;
}

HSTREAM thread_rickroll::rickstream = NULL;

void rickroll()
{
	thread_rickroll* thread = new thread_rickroll(); // TODO: this has to get closed and deleted somewhere...
	thread->Create();
	thread->Run();
}
