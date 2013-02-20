#include "prec.h"
#include "Main.h"
#include "MainFrame.h"

IMPLEMENT_APP(Main)

bool Main::OnInit()
{
	if(!wxApp::OnInit())
		return false;

	wxInitAllImageHandlers();
//	SetExitOnFrameDelete(false);
	BASS_Init(-1,44100,0,NULL,NULL);
	srand((unsigned int)time(NULL));
	curl_global_init(CURL_GLOBAL_ALL);

	frame = new MainFrame("test");
//	frame->Show();

	tray = new RadioIcon();
	tray->SetIcon(wxICON(wicon));

	return true;
}

int Main::OnExit()
{
	tray->RemoveIcon();
	delete tray;

	curl_global_cleanup();
	return wxApp::OnExit();
}
