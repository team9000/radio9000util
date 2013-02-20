#pragma once

#include "SocketBase.h"

// from http://curl.haxx.se/libcurl/c/getinmemory.html
class ProtoHTTPMem
{
public:
	void* memory;
	size_t size;

	ProtoHTTPMem()
	{
		memory = NULL;
		size = 0;
	}
	~ProtoHTTPMem()
	{
		if(memory) free(memory);
	}
	void Realloc(size_t size)
	{
	  if(memory)
		memory = realloc(memory, size);
	  else
		memory = malloc(size);
	}
};

class ProtoHTTP;
class ProtoHTTPRequest
{
public:
	wxString url;
	wxFile* writefile;
	ProtoHTTPMem* writemem;
	int timeout;
	ProtoHTTP* caller;
	ProtoHTTPRequest()
	{
		writefile = NULL;
		writemem = NULL;
		timeout = 10;
	}
};

class ProtoHTTP : public SocketBase
{
public:
	ProtoHTTP();
	~ProtoHTTP();
	void SetTimeout(int seconds) {
		timeout = seconds;
	}

	void DownloadFile(wxString url, wxString filename);
	void DownloadText(wxString url, wxString &output);
	static wxString URLEncode(wxString input);

private:
	CURL* curl;
	void Download(ProtoHTTPRequest& request);
	static int CurlProgress (void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);
	static size_t CurlWriteMem(void *ptr, size_t size, size_t nmemb, void *stream);
	static size_t CurlWriteFile(void *ptr, size_t size, size_t nmemb, void *stream);

	int timeout;
};
