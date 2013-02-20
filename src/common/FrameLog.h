#pragma once

class FrameLog : public wxLogWindow
{
public:
	static FrameLog* single;
	static void Start();
	static void Stop();
	static void Open();

	FrameLog( wxWindow* parent );
	~FrameLog();
};
