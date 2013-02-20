#pragma once

class wSettingsManager {
public:
	wSettingsManager()
	{
		// load from our settings file?
	}
	~wSettingsManager() { }
	void Save();
	int Load();

	SafeMutex lock;
	wxJSONValue root;

private:
	wxString Filename();
};
