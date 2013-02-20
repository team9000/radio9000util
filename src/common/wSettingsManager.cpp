#include "prec.h"
#include "wSettingsManager.h"
#include <wx/wfstream.h>

wxString wSettingsManager::Filename() {
	// TODO: when upgrading WX, make sure GetUserConfigDir still returns what we think it returns
	// because right now, it's not working as documented
	// Look through all files for this, we use it elsewhere
	wxStandardPaths::Get().UseAppInfo(wxStandardPaths::AppInfo_AppName);
	wxChar sep = wxFileName::GetPathSeparator();

	wxString filename = wxStandardPaths::Get().GetUserConfigDir();
	filename += sep+"Wootalyzer";
	filename += sep+"settings.json";
	return filename;
}

int wSettingsManager::Load() {
	// TODO: should we lock during load and save?
	root = wxJSONValue(wxJSONTYPE_OBJECT);

	wxFFileInputStream input(Filename(), "r");
	if(!input.IsOk()) return 0;

	wxJSONReader reader;
	int numErrors = reader.Parse(input, &root);
	if(numErrors > 0) {
		int answer = wxMessageBox(
			"There was a problem loading your Wootalyzer settings. If you continue, your settings will be lost. Would you like to continue?",
			"Settings Load Error",
			wxYES_NO, NULL);
		if(answer != wxYES) {
			return 1;
		}
		Save();
	}
	return 0;
}

void wSettingsManager::Save() {
	wxFFileOutputStream output(Filename(), "w");
	if(!output.IsOk()) return;

	wxJSONWriter writer;
	writer.Write(root, output);
}
