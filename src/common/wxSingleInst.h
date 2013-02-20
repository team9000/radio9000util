#pragma once

class wxSingleInst
{
private:
	wxSingleInstanceChecker* check;
	wxServerBase* server;
	bool other;
public:
	wxSingleInst();
	~wxSingleInst();
	bool IsAnotherRunning();
};

class sConnection : public wxConnection
{
public:
	virtual bool OnExecute(const wxString& topic, wxChar*data, int size, wxIPCFormat format);
};

class sServer: public wxServer
{
public:
	virtual wxConnectionBase *OnAcceptConnection(const wxString& topic);
};
