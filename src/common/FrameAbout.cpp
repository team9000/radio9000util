#include "prec.h"
#include "FrameAbout.h"
#include "version.h"

FrameAbout::FrameAbout(wxWindow* parent)
: FrameAboutGui(parent)
{
	this->aboutbox->Connect(wxEVT_COMMAND_HTML_LINK_CLICKED, wxHtmlLinkEventHandler(FrameAbout::hitlink), NULL, this);

	wxString aboutstr;
	wxString aboutfile = wxT("misc/about.htm");
	if(wxFileExists(aboutfile)) {
		wxFFile file(aboutfile, wxT("r"));
		if(file.IsOpened()) {
			file.ReadAll(&aboutstr);
		}
	}

	this->aboutbox->SetPage(aboutstr);

	wxString version = wxString::FromUTF8(APP_VERSION_STR);
	wxString versionstr = wxT("Version ") + version;
	this->versionbox->SetLabel(versionstr);

	single = this;
}

FrameAbout::~FrameAbout()
{
	single = NULL;
}

FrameAbout* FrameAbout::single = NULL;
void FrameAbout::OpenSingle()
{
	if(!wxGetApp().mainwnd) return;
	if(!single)
		single = new FrameAbout(wxGetApp().mainwnd);
	single->Show();
	single->SetFocus();
}

void FrameAbout::OnOK(wxCommandEvent& event)
{
	Close();
}

void FrameAbout::OnWebsite(wxCommandEvent& event)
{
	wxLaunchDefaultBrowser(wxT("http://www.wootalyzer.com/"));
}

void FrameAbout::hitlink(wxHtmlLinkEvent &event)
{
	wxHtmlLinkInfo info = event.GetLinkInfo();
	wxString link = info.GetHref();
	wxLaunchDefaultBrowser(link);
}
