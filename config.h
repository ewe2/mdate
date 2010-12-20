/* config.h - part of Mdate++
 * Rewritten September 2003 to clarify further porting issues.
 * Copyright (C) under GPL 2003-2009 Sean Dwyer <ewe2@users.sourceforge.net>
 */

/* $Id: config.h 30 2010-12-04 12:00:35Z ewe2 $ */

/* There are probably massive issues regarding architectures and this file.
 * mdate (in the _very_ early days) was ported to sparc, ppc and alpha
 * architectures by Debian (it was last included in woody), but I have no
 * record of what changes would have been needed, as the debianization didn't
 * diff the respective config.h's. At the least consider endianness and
 * differences fo math precision.
 */

#ifndef __config_h
#define __config_h

#ifdef __cplusplus
extern "C" {
#endif

/* there used to be version ifdefs here, this is now taken care of in the
 * Makefile
 */

/* some OS-specific stuff */
#ifdef __BEOS__
	#define PREFIX "/boot/home/config"
#else
	#define PREFIX "/usr"
#endif

/* WARNING: this may be different on your -nix or dist! */
#define LOCALEDIR "PREFIX/share/locale"

/* don't use i18n on doze platforms. we still have cross-compiler problems
 * with the getopt_long() function grr. HAVE_REMAINDER is another option for
 * some *nixen types, but we aren't ported to them as far as I know.
 */

#if defined __linux__ || defined __BEOS__
	#define HAVE_DREM 1
	#define USE_I18N 1
	#define HAVE_GETOPT_LONG 1
	#define HAVE_UNISTD_H 1
	#define HAVE_TZSET 1
	#define TIME_WITH_SYS_TIME 1
	#define HAVE_STRING_H 1
	#undef USE_MYDREM
	#undef HAVE_REMAINDER
#endif

/* currently these are the only doze targets considered. don't expect cygwin
 * to work */
#if defined __MINGW32__ || defined __WIN32__
	#define USE_MYDREM 1
	#define NEED_INCLUDED_GETOPT 1
	#define HAVE_STRING_H 1
	#undef USE_I18N
#endif

/* freebsd has drem, but its only a wrapper for remainder */
#if defined __FreeBSD__
       #undef HAVE_DREM
       #define HAVE_STRING_H 1
       #define HAVE_GETOPT_LONG 1
       #define HAVE_UNISTD_H 1
       #define USE_I18N 1
       #define HAVE_TZSET 1
       #define TIME_WITH_SYS_TIME 1
       #define HAVE_REMAINDER 1
       #undef USE_MYDREM
#endif

/* OS X requirements */
#if defined IS_OSX
       #define HAVE_GETOPT_LONG 1
       #define HAVE_REMAINDER 1
       #undef HAVE_DREM
       #undef USE_MYDREM
       #undef NEED_INCLUDED_GETOPT
#endif

/* these are mostly linux/gnu-reliant defs. I assume BeOS and OS X can cope
 * with them.
 */

#ifdef USE_I18N
	#define USE_SETLOCALE 1
	#define ENABLE_NLS 1
	#define HAVE_GETTEXT 1
	#define HAVE_LC_MESSAGES 1
	#define HAVE_ICONV 1
	#define ICONV_CONST
	#define HAVE_LIBINTL 1
	#define HAVE_LIBINTL_H 1
	#define HAVE_LOCALE_H 1
#endif

/* A decent ANSI compilant compiler will include these, but you may not be so
 * lucky...realloc is vital, and should be defined anyway if you have stdlib.h
 */

#define HAVE_SNPRINTF 1
#define HAVE_STRFTIME 1
#define HAVE_MATH_H 1
#define HAVE_STDLIB_H 1
#define STDC_HEADERS 1
#define HAVE_REALLOC 1

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __config.h */
