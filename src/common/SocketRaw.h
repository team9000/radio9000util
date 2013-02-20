#pragma once

#include "SocketBase.h"
#include "DynData.h"

class SocketRaw : public SocketBase
{
public:
	SocketRaw();
	~SocketRaw();

	void Connect(wxString hostname, int port);
	wxString ReadLine();
	void Send(wxString data);
	void Process();

private:
	DynData outgoing;
	DynData incoming;
	CURL* curl;
	curl_socket_t sockfd;
};
