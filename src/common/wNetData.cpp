#include "prec.h"
#include "wNetData.h"

wNetData wNetDataSafe::data;

wNetData::wNetData()
{
	// FETCH

	fetch_timeout = 10;
	fetch_speedlimit = REFRESH_FETCH_SPEEDLIMIT;
	fetch_url = REFRESH_FETCH_URL;

	fetch_reset = false;
	fetch_turbo = 5;
	fetch_lastattempt = 0;
	fetch_lastsuccess = 0;

	// PUSH

	push_timeout[0] = 10;
	push_timeout[1] = 10;
	push_timeout[2] = 60;
	push_speedlimit = 0;
	push_host = "";
	push_port = 0;

	push_reset = false;
	push_turbo = 0;
	push_lastattempt = 0;
	push_lastsuccess = 0;
	push_connecting = false;
	push_connected = false;
}
