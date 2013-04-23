/* winlean.h - Standard "lean" windows include

   Copyright 2010, 2011, 2012, 2013 Red Hat, Inc.

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef _WINLEAN_H
#define _WINLEAN_H 1
#define WIN32_LEAN_AND_MEAN 1

/* Mingw64 */
#define _WINNLS_
#define _WINNETWK_
#define _WINSVC_
#define _ADVAPI32_
#define _DSGETDCAPI_
#define _GDI32_
#define _KERNEL32_
#define _OLE32_
#define _SHELL32_
#define _SPOOL32_
#define _USER32_
#define _WINMM_
#define WINIMPM
#define WINSOCK_API_LINKAGE

/* Windows headers define a couple of annoyingly intrusive macros for the
   sole purpose of inline documentation.  Since they are defined without
   respect for the namespace and not undef'ed anymore, they tend to collide
   with otherwise innocent definitions in the application.  We check if they
   exist and if not, we undef them again after including the Windows headers. */
#ifndef IN
#define __undef_IN
#endif
#ifndef OUT
#define __undef_OUT
#endif
#ifndef OPTIONAL
#define __undef_OPTIONAL
#endif
#ifndef NOTHING
#define __undef_NOTHING
#endif
#ifndef CRITICAL
#define __undef_CRITICAL
#endif

#include <windows.h>
#include <wincrypt.h>
#include <lmcons.h>
#include <ntdef.h>

/* Temporary kludge for missing flag in Mingw64's w32api. */
#ifndef PIPE_REJECT_REMOTE_CLIENTS
#define PIPE_REJECT_REMOTE_CLIENTS 8
#endif

#ifdef __undef_IN
#undef IN
#endif
#ifdef __undef_OUT
#undef OUT
#endif
#ifdef __undef_OPTIONAL
#undef OPTIONAL
#endif
#ifdef __undef_NOTHING
#undef NOTHING
#endif
#ifdef __undef_CRITICAL
#undef CRITICAL
#endif

#undef _WINNLS_
#undef _WINNETWK_
#undef _WINSVC_

/* When Terminal Services are installed, the GetWindowsDirectory function
   does not return the system installation dir, but a user specific directory
   instead.  That's not what we have in mind when calling GetWindowsDirectory
   from within Cygwin.  So we redefine GetWindowsDirectory to something
   invalid here to avoid that it's called accidentally in Cygwin.  Don't
   use this function.  Use GetSystemWindowsDirectoryW. */
#define GetWindowsDirectoryW dont_use_GetWindowsDirectory
#define GetWindowsDirectoryA dont_use_GetWindowsDirectory
#endif /*_WINLEAN_H*/
