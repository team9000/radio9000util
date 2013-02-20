#include "prec.h"
#include "ProtoHTTP.h"
#include "version.h"

ProtoHTTP::ProtoHTTP()
{
	curl = curl_easy_init();
}

ProtoHTTP::~ProtoHTTP()
{
	if(curl) curl_easy_cleanup(curl);
}

void ProtoHTTP::DownloadFile(wxString url, wxString filename)
{
	if(IsStopped()) return;
	ClearError();

	// TODO: test downloading a new image while the current image is open for viewing
	wxFile file;
	if(!file.Create(filename, true)) {
		Error(wxT("Couldn't create file for write"));
		return;
	}
	if(!file.IsOpened()) {
		Error(wxT("Couldn't open file for write"));
		return;
	}

	ProtoHTTPRequest request;
	request.url = url;
	request.writefile = &file;
	Download(request);
	file.Close();
}

void ProtoHTTP::DownloadText(wxString url, wxString &output)
{
	if(IsStopped()) return;
	ClearError();

	ProtoHTTPMem tempmem; // this automagically gets capped with a \0 at the end
	ProtoHTTPRequest request;
	request.url = url;
	request.writemem = &tempmem;
	Download(request);
	if(HasError()) return; // memory clears itself

	if(tempmem.memory)
	{
		wxString convert = wxString::FromUTF8((char*)tempmem.memory);
		output = convert;
	} else {
		Error(wxT("wHTTP completed with no data in memory!"));
	}
}

void ProtoHTTP::Download(ProtoHTTPRequest& request)
{
	request.caller = this;
	const char* mburlchar = request.url.ToUTF8(); // beware, this only survives during this scope

	curl_easy_setopt(curl, CURLOPT_URL, mburlchar);
	curl_easy_setopt(curl, CURLOPT_REFERER, mburlchar);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "Wootalyzer/" APP_VERSION_STR " (www.wootalyzer.com)"); // TODO: see what this does
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
	curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 0);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
	curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, CurlProgress);
	curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &request);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
	curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 5);
	curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);

	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, timeout);
	this->ApplyCurlParams(curl);

	if(request.writefile)
	{
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteFile);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &request);
	}
	else if(request.writemem)
	{
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteMem);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &request);
	}
	else
	{
		Error(wxT("wxWHTTP called without write params"));
		return;
	}

	CURLcode result = curl_easy_perform(curl);
	long statLong;
	curl_easy_getinfo(curl, CURLINFO_HTTP_CODE, &statLong);

	if(result != CURLE_OK) {
		Error(wxString::Format(wxT("wxWHTTP resulted in CURL error %d"), result));
		return;
	}
	if(statLong != 200) {
		Error(wxString::Format(wxT("wxWHTTP resulted in HTTP error %d"), statLong));
		return;
	}
}

int ProtoHTTP::CurlProgress(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
	ProtoHTTPRequest* request = (ProtoHTTPRequest*)clientp;
	if(request->caller->IsStopped())
		return 1;

	return 0;
}

size_t ProtoHTTP::CurlWriteMem(void *ptr, size_t size, size_t nmemb, void *stream)
{
	ProtoHTTPRequest* request = (ProtoHTTPRequest*)stream;
	if(request->caller->IsStopped())
		return 0;

	size_t realsize = size*nmemb;
	ProtoHTTPMem* mem = (ProtoHTTPMem*)request->writemem;

	mem->Realloc(mem->size + realsize + 2);
	if(mem->memory) {
		memcpy(&((wxByte*)mem->memory)[mem->size], ptr, realsize);
		mem->size += realsize;
		((wxByte*)mem->memory)[mem->size] = 0; // cap with two 0s just in case this is unicode (???, meh)
		((wxByte*)mem->memory)[mem->size+1] = 0;
	} else {
		// this is pretty fatal, but we can't send the errors anywhere because
		// this method is static
	}
	return realsize;
}

size_t ProtoHTTP::CurlWriteFile(void *ptr, size_t size, size_t nmemb, void *stream)
{
	ProtoHTTPRequest* request = (ProtoHTTPRequest*)stream;
	if(request->caller->IsStopped())
		return 0;

	wxFile* passthrough = (wxFile*)request->writefile;
	passthrough->Write(ptr, size*nmemb);
	return nmemb;
}

wxString ProtoHTTP::URLEncode(wxString input)
{
	const char* mbinputchar = input.ToUTF8();

	CURL *curl = curl_easy_init();
	char* encoded = curl_easy_escape(curl, mbinputchar, 0);
	wxString output = wxString::FromUTF8(encoded);
	curl_free(encoded);
	curl_easy_cleanup(curl);

	return output;
}
