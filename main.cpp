// vim:ts=4:sw=4
// main.cc : commandline driver for mdate++
//
// Copyright(c) under GPL 1998-2009 Sean Dwyer <ewe2@users.sourceforge.net>

#ifdef NEED_INCLUDED_GETOPT
#include "getopt.h"
#else
#include <getopt.h>
#endif

#include <cstdio>
#include <iostream>

#include "mdate.h"
#include "cmdline.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

using namespace std;

static char rcsid[] __attribute__ ((unused)) = "@(#) $Id$";

// the massive big ooooge main thingy. this is all we do here, everything else
// has been folded into other files.
 
// there is one option, runtime language (-L) support, that is not tested for
// use here, it's transparent. This could be a problem later.
 
int main (int argc, char *argv[])
{
	mdate md;
	gregdate gdate;
	longdate ldate;
	julian jdate;
	julian_date thedate;
	double cor;
	const char *datey=0;
	std::stringstream buffy;

#ifdef USE_I18N
	setlocale(LC_ALL,"");
	bindtextdomain("mdate", LOCALEDIR);
	textdomain("mdate");
#endif

	struct gengetopt_args_info args_info;

	// run the parser
	if (cmdline_parser(argc, argv, &args_info) != 0)
		::exit(1);
	
	// check misc. options
	if (args_info.help_given)
		cmdline_parser_print_help();
	if (args_info.version_given)
		cmdline_parser_print_version();

	// if we didnt get a date option, process for today's date
	if ((!args_info.dmy_given) && 
		(!args_info.julian_given) &&
		(!args_info.longcount_given)){
		
		// set up the correlation. silently ignore gmt option
		// this should be a conf file option
		if (args_info.correlation_given)
			cor = args_info.correlation_arg;
		else
			cor = 584285.0;
		
		jdate.set_correlation(cor);
		
		// today's date
		if (!md.set_time(cor, &thedate)) {
			cerr << MSG_GENERR;
			::exit(1);
		}
			
		
		// output according to format, this is a non-option argument so exit
		// here when done.
		if (args_info.format_given) {
			datey = args_info.format_arg;
			md.mdate_strftime(cor, &buffy, datey, thedate);

			cout << buffy.str() << endl;
 			::exit(0);
		}
		
		datey=default_format;
		md.mdate_strftime(cor,&buffy,datey,thedate);
		cout << buffy.str() << endl;

	} else {
		// we got a -d, -j or -l option
		// process correlation first
		if (args_info.correlation_given)
			cor = args_info.correlation_arg;
		else if (args_info.gmt_given)
			cor = 584283.0;
		else
			cor = 584285.0;
		jdate.set_correlation(cor);
		
		// process -d
		// dates are expected to be in "dd mm [-]yyyy" format
		if (args_info.dmy_given == 1) {
			int day, month, year;
			day = args_info.dmy_arg1;
			month = args_info.dmy_arg2;
			year = args_info.dmy_arg3;
			gdate.set_gregdate(day, month, year);
			if (!md.jdate_from_gregdate(cor, gdate, &thedate)) {
				cerr << MSG_IGD;
				::exit(1);
			}
		}
		// process -j
		// jdn's are expected in double format
		else if (args_info.julian_given) {
			double j;
			j = args_info.julian_arg;
			if (!jdate.jdate_from_jd(cor, j, &thedate)) {
				cerr << MSG_IJDN;
				::exit(1);
			}
		}
		// process -l
		// longcounts are expected in "00 00 00 00 00" format
		else if (args_info.longcount_given) {
			int ba,ka,tu,ui,ki;
			ba = args_info.longcount_arg1;
			ka = args_info.longcount_arg2;
			tu = args_info.longcount_arg3;
			ui = args_info.longcount_arg4;
			ki = args_info.longcount_arg5;
			ldate.set_longdate(ba,ka,tu,ui,ki);
			md.jdate_from_longcount(cor, ldate, &thedate);
		}
	}
 
	return 0;
}
