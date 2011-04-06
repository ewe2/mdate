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
	// this is just for testing. we really don't want anything hardcoded in
	// here, its just to parse the options, we'll validate later.
	double corr;
	double julian;

	// Because these are vectors, we can do different stuff with the options.
	// if we cast to string, we can do things the old way, escaping values and
	// then casting back to int. Or we just have boost do the cast directly
	// for us.
	vector<int> longcount;
	vector<int> dmy;

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
		("correlation,c",mo::value<double>(&corr)->default_value(585283.0),	"default correlation")
		("language,L",mo::value<string>()->default_value("en"),"change language (default en)")
		("gmt,g",mo::value<int>()->default_value(1),"use gmt (default on)");

	mo::options_description date("date options");
	date.add_options()
		("julian,j",mo::value<double>(&julian), "julian date")
		("dmy,d",mo::value< vector<int> >(&dmy)->multitoken(),"day month year")
		("longcount,l",mo::value<vector <int> >(&longcount)->multitoken(),"long count");


	mo::options_description cmdline_options;
	cmdline_options.add(basic).add(config).add(date);
	mo::options_description config_file_options;
	config_file_options.add(config);

	mo::positional_options_description p;
	p.add("gmt",1).add("dmy",1).add("longcount",1).add("correlation",1);

	mo::variables_map vm;
	mo::parsed_options parsed = mo::command_line_parser(argc,argv).options(cmdline_options).positional(p).run();
	mo::store(parsed,vm);
	mo::notify(vm);

	// at this point we're just validating options. the parser automatically
	// validates data given to the option so we can save a bit of logic in
	// main() Ideally we'll pass vm to another function with this in it.
	//
	// don't forget to use positional to output a default date, as if we used
	// -d with a default value of today.
	try {
		if (vm.count("help")) {
			version();
			cout << helptext << endl;
//			cout << basic << endl;
//			cout << config << endl;
//			cout << date << endl;
			return 0;
		}

		if (vm.count("version")) {
			cout << "Mdate v1.7.0" << "\n";
			cout << "Copyright (c) Sean Dwyer 2011" << endl;
			return 0;
		}

		if (vm.count("correlation")) {
			cout << "correlation set to " << corr << endl;
		} else {
			cout << "compression not set." << endl;
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
