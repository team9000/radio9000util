#pragma once

#define VER_MAJOR		1
#define VER_MINOR		0
#define VER_REVISION	0
#define VER_STAGE		.

/*
#ifdef __WXMAC__
#include "../../build/osx/build/hgversion.h"
#else
#include "../../build/msw/build/hgversion.h"
#endif
*/

#define _WQUOTEME(x) #x
#define WQUOTEME(x) _WQUOTEME(x)

#define APP_VERSION VER_MAJOR,VER_MINOR,VER_REVISION,0
#define APP_VERSION_STR WQUOTEME(VER_MAJOR) "." WQUOTEME(VER_MINOR) WQUOTEME(VER_STAGE) WQUOTEME(VER_REVISION)

// Mac Package Versions
#define MACRO_PASTE_6(a, b, c, d, e, f) a##b##c##d##e##f
#define MACRO_PASTE_6A(a, b, c, d, e, f) MACRO_PASTE_6(a, b, c, d, e, f)
#define VER_MAC_CFBUNDLE MACRO_PASTE_6A(VER_MAJOR, ., VER_MINOR, ., VER_REVISION, VER_STAGE)
#define VER_MAC_CFBUNDLE_BUILD HgGlobalRevision
