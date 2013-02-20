#include "prec.h"
#include "wSettingsUpgraderEngine.h"
#include "guievents.h"

bool wSettingsUpgraderEngine::NeedsUpgrade()
{
	return true;
}

int wSettingsUpgraderEngine::Upgrade()
{
	wxStandardPaths::Get().UseAppInfo(wxStandardPaths::AppInfo_AppName);
	wxChar sep = wxFileName::GetPathSeparator();

	// DO THE UPGRADE! Return non-zero on error
	wxString v3dir = wxStandardPaths::Get().GetUserConfigDir();
	v3dir += sep+"wootalyzer";
	wxString v3settings = v3dir + sep+"settings.ini";

	wxString v4dir = wxStandardPaths::Get().GetUserConfigDir();
	v4dir += sep+"Wootalyzer";
	wxString v4settings = v4dir + sep+"settings.json";

	bool v4exists = wxFileExists(v4settings);

	if(wxFileExists(v3settings)) {
		wxDir dir(v3dir);
		if (!dir.IsOpened()) {
			return 1;
		}

		wxString filename;
		bool cont = dir.GetFirst(&filename, wxEmptyString, wxDIR_FILES);
		while(cont)
		{
			if(filename.EndsWith(".ini"))
			{
				if(v4exists)
				{
					// just delete everything from v3 if v4 exists
				} else {
				}
				wxRemoveFile(v3dir+sep+filename);
			}
			cont = dir.GetNext(&filename);
		}
	}

	return 0;
}

void* wSettingsUpgraderEngine::Entry()
{
	int result = Upgrade();
	wCallEvent(wEVT_SETTINGS_UPGRADED, (void*)result);
	return 0;
}

