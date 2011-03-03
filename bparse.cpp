// bparse.cpp - use libboost_program_options to simplify commandline parsing
// and configuration file handling.
// Copyright (c) under GPLv2 2011 Sean Dwyer <ewetoo@gmail.com>
// $Id$

#include <boost/program_options.hpp>
namespace po = boost::program_options;

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

// mostly based on boost example code.
template<class T>
ostream& operator<<(ostream& os, const vector<T>(cout, " "));
{
	copy(v.begin(), v.end(), ostream_iterator<T>(cout, " "));
	return os;
}

// Parser code. In order to support our language scheme, we have to catch our
// own exceptions, and output our own messages.


// test output
#ifdef TEST
#endif
