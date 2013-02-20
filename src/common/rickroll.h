#pragma once

class thread_rickroll : public wxThread
{
public:
    thread_rickroll();
    void* Entry();

	static HSTREAM rickstream;
};

void rickroll();
