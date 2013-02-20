#include "prec.h"
#include "guievents.h"
#include "wSettingsUpgrader.h"
#include "wSettingsUpgraderEngine.h"

// returns non-zero if the app should quit
int wSettingsUpgrader::Upgrade() {
	if(!wSettingsUpgraderEngine::NeedsUpgrade())
		return 0;

	FrameSettingsUpgrader* window = new FrameSettingsUpgrader(NULL);
	window->Centre(wxCENTRE_ON_SCREEN);
	window->SetFocus();

	wSettingsUpgraderEngine* upgrader = new wSettingsUpgraderEngine();
	upgrader->Create();
	upgrader->Run();

	// this won't return until the upgrader thread tells the window that it's done
	int result = window->ShowModal();

	delete upgrader;

	return result;
}

FrameSettingsUpgrader::FrameSettingsUpgrader( wxWindow* parent )
: FrameSettingsUpgraderGui(parent)
{
	wEvents.Connect(wEVT_SETTINGS_UPGRADED, wxCommandEventHandler(FrameSettingsUpgrader::OnUpgradeDone), NULL, this);
}

FrameSettingsUpgrader::~FrameSettingsUpgrader() {
	wEvents.Disconnect(wEVT_SETTINGS_UPGRADED, wxCommandEventHandler(FrameSettingsUpgrader::OnUpgradeDone), NULL, this);
}

void FrameSettingsUpgrader::OnClose(wxCloseEvent& event) {
	// block close
	EndModal(0);
}

void FrameSettingsUpgrader::OnUpgradeDone(wxCommandEvent &event) {
	int result = (int)event.GetClientData();
	if(result != 0) {
		int answer = wxMessageBox(
			"There was a problem migrating your settings from the old version of Wootalyzer. If you continue, your settings will be lost. Would you like to continue?",
			"Settings Migration Error",
			wxYES_NO, this);
		if(answer == wxYES) {
			result = 0;
		} else {
			// TODO: save here
		}
	}

	EndModal(result);
}
