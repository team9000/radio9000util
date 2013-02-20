#include "prec.h"
#include "SocketBase.h"

SocketBase::SocketBase()
{
	stopped = false;
	errored = true;
	error = "Socket Not Connected";
	proxyType = wSOCKET_PROXY_NONE;
	proxyPort = 0;
}

void SocketBase::SetProxy(SocketProxyType type, wxString host, int port, wxString user, wxString pass)
{
	proxyType = type;
	proxyHost = host;
	proxyPort = port;
	proxyUser = user;
	proxyPass = pass;
}

void SocketBase::Stop()
{
	error = "Socket is stopped for shutdown";
	errored = true;
	stopped = true;
}
bool SocketBase::IsStopped()
{
	return stopped;
}
bool SocketBase::HasError()
{
	return stopped || errored;
}
wxString SocketBase::GetError()
{
	return error;
}

void SocketBase::Error(wxString newerror)
{
	if(errored) return;
	error = newerror;
	errored = true;
}

void SocketBase::AutoError(CURLcode code, wxString msg)
{
	wxString reason;
	if(code == CURLE_OK) {
		reason = wxT("No error code?");
	} else {
		reason = wxString::Format(wxT("CODE %d"), code);
	}
	if(msg != "")
		reason = msg+wxT(" - ")+reason;

	Error(reason);
}

void SocketBase::ClearError()
{
	errored = false;
	error = "";
}

void SocketBase::ApplyCurlParams(CURL* curl)
{
	if(proxyType != wSOCKET_PROXY_NONE && proxyHost != "") {
		curl_easy_setopt(curl, CURLOPT_PROXY, (const char*)proxyHost.ToUTF8());
		curl_easy_setopt(curl, CURLOPT_PROXYPORT, (long)proxyPort);
		curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 1);

		if(proxyType == wSOCKET_PROXY_HTTPS)
			curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
		else if(proxyType == wSOCKET_PROXY_SOCKS5)
			curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);

		if(proxyUser != "")
			curl_easy_setopt(curl, CURLOPT_PROXYUSERNAME, (const char*)proxyUser.ToUTF8());
		if(proxyPass != "")
			curl_easy_setopt(curl, CURLOPT_PROXYPASSWORD, (const char*)proxyUser.ToUTF8());
	}
}



/*
OLD PROXY CODE

void wxWSocketClient::Connect(wxString hostname, int port)
{
	if(IsStopped())
	{
		WDoError(wxT("Socket is stopped for shutdown"));
		return;
	}

	WDoError();
	closeOnError = true;
	wxSocketClient::Close();

	wxString connectHost;
	int connectPort;
	if(pType == wxSOCKET_PROXY_NONE)
	{
		connectHost = hostname;
		connectPort = port;
	} else {
		connectHost = pHostname;
		connectPort = pPort;
	}

	wxIPV4address addr;
	if(!addr.Hostname(connectHost))
	{
		WDoError(wxT("Invalid Hostname"));
		return;
	}
	if(!addr.Service(connectPort))
	{
		WDoError(wxT("Invalid Port"));
		return;
	}
	wxSocketClient::SetFlags(wxSOCKET_WAITALL | wxSOCKET_BLOCK);
	wxSocketClient::SetTimeout(timeoutConnect);
	if(!wxSocketClient::Connect(addr, true))
	{
		WDoError(FormatError(wxT("C")));
		return;
	}

	if(pType == wxSOCKET_PROXY_HTTPS)
	{
		wxString write = wxString::Format(wxT("CONNECT %s:%d HTTP/1.0\r\n"), hostname, port);
		write += wxT("User-agent: Mozilla/1.1N\r\n");
		if(pUser != wxT("") || pPass != wxT(""))
		{
			write += wxString::Format(wxT("Proxy-Authorization: %s\r\n"), GenerateAuthString(pUser, pPass));
		}
		write += wxT("\r\n");
		WriteStringAsMB(write);
		if(WIsError()) return;

		wxByte read=0;
		wxString header = wxT("");

		while(true)
		{
			read = ReadByte();
			if(WIsError()) return;
			header += read;
			if(header.EndsWith(wxT("\r\n\r\n"))) break;
		}

		if(!header.Contains(wxT(" 200 ")))
		{
			WDoError(wxT("Invalid HTTP Proxy Response: \n")+header.Trim());
			return;
		}
	}
	else if(pType == wxSOCKET_PROXY_SOCKS5)
	{
		bool usepass = (pUser != wxT("") || pPass != wxT(""));
		int authmethod = usepass ? 2 : 0;

		wxByte send[10];
		send[0] = 5;
		send[1] = 1;
		send[2] = authmethod;
		Write(send, 3);
		if(WIsError()) return;

		wxByte read = ReadByte();
		if(WIsError()) return;
		if(read != 5)
		{
			WDoError(wxString::Format(wxT("Invalid SOCKS5 Version Response: %d"), read));
			return;
		}

		read = ReadByte();
		if(WIsError()) return;
		if(read != authmethod)
		{
			WDoError(wxString::Format(wxT("Invalid SOCKS5 Auth Response: %d"), read));
			return;
		}

		if(usepass)
		{
			send[0] = 1;
			Write(send, 1);
			if(WIsError()) return;

			wxWX2MBbuf mbUser = pUser.mb_str();
			int length = strlen(mbUser);
			send[0] = length;
			Write(send, 1);
			if(WIsError()) return;
			Write(mbUser, length);
			if(WIsError()) return;

			wxWX2MBbuf mbPass = pPass.mb_str();
			length = strlen(mbPass);
			send[0] = length;
			Write(send, 1);
			if(WIsError()) return;
			Write(mbPass, length);
			if(WIsError()) return;

			read = ReadByte();
			if(WIsError()) return;
			read = ReadByte();
			if(WIsError()) return;
			if(read != 0)
			{
				WDoError(wxString::Format(wxT("SOCKS5 Authentication Failed: %d"), read));
				return;
			}
		}

		send[0] = 5;
		send[1] = 1;
		send[2] = 0;
		send[3] = 3;
		Write(send, 4);
		if(WIsError()) return;

		wxWX2MBbuf mbHost = hostname.mb_str();
		int length = strlen(mbHost);
		send[0] = length;
		Write(send, 1);
		if(WIsError()) return;
		Write(mbHost, length);
		if(WIsError()) return;

		wxUint16 port16 = port;
		wxUint16 bigEndianPort16 = wxUINT16_SWAP_ON_LE(port16);
		Write(&bigEndianPort16, 2);
		if(WIsError()) return;

		read = ReadByte();
		if(WIsError()) return;
		if(read != 5)
		{
			WDoError(wxString::Format(wxT("Invalid SOCKS5 Version Response 2: %d"), read));
			return;
		}

		read = ReadByte();
		if(WIsError()) return;
		if(read != 0)
		{
			WDoError(wxString::Format(wxT("SOCKS5 Connection Refused: %d"), read));
			return;
		}

		read = ReadByte();
		if(WIsError()) return;

		wxByte skiptype = ReadByte();
		if(WIsError()) return;

		int skipbytes = 0;
		if(skiptype == 1)
		{
			skipbytes = 4;
		} else if(skiptype == 3) {
			skipbytes = ReadByte();
			if(WIsError()) return;
		} else if(skiptype == 4) {
			skipbytes = 16;
		} else {
			WDoError(wxString::Format(wxT("SOCKS5 Invalid SkipBytes: %d"), read));
			return;
		}

		for(int i = 0; i < skipbytes+2; i++) {
			ReadByte();
			if(WIsError()) return;
		}
	}
}

*/
