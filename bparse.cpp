// bparse.cpp - use libboost_program_options to simplify commandline parsing
// and configuration file handling.
//
//

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

// test output
#ifdef TEST
#endif
