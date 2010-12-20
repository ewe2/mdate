// mdate.h - class defs for mdate++
// Copyright(c) under GPL 1998-2009 Sean Dwyer <ewe2@users.sourceforge.net>

// $Id: mdate.h 30 2010-12-04 12:00:35Z ewe2 $

#ifndef _mdate_h
#define _mdate_h

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <string.h>
#include <sstream>

#ifdef HAVE_UNISTD_H
#  include <sys/types.h>
#  include <unistd.h>
#endif

#ifdef TIME_WITH_SYS_TIME
#  include <sys/time.h>
#  include <time.h>
#else
#  ifdef HAVE_SYS_TIME_H
#    include <sys/time.h>
#  else
#    include <time.h>
#  endif
#endif

#include <cmath>

#ifdef USE_I18N
#include <libintl.h>
#include <locale.h>
#define md_gettext(String) gettext(String)
#else
#define md_gettext(String) String
#endif

// Mayan and language-dependent day/month names
#include "names.h"

// size of temporary date string buffer (should be enough to contain any date
// as string)
#define DATE_BUFSIZE 1024

// required here for translation support across all modules
#include "lang.h"

// this is outdated in g++ terms, but may still be needed for older compilers
//typedef enum {FALSE, TRUE} bool;
typedef double julian_date;
typedef double corr;

//forward defs
class mdate;
class longdate;
class gregdate;
class haabdate;
class tzolkindate;
class julian;

// class defs
class longdate {
public:
	//constructor
	longdate(void);
	
	// friends
	friend class gregdate;
	friend class julian;
	friend class mdate;

	// methods
	void longcount_tostr(longdate from, char *to);
	bool longcount_from_jdate(corr c, julian_date from, longdate *to);
	void set_longdate(int bak, int kat, int tun, int uin, int kin);

// data fields
private:
	int bak, kat, tun, uin, kin;
};

inline longdate::longdate(void)
{
	bak = kat = tun = uin = kin = 0;
}

// note that wday is ONLY used in formatting, and isn't required for most
// uses.
class gregdate {
public:
	//constructor
	gregdate(void);
	
	// friends
	friend class mdate;
	
	//methods
	int gregorian_leap_year(int g_year);
	int gregdate_weekday(gregdate from);
	bool is_valid_gregdate(gregdate date);
	void set_gregdate(int day, int month, int year);
	void gregdate_tostr(gregdate from, char *to);
	void gregdate_tostr(int pflag, gregdate from, char *to);
	bool gregdate_sstr(char *format, gregdate from, char *to);
	const char* gregday_str(int flag, int from);

// data fields
private:
	int day, month, year, wday;
};

inline gregdate::gregdate(void)
{
	day = month = year = wday = 0;
}

class haabdate {
public:
	//constructor
	haabdate(void);

	// methods
	void haabdate_from_jdate(corr c, julian_date from, haabdate *to);
	const char* haabmonth_str(int from);
	bool haabdate_tostr(haabdate from, char *to);
	bool haabdate_tostr(int pflag, haabdate from, char *to);

// data fields
private:
	int month, day;
};

inline haabdate::haabdate(void)
{
	month = day = 0;
}

class tzolkindate {
public:
	//constructor
	tzolkindate(void);

	// methods
	void tzolkindate_from_jdate(corr c, julian_date from, tzolkindate *to);
	const char* tzolkinmonth_str(int from);
	bool tzolkindate_tostr(tzolkindate from, char *to);
	bool tzolkindate_tostr(int pflag, tzolkindate from, char *to);

// data fields
private:
	int month, day;
};

inline tzolkindate::tzolkindate(void)
{
	month = day = 0;
}

class julian {
public:
	//constructor
	julian(void);
	
	// friends
	friend class mdate;
	friend class longdate;

	// set this when we've decided on a correlation.
	// this is public because we want to be able to test it in commandline
	// parsing.
	bool corr_set;

	// methods
	bool jdate_from_jd(corr c, double from, julian_date *to);
	bool is_valid_jdate(corr c, double jul);
	void jdate_tostr(julian_date from, char *to);
	void jdate_tostr(int pflag, julian_date from, char *to);
	bool set_correlation(corr c);

// data fields
private:
	// couple of standard correlations, plus a spare one for the weird users.
	corr cor_def;
	corr cor_gmt;
	corr cor_usr;
};

// gmt is now default, the -g option is ignored.
inline julian::julian(void)
{
	cor_def = 584283.0L;
	cor_gmt = 584283.0L;
	// cor_usr is uninitialised so it can be set
	corr_set = 0;
}

class mdate : public longdate, gregdate, haabdate, tzolkindate, julian {
public:
	//constructor
	mdate(void);
	// destructor
	// copy constructor
	
	// public display flag
	int pflag;
	
	// inheritance-dependent methods
	bool gregdate_from_jdate(corr c, julian_date from, gregdate *to);
	bool jdate_from_gregdate(corr c, gregdate from, julian_date *to);
	bool jdate_from_tm(corr c, struct tm from, julian_date *to);
	void jdate_from_longcount(corr c, longdate from, julian_date *to);
	void mdate_strftime(corr c, std::stringstream *to, const char *format, julian_date thedate);
	bool set_time(corr c, julian_date *to);
};

// constructor calls all parent constructors
inline mdate::mdate(void)
{
	pflag = 0;
	longdate();
	gregdate();
	haabdate();
	tzolkindate();
	julian();
}

#endif // _mdate.h
