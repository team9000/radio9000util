#include "prec.h"
#include "SocketRaw.h"

SocketRaw::SocketRaw()
{
	curl = curl_easy_init();
	sockfd = NULL;
}

SocketRaw::~SocketRaw()
{
	if(curl) curl_easy_cleanup(curl);
}

void SocketRaw::Connect(wxString hostname, int port)
{
	if(IsStopped()) return;
	ClearError();
	curl_easy_reset(curl);
	sockfd = NULL;

	curl_easy_setopt(curl, CURLOPT_URL, (const char*)hostname.ToUTF8());
	curl_easy_setopt(curl, CURLOPT_PORT, (long)port);

//	curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 0);
	curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
//	curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);

//	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
//	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, timeout);
	this->ApplyCurlParams(curl);

	CURLcode res = curl_easy_perform(curl);
	if(res != CURLE_OK) {
		AutoError(res);
		return;
	}

	long sockextr;
	res = curl_easy_getinfo(curl, CURLINFO_LASTSOCKET, &sockextr);
	if(res != CURLE_OK) {
		AutoError(res);
		return;
	}
	sockfd = sockextr;
}

wxString SocketRaw::ReadLine()
{
	return incoming.PopLine();
}

void SocketRaw::Send(wxString data)
{
	outgoing.Push(data);
}

void SocketRaw::Process()
{
	size_t bytesWritten;
	curl_easy_send(curl, outgoing.memory, outgoing.size, &bytesWritten);
	if(bytesWritten > 0) {
		outgoing.PopGarbage(bytesWritten);
	}

	size_t bytesRead;
	char temp[8192];
	while(true) {
		curl_easy_recv(curl, temp, 8192, &bytesRead);
		if(bytesRead <= 0) break;
		incoming.Push(temp, bytesRead);
	}
}
