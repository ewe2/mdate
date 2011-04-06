// DEFAULT TRANSLATION.
// Things that are NOT translatable:
// at present, NO Mayan names, printf formats, program options or CVS ids!!
 
// English translation strings. 
// This file follows the mplayer translation string system. Please add the
// version your translation is synced for below to help keep things updated.
 
// version 1.5.0
// $Id$

// ============================= Mdate help ===============================

#ifdef STATIC_HELP
static char en_helptext[] __attribute__ ((unused)) =
"\n"
"Mdate outputs simple Mayan dates.\n"
"Usage: mdate [OPTION]... [+FORMAT]\n"
"   -h, --help                Print help and exit\n"
"   -V, --version             Print version and exit\n"
"   -p, --parseable           program-parseable output (default=off)\n"
"   -g, --gmt                 use gmt correlation (default=on)\n"
"   -L, --lang=LANGUAGE       change language (default en)\n"
"   -c, --correlation=DOUBLE  optional correlation (default=no)\n"
"   -d, --dmy=STRING          day month year (Gregorian)\n"
"   -j, --julian=DOUBLE       julian day number\n"
"   -l, --longcount=STRING    long count\n"
"\n"
"Valid LANGUAGE identifiers are:\n"
"  en English\n"
"  es Spanish\n"
"  pl Polish\n"
"  de German\n"
"  fr French\n"
"\n"
"Valid FORMAT identifiers are:\n"
"  @a abbreviated weekday name\n"
"  @A full weekday name\n"
"  @b abbreviated month name\n"
"  @B full month name\n"
"  @d weekday (01..31)\n"
"  @e weekday without a leading zero \n"
"  @F ISO format Gregorian date (%Y-%m-%d)\n"
"  @f ISO format Gregorian date (%Y%m%d)\n"
"  @h unpadded Haab date\n"
"  @H padded Haab date\n"
"  @l Long Count\n"
"  @M named Gregorian month\n"
"  @m numbered Gregorian month\n"
"  @T padded Tzolkin date\n"
"  @t unpadded Tzolkin date\n"
"  @y year as decimal 00 to 99\n"
"  @Y Gregorian year\n"
"  @n add a newline to the output\n"
"  @j add a tab to the output\n"
"\n";
#endif

// ============================= Mdate messages ===========================

const char* EN_MSG_CERR = "Mdate: `--correlation' (`-c') option given more than once\n";
const char* EN_MSG_DERR = "Mdate: `--dmy' (`-d') option given more than once\n";
const char* EN_MSG_JERR = "Mdate: `--julian' (`-j') option given more than once\n";
const char* EN_MSG_LERR = "Mdate: `--longcount' (`-l') option given more than once\n";
const char* EN_MSG_OPTERR = "Mdate: option unknown: ";
const char* EN_MSG_NONOPTERR = "Too many non-option arguments!\n";
const char* EN_MSG_LONGERR = "Invalid LongCount specified!\n";
const char* EN_MSG_GENERR = "error!\n";
const char* EN_MSG_ILC = "Invalid Long Count entered!\n";
const char* EN_MSG_IGD = "Invalid Gregorian Date entered!\n";
const char* EN_MSG_IJDN = "Invalid Julian Day Number entered!\n";
const char* EN_MSG_FORMATERR = "Unknown format!\n";

// ============================= Mdate formats ============================

static char en_pretty_format[] __attribute__ ((unused)) =
"\n"
"Gregorian Date     : @d-@B-@Y (@d/@m/@Y)\n"
"Julian Day Number  : @J\n"
"Long Count         : @l\n"
"Tzolkin Date       : @T\n"
"Haab Date          : @h\n";

static char en_default_format[] __attribute__ ((unused)) = "JDN: @J date: @d @m @Y  @l @T @H";

// ============================= Mdate days ===============================

static const char *en_short_days[] __attribute__ ((unused)) = {
	"Mon","Tues","Wed","Thur","Fri","Sat","Sun"
};

static const char *en_days[] __attribute__ ((unused)) = {
	"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"
};
