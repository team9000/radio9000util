#pragma once
#include "wDeal.h"

class wDealProcessor {
public:
	static bool ProcessPack(wxJSONValue& datapack);

private:
	static bool JSONChangeParse(wxJSONValue& json, wxString& target);
	static bool JSONChangeParse(wxJSONValue& json, int& target);
	static bool JSONChangeParse(wxJSONValue& json, bool& target);
	static bool JSONChangeParse(wxJSONValue& json, double& target);
};
