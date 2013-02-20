#include "prec.h"
#include "image.h"
#include "guievents.h"

void* tImage::Entry()
{
	while(true)
	{
		if(TestShutdown()) return 0;

		wxStopWatch iterationtime;

		DoImage();

		while(iterationtime.Time() < REFRESH_LOOP_SAFETYTIME)
		{
			SleepOrShutdown(100);
		}
	}
	return 0;
}

void tImage::OnShutdown()
{
	http.Stop();
}

void tImage::DoImage()
{
	// Find a deal that needs its image downloaded
	// TODO: give priority to deals that are selected already
	// TODO: ONLY download images for deals that are TRACKED!!! IMPORTANT!

	wDeal* target = NULL;
	wxString imageurl;
	{
		wDealSafe dealsafe(target, wDEAL_ADJUST_FIX, wDEAL_REQUIRE_IMAGEDL);
		if(target == NULL) return; // No valid targets!
		target->image_downloading = true;
		if(target->image_localfile != wxT("")) {
			wxRemoveFile(target->image_localfile);
			target->image_localfile = wxT("");
		}
		target->image_dlattempts++;// TODO: delete all image files on exit
		imageurl = target->image;
	}

	wxString filename = wxFileName::CreateTempFileName(wxT("wtz"));
	http.DownloadFile(imageurl, filename);
	bool downloaded = !http.HasError();
	downloaded &= wxFileExists(filename);

	{
		wDeal* oldtarget = target;
		wDealSafe dealsafe(target, wDEAL_ADJUST_FIX);
		if(oldtarget != target)
		{
			// deal is gone!
			wxRemoveFile(filename);
			return;
		}
		if(imageurl != target->image)
		{
			// image has changed since we started
			wxRemoveFile(filename);
			return;
		}
		target->image_downloading = false;
		if(downloaded)
		{
			target->image_downloaded = true;
			target->image_localfile = filename;

			wCallEvent(wEVT_IMAGE_CHANGED, target);
		}
	}
}
