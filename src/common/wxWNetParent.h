#pragma once

enum wxNetProxyType
{
  wxSOCKET_PROXY_NONE,
  wxSOCKET_PROXY_HTTPS,
  wxSOCKET_PROXY_SOCKS5
};

class wxWNetParent
{
public:
	wxWNetParent()
	{
		pType = wxSOCKET_PROXY_NONE;
		pPort = 0;
		stopped = false;
	}
	bool WIsError() { return error.Length() != 0; }
	wxString WLastError() { return error; }
	void Stop() {
		stopped = true;
	}
	void SetProxy(wxNetProxyType type, wxString hostname=wxT(""), int port=80, wxString user=wxT(""), wxString pass=wxT(""))
	{
		pType = type;
		pHostname = hostname;
		pPort = port;
		pUser = user;
		pPass = pass;
	}
protected:
	void WDoError(wxString newerror = wxT("")) { error = newerror; };
	bool IsStopped() { return stopped; }

	wxNetProxyType pType;
	wxString pHostname;
	int pPort;
	wxString pUser;
	wxString pPass;
private:
	wxString error;
	bool stopped;
};
