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

#define VERSION "1.7.0"

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
	cout << "Mdate " << VERSION << "\n";
}

// Parser code. In order to support our language scheme, we have to catch our
// own exceptions, and output our own messages.

int parseit(int argc, char *argv[])
{
	string config_file;
	double corr;

	// minimum options
	mo::options_description basic("Mdate options");
	basic.add_options()
		("version,v","print version string")
		("help,h","print help")
		("config,m",mo::value<string>(&config_file)->default_value("mdaterc"),
		 	"name of configuration file.")
		;

	// configfile options
	mo::options_description config("configuration");
	config.add_options()
		("correlation,c",mo::value<double>(&corr)->default_value(585283.0),
		 	"default correlation")
		;

	mo::options_description cmdline_options;
	cmdline_options.add(basic).add(config);
	mo::options_description config_file_options;
	config_file_options.add(config);


	mo::variables_map vm;
	mo::parsed_options parsed = mo::command_line_parser(argc,argv).options(cmdline_options).allow_unregistered().run();
	mo::store(parsed,vm);
	mo::notify(vm);

	try {
		if (vm.count("help")) {
			version();
			cout << basic << "\n";
			return 0;
		}

		if (vm.count("version")) {
			cout << "Mdate v1.7.0" << "\n";
			cout << "Copyright (c) Sean Dwyer 2011" << "\n";
			return 0;
		}

		if (vm.count("correlation")) {
			cout << "correlation set to " << corr << ".\n";
		} else {
			cout << "compression not set." << "\n";
		}
	}
	catch(exception &e) {
		cerr << "error: " << e.what() << "\n";
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
