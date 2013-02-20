#pragma once

#include "wx/defs.h"
#include "jsonval.h"
#include "SocketRaw.h"

class ProtoJsonNL : public SocketRaw
{
public:
	wxJSONValue ReadJson();
	void Send(wxJSONValue& message);
};
