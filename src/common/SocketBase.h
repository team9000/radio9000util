#pragma once

enum SocketProxyType
{
	wSOCKET_PROXY_NONE,
	wSOCKET_PROXY_HTTPS,
	wSOCKET_PROXY_SOCKS5
};

class SocketBase
{
public:
	SocketBase();
	void SetProxy(SocketProxyType type, wxString host, int port, wxString user="", wxString pass="");
	void Stop();
	bool IsStopped();
	bool HasError();
	wxString GetError();

protected:
	void Error(wxString newerror);
	void AutoError(CURLcode code, wxString msg="");
	void ClearError();

	void ApplyCurlParams(CURL* curl);

private:
	bool stopped;
	bool errored;
	wxString error;

	SocketProxyType proxyType;
	wxString proxyHost;
	int proxyPort;
	wxString proxyUser;
	wxString proxyPass;
};
