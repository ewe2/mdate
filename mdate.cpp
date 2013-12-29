// vim:ts=4:sw=4
//! \file mdate.cpp
//! \brief Member functions and other utilities

//! This is actually the core of the original mtools.c and the later libmdate.c
//! with new bits added of course.
//
//! Copyright(c) under GPL 1998-2009 Sean Dwyer <ewetoo@gmail.com>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "mdate.h"

#include <cstdlib>
#include <cstring>
#include <iostream>

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

using namespace std;

//! \var VCS version
static char rcsid[] __attribute__ ((unused)) = "@(#) $Id$";

//! \def AMOD(x,y)
//! \brief Reinholt & Dershowitz augmented modulus, preventing over/underflow
#define AMOD(x,y) (1 + (((x) - 1) % (y)))

// util functions

//! \fn double my_drem(double x, double y)
//! \brief Compatible drem function for OS's without one.
//! \param x first number to compare
//! \param y second number to compare
#ifdef USE_MYDREM
static double my_drem(double x, double y)
{
	double n;

	n = x/y;
	if (n - floor(n) > .5) {
		n = floor(n + 1);
	} 
	else if (n - (int) n < .5) {
		n = floor(n);
	}
	else {
		if ((int) floor(n) % 2 == 0) {
			n = floor(n);
		} else {
			n = floor(n + 1);
		}
	}
	return x - n * y;
}
#endif


//! \fn double my_mod(double x, double y)
//! \brief Checks for a signed modulus and applies the correct function to
//! provide a positive result.
//! \param x first number to compare, may be signed or unsigned
//! \param y second number to compare, may be signed or unsigned

//! If the system has drem or remainder those functions are used.
//! If the system has no compatible function, \fn my_drem() is called
//! If the modulus is unsigned, fmod() is called.
static double my_mod(double x, double y)
{
	double result;

	if ((x < 0) && (y < 0))
		result = fmod(x, y);
	else if ((x > 0) && (y < 0))
#if defined(HAVE_DREM)
		result = drem(x, y);
#endif
#if defined(HAVE_REMAINDER)
		result = remainder(x, y);
#endif
#if defined(USE_MYDREM)
		result = my_drem(x, y);
#endif
	else if ((x < 0) && (y > 0))
#if defined(HAVE_DREM)
        result = drem(x, y);
#endif
#if defined(HAVE_REMAINDER)
        result = remainder(x, y);
#endif
#if defined(USE_MYDREM)
        result = my_drem(x, y);
#endif
	else
		result = fmod(x, y);
	
	return result;
}

// class methods

// interface to class julian data fields
bool julian::set_correlation(corr c)
{
	if (c == cor_def) {
		corr_set = 1;
		return 1;
	} 	else { // user-defined correlation
		cor_usr = c;
		corr_set = 1;
		return 1;
	}
	return 0;
}

// interface to class longdate data fields
void longdate::set_longdate(int bakk, int katk, int tunk, int uink, int kink)
{
	bak = bakk;
	kat = katk;
	tun = tunk;
	uin = uink;
	kin = kink;
}

// interface to class gregdate data fields
void gregdate::set_gregdate(int gday, int gmonth, int gyear)
{
	day = gday;
	month = gmonth;
	year = gyear;
}

// the serious stuff

// using struct tm to calculate a JDN

bool mdate::jdate_from_tm(corr c, struct tm from, julian_date *to)
{
	gregdate gddate;
	gddate.day = from.tm_mday;
	gddate.month = from.tm_mon + 1;
	gddate.year = from.tm_year + 1900;
	gddate.wday = from.tm_wday;
	if (!mdate::jdate_from_gregdate(c, gddate, to))
		return 0;
	return 1;
}

// These are the public domain Fliegel/Van Flandern JDN<>Gregorian Date
// algorithms slightly tweaked. Since we don't use fractional JDN's, it's safe
// to compute using casts to long ints.

bool mdate::gregdate_from_jdate(corr c, julian_date from, gregdate *to)
{
	int l, n, i, j;
	int day, month, year;
	double jdn;

	jdn = from;

	if (!julian::is_valid_jdate(c,from))
		return 0;
	
	l = (long)jdn + 68569;
	n = (4*l) / 146097;
	l = l - (((146097 * n) + 3) / 4);
	i = (4000 * (l + 1)) / 1461001;
	l = l - ((1461 * i) / 4) + 31;
	j = (80 * l) / 2447;
	day = l - ((2447 * j)/80);
	l = (j/11);
	month = j + 2 - (12 * l);
	year = ((100 * (n - 49)) + i + l);

	to->day = (int)day;
	to->month = (int)month;
	to->year = (int)year;
	return 1;
}


bool mdate::jdate_from_gregdate(corr c, gregdate from, julian_date *to)
{
	double j,j1,j2,j3;
	int d, m, y;

	if (!(gregdate::is_valid_gregdate(from)))
		return 0;

	m = from.month;
	y = from.year;
	d = from.day;

	// much safer than a one-liner
	j = (m - 14)/12;
	j1 = (d - 32075) + floor((1461 * (y +4800 + j) /4));
	j2 = j1 + floor((367 * (m - 2 - j * 12) /12));
	j3 = j2 - floor((3 * floor(y + 4800 + j) / 100 / 4));

	*to = j3;
	return 1;
}

// test for leap year
int gregdate::gregorian_leap_year(int g_year)
{
	return !(g_year % 100 ? g_year % 4 : g_year % 400);
}

// public domain code: zeller congruence theory
int gregdate::gregdate_weekday(gregdate from)
{
	int offs = -2;
	int dd,mm,yy,i,j;
	int weekday;
	dd = from.day; mm=from.month; yy=from.year;

	if (mm < 3) {
		mm += 12;
		yy -= 1;
	}
	
	i = (26 * (mm+1)) / 10;
	j = (int) ((125 *(long) yy) /100);

	weekday = ((dd + i + j - (yy / 100) + (yy / 400) + offs) % 7);
	return weekday;
}

// test given gregorian dates: it looks overly complicated, but the gotchas
// are surprising.
bool gregdate::is_valid_gregdate(gregdate date)
{
	static const int daysinmonth[] =
		{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	
	if (date.month < 1 || date.month > 12)
		return 0;

	if ((date.month == 2) && (!gregdate::gregorian_leap_year(date.year))
		&& (date.day > 28))
		return 0;
	
	if (date.day < 1 || date.day > daysinmonth[date.month])
		return 0;

	return 1;
}

// pretty printing version. of gregdate_tostr
void gregdate::gregdate_tostr(gregdate from, char *to)
{
	struct tm gtm = {
		12, 12, 12, from.day, from.month - 1, from.year - 1900,
		0,0,0
	};
	strftime(to, DATE_BUFSIZE, "%d-%B-%Y (%d/%m/%Y)", &gtm);
}

// program-parseable version of gregdate_tostr
void gregdate::gregdate_tostr(int pflag, gregdate from, char *to)
{
	struct tm gtm = {
		12, 12, 12, from.day, from.month - 1, from.year - 1900,
		0,0,0
	};
	strftime(to, DATE_BUFSIZE, "%d  %m  %Y", &gtm);
}

// try to pass off as much to strftime instead of all these overloaded
// functions. ripped pretty much from GNU date.c. this effectively removes the
// need for most formatting, but we'll keep the old _tostr() functions. this
// function uses memory allocation!!

// weekday is NOT calculated here, because wday gets lost
bool gregdate::gregdate_sstr(char *format, gregdate from, char *to)
{
       char *out = NULL;
       size_t out_length = 0;
       
       struct tm gtm = {
               12,12,12, from.day, from.month - 1, from.year - 1900,
               from.wday,0,0
       };

       char *default_format = "%d %m %Y";
       if (format == NULL) {
               format = default_format;
       } else if (*format == '\0') {
               return 0;
       }
       
       do {
               out_length += 200;
               out = (char *) realloc (out,out_length);
               out[0] = '\1';
       } while (strftime(to, out_length, format, &gtm) == 0 && out[0] != '\0');

       free(out);
       return 1;
}

// test given julian day number
bool julian::jdate_from_jd(corr c, double from, julian_date *to)
{
	if (!is_valid_jdate(c, from))
		return 0;
	
	*to = from;
	return 1;
}

// test julian day number against the correlation. this effectively prevents
// use of pre-JDN dates.
bool julian::is_valid_jdate(corr c, double jul)
{
	if ((jul < c) || (c > jul))
		return 0;
	
	return 1;
}

// julian date to string functions, overloaded for output formats
void julian::jdate_tostr(julian_date from, char *to)
{
	snprintf(to, DATE_BUFSIZE, "%.1f", from);
}

void julian::jdate_tostr(int pflag, julian_date from, char *to)
{
	snprintf(to, DATE_BUFSIZE, "%9.1f", from);
}


// julian date to/from longcounts. check if pre-epoch.
void mdate::jdate_from_longcount(corr c, longdate from, julian_date *to)
{
	double result;

	result = (double)  ((from.bak * 144000.0) + (from.kat * 7200.0) +
		(from.tun * 360.0) + (from.uin * 20.0) + (double) from.kin);
	
	*to = result + c;
}

// one of mdate's oldest functions, LC from JDN
bool longdate::longcount_from_jdate(corr c, julian_date from, longdate *to)
{
	double lc;
	double r;

	lc = from - c;
	if (lc < 0.0) {
		return 0;
	} else {
		to->bak = (int) floor(lc / 144000.0);
		r = my_mod(lc, 144000.0);
		to->kat = (int) floor(r / 7200);
		r = my_mod(r, 7200.0);
		to->tun = (int) floor(r / 360);
		r = my_mod(r, 360.0);
		to->uin = (int) floor(r / 20);
		to->kin = (int) my_mod(r, 20.0);
		return 1;
	}
}

void longdate::longcount_tostr(longdate from, char *to)
{
	snprintf(to, DATE_BUFSIZE, "%.2d.%.2d.%.2d.%.2d.%.2d",
			from.bak, from.kat, from.tun, from.uin, from.kin);
}

void haabdate::haabdate_from_jdate(corr c, julian_date from, haabdate *to)
{
	double doh, lc;
	int day, month;

	lc = from - c;

	doh = (int) my_mod((lc + 8.0 + 20.0 * (18.0 - 1.0)), 365.0);
	day = (int) floor(my_mod(doh, 20.0));
	month = (int)floor(doh / 20.0) + 1;

	to->day = day;
	to->month = month;
}

const char* gregdate::gregday_str(int flag, int from)
{
	if (flag > 6)
		return NULL;

	if (flag > 0)
		return days[from];
	else
		return short_days[from];
}

// test for preferred dialect also
const char* haabdate::haabmonth_str(int from)
{
	if (from > 19) {
		return NULL;
	}

#if defined(NEWMAYAN)
	return m_haab_new[from];
#endif
#if defined(OLDMAYAN)	
	return m_haab_old[from];
#endif

	return NULL;
}

bool haabdate::haabdate_tostr(haabdate from, char *to)
{
	const char *month;

	if ((month = haabmonth_str(from.month)) == NULL) {
		return 0;
	}
	snprintf(to, DATE_BUFSIZE, "%d %s", from.day, month);
	return 1;
}

bool haabdate::haabdate_tostr(int pflag, haabdate from, char *to)
{
	const char *month;

	if ((month = haabmonth_str(from.month)) == NULL) {
		return 0;
	}
	snprintf(to, DATE_BUFSIZE, "% .2d %s", from.day, month);
	return 1;
}

void tzolkindate::tzolkindate_from_jdate(corr c, julian_date from, tzolkindate *to)
{
	int number, name, ilc;
	double lc;

	lc = from - c;

	ilc = (int) floor(lc);
	number = AMOD((ilc + 4), 13);
	name = AMOD((ilc + 20), 20);

	to->month = name;
	to->day = number;
}

const char* tzolkindate::tzolkinmonth_str(int from)
{
	if (from > 20) {
		return NULL;
	}

#if defined(NEWMAYAN)
	return m_tzolkin_new[from];
#endif
#if defined(OLDMAYAN)	
	return m_tzolkin_old[from];
#endif

	return NULL;
}

bool tzolkindate::tzolkindate_tostr(tzolkindate from, char *to)
{
	const char *month;

	if ((month = tzolkinmonth_str(from.month)) == NULL) {
		return 0;
	}
	snprintf(to, DATE_BUFSIZE, "%d %s", from.day, month);
	return 1;
}

bool tzolkindate::tzolkindate_tostr(int pflag, tzolkindate from, char *to)
{
	const char *month;

	if ((month = tzolkinmonth_str(from.month)) == NULL) {
		return 0;
	}
	snprintf(to, DATE_BUFSIZE, "% .2d %s", from.day, month);
	return 1;
}

// encapsulated from main.cc back into class mdate. this is
// language-dependent!
 
void mdate::mdate_strftime(corr c, std::stringstream *to, const char *format, julian_date thedate)
{
	int	fmtlen = strlen(format);
	int	i;
	int flag=0; // don't assume we want pretty format
	int wday;
	mdate md;
	gregdate gdate;
	longdate ldate;
	haabdate hdate;
	tzolkindate tdate;

    if (!ldate.longcount_from_jdate(c, thedate,	&ldate)) {
		cerr << MSG_LONGERR;
		::exit(1);
	}

	if (!md.gregdate_from_jdate(c, thedate, &gdate)) {
		cerr << MSG_GENERR;
		::exit(1);
	}

	tdate.tzolkindate_from_jdate(c, thedate, &tdate);
	hdate.haabdate_from_jdate(c, thedate, &hdate);

	// force wday calculation: note that this cannot be counted upon for older
	// dates, due to struct tm limitations.
	wday = gdate.gregdate_weekday(gdate);

	// now format
	*to << "";

	// use '@' instead of '%' because we change some strftime() formats.
	for(i=0;i<fmtlen; ++i) {
		if(format[i]=='@') {
			char *tempdate=0, bendy[DATE_BUFSIZE];
			switch(format[++i]) {
				case 'a':
					gdate.gregdate_sstr("%a",gdate,bendy);
					snprintf(bendy, DATE_BUFSIZE, "%s", gdate.gregday_str(0,wday));
					tempdate=bendy;
					break;
				case 'A':
					gdate.gregdate_sstr("%A",gdate,bendy);
					snprintf(bendy, DATE_BUFSIZE, "%s", gdate.gregday_str(1,wday));
					tempdate=bendy;
					break;
				case 'b':
					gdate.gregdate_sstr("%b",gdate,bendy);
					tempdate=bendy;
					break;
				case 'B':
					gdate.gregdate_sstr("%B",gdate,bendy);
					tempdate=bendy;
					break;
				case 'd':
					gdate.gregdate_sstr("%d", gdate, bendy);
					tempdate=bendy;
					break;
				case 'e':
					gdate.gregdate_sstr("%e", gdate, bendy);
					tempdate=bendy;
					break;
				case 'F':
					gdate.gregdate_sstr("%F",gdate,bendy);
					tempdate=bendy;
					break;
				case 'f':
					gdate.gregdate_sstr("%Y%m%d",gdate,bendy);
					tempdate=bendy;
					break;
				case 'H': // supporting the old functions here
					hdate.haabdate_tostr(flag,hdate,bendy);
					tempdate=bendy;
					break;
				case 'h':
					hdate.haabdate_tostr(hdate,bendy);
					tempdate=bendy;
					break;
				case 'J':
					snprintf(bendy, DATE_BUFSIZE,"%.1f", thedate);
					tempdate=bendy;
					break;
				case 'l':
					ldate.longcount_tostr(ldate, bendy);
					tempdate=bendy;
					break;
				case 'M':
					gdate.gregdate_sstr("%B",gdate,bendy);
					tempdate=bendy;
					break;
				case 'm':
					gdate.gregdate_sstr("%m",gdate,bendy);
					tempdate=bendy;
					break;
				case 'T': // supporting the old functions here too.
					tdate.tzolkindate_tostr(tdate,bendy);
					tempdate=bendy;
					break;
				case 't':
					tdate.tzolkindate_tostr(flag,tdate,bendy);
					tempdate=bendy;
					break;
				case 'y':
					gdate.gregdate_sstr("%y",gdate,bendy);
					tempdate=bendy;
					break;
				case 'Y':
					gdate.gregdate_sstr("%Y",gdate,bendy);
					tempdate=bendy;
					break;
				case 'n': *to << "\n"; break;
				case 'j': *to << "\t"; break; // use a spare identifier
				default:
					cerr << MSG_FORMATERR;
					break;
			}
			if(tempdate) {
				*to << tempdate;
			}
		} else {
			*to << format[i];
		}
 	}
}

// also moved from main.cc to class mdate. makes sense. this is
// language-dependent!

bool mdate::set_time(corr c, julian_date *to)
{
	struct tm *today;
	time_t t;	// bitter complaints from FreeBSD if cast to long
	mdate md;

	t = time(NULL);
	today = localtime(&t);
	if (!md.jdate_from_tm(c, *today, to)) {
		cerr << MSG_GENERR;
		return 0;
	}
	return 1;
}

// end of mdate.cc
