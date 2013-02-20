#pragma once

class wSettingsUpgraderEngine : public StoppableThread
{
public:
	static bool NeedsUpgrade();
	int Upgrade();
	void* Entry();
};
