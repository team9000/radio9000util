#pragma once

#include "StoppableThread.h"
#include "ProtoHTTP.h"

class tImage : public StoppableThread
{
public:
	void* Entry();
	void OnShutdown();

private:
	void DoImage();

	ProtoHTTP http;
};
