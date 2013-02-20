#pragma once

#pragma warning (disable: 4100)

//#include <wx/wxprec.h>
#include <wx/wx.h>
#include <wx/socket.h>
#include <wx/arrimpl.cpp> // needed for object arrays to work
#include <wx/file.h>
#include <wx/ffile.h>
#include <wx/snglinst.h>
#include <wx/ipc.h>
#include <wx/uri.h>
#include <wx/stdpaths.h>
#include <wx/display.h>
#include <wx/wfstream.h>
#include <wx/dir.h>
#include "libs.h"
#include "config.h"

#ifdef _UNICODE
#define BASS_AUTO_UNICODE BASS_UNICODE
#else
#define BASS_AUTO_UNICODE 0
#endif

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK ,__FILE__, __LINE__)
#define new DEBUG_NEW
#else
#define DEBUG_NEW new
#endif
