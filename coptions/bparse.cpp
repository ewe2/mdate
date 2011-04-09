// bparse.cpp - use libboost_program_options to simplify commandline parsing
// and configuration file handling.
// Copyright (c) under GPLv2 2011 Sean Dwyer <ewetoo@gmail.com>
// $Id$

#include <boost/program_options.hpp>
namespace mo = boost::program_options;

#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define STATIC_HELP
#include "mdate.h"

using namespace std;
namespace mo = boost::program_options;

// lets us simply copy strings.
template<class T>
ostream& operator<<(ostream& os, const vector<T>&v)
{
	copy(v.begin(), v.end(), ostream_iterator<T>(cout, " "));
	return os;
}

void version(void)
{
	cout << PACKAGE << " " << VERSION << endl;
	cout << "Copyright (c) 1998-2011 Sean Dwyer <ewetoo@gmail.com>" << endl;
}

// Parser code. In order to support our language scheme, we have to catch our
// own exceptions, and output our own messages.

int parseit(int argc, char *argv[])
{
	string config_file;
	double corr;
	double julian;
	int gmt;

	// Because these are vectors, we can do different stuff with the options.
	// if we cast to string, we can do things the old way, escaping values and
	// then casting back to int. Or we just have boost do the cast directly
	// for us.
	vector<int> longcount;
	vector<int> dmy;
	vector<string> fmt;

	//format needs to be both a positional argument and a config file
	//argument.

	// minimum options
	mo::options_description basic("Mdate options");
	basic.add_options()
		("version,V","print version string")
		("help,h","print help")
		("config,m",mo::value<string>(&config_file)->default_value("mdaterc"),
		 	"name of configuration file.")
		;

	// configfile options
	mo::options_description config("configuration");
	config.add_options()
		("correlation,c",mo::value<double>(&corr)->default_value(584283.0),	"default correlation")
		("language,L",mo::value<string>()->default_value("en"),"change language (default en)")
		("format,f",mo::value<vector <string> >(&fmt),"format string");

	mo::options_description date("date options");
	date.add_options()
		("julian,j",mo::value<double>(&julian), "julian date")
		("dmy,d",mo::value< vector<int> >(&dmy)->multitoken(),"day month year")
		("longcount,l",mo::value<vector <int> >(&longcount)->multitoken(),"long count");


	mo::options_description cmdline_options;
	cmdline_options.add(basic).add(config).add(date);
	mo::options_description config_file_options;
	config_file_options.add(config);

	// this will work, but ONLY at the end of a commandline argument and ONLY
	// because of logic defining the the limits of other arguments.
	mo::positional_options_description p;
	p.add("format",-1);

	mo::variables_map vm;
	mo::parsed_options parsed = mo::command_line_parser(argc,argv).options(cmdline_options).positional(p).run();
	mo::store(parsed,vm);
	mo::notify(vm);

	// basic config file handling. we need to provide for Windows users also.
	ifstream ifs(config_file.c_str());
	if (!ifs) {
		cout << "error: cannot open config file: " << config_file << endl;
		return 0;
	} else {
		mo::store(parse_config_file(ifs, config_file_options),vm);
		mo::notify(vm);
	}

	// at this point we're just validating options. the parser automatically
	// validates data given to the option so we can save a bit of logic in
	// main() Ideally we'll pass vm to another function with this in it.
	//
	// don't forget to use positional to output a default date, as if we used
	// -d with a default value of today.
	try {
		if (vm.count("help")) {
			version();
//			cout << helptext << endl;
			cout << basic << endl;
			cout << config << endl;
			cout << date << endl;
			return 0;
		}

		if (vm.count("version")) {
			cout << "Mdate v1.7.0" << endl;
			cout << "Copyright (c) Sean Dwyer 2011" << endl;
			return 0;
		}

		if (vm.count("correlation")) {
			cout << "correlation set to " << corr << endl;
		} else {
			cout << "correlation not set." << endl;
		}
		
		if (vm.count("gmt")) {
			cout << "gmt set " << gmt << endl;
		} else {
			cout << "gmt not set." << endl;
		}

		// these two are effectively tokenized so we can easily pass them on
		// to their functions
		// note simple logic to avoid tokenizing errors. the alternative is to
		// override class typed_value just to use min_ and max_ tokens().
		if (vm.count("dmy")){
			if ((dmy.size() > 3|| dmy.size() < 3)) {
				cout << "error: -d requires 3 arguments" << endl;
				::exit(1);
			} else {
				cout << "day month year is " << dmy << endl;
			}
		}
		if (vm.count("longcount")) {
			if ((longcount.size() > 5 || longcount.size() < 5)) {
				cout << "error: -l requires 5 arguments" << endl;
				::exit(1);
			} else {
				cout << "long count is " << longcount << endl;
			}
		}
		
		// all the work is done in mdate_strftime()
		// the only issue with this is that
		if (vm.count("format")) {
			cout << "format is " << fmt << endl;
		} else {
			cout << "no format set." << endl;
		}
	}
	catch(exception &e) {
		cerr << "error: " << e.what() << endl;
	}

	return 0;
}

// test output
#ifdef TEST
int main(int argc, char *argv[])
{
	parseit(argc,argv);
	return 0;
}
#endif
