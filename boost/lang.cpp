// vim:ts=4:sw=4
// lang.cc : derived from runtime language support (c)2003 by Shard
// <shard@>
//
// Copyright (c) under GPL 1998-2011 Sean Dwyer <ewe2@users.sourceforge.net>

static char rcsid[] __attribute__ ((unused)) = "@(#) $Id$";

#include "lang.h"

// include your header file here.
#define STATIC_HELP
#include "en.h"
#include "es.h"
#include "pl.h"
#include "de.h"
#include "fr.h"
#include "names.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

using namespace std;

// these are defaults (ie default language is C/en)

#ifdef DEF_EN
const char* helptext = en_helptext;
const char* MSG_CERR = EN_MSG_CERR;
const char* MSG_DERR = EN_MSG_DERR;
const char* MSG_JERR = EN_MSG_JERR;
const char* MSG_LERR = EN_MSG_LERR;
const char* MSG_OPTERR = EN_MSG_OPTERR;
const char* MSG_NONOPTERR = EN_MSG_NONOPTERR;
const char* MSG_LONGERR = EN_MSG_LONGERR;
const char* MSG_GENERR = EN_MSG_GENERR;
const char* MSG_ILC = EN_MSG_ILC;
const char* MSG_IGD = EN_MSG_IGD;
const char* MSG_IJDN = EN_MSG_IJDN;
const char* MSG_FORMATERR = EN_MSG_FORMATERR;
const char* pretty_format = en_pretty_format;
const char* default_format = en_default_format;
const char** short_days = en_short_days;
const char** days = en_days;
#endif

#ifdef DEF_DE
const char* helptext = de_helptext;
const char* MSG_CERR = DE_MSG_CERR;
const char* MSG_DERR = DE_MSG_DERR;
const char* MSG_JERR = DE_MSG_JERR;
const char* MSG_LERR = DE_MSG_LERR;
const char* MSG_OPTERR = DE_MSG_OPTERR;
const char* MSG_NONOPTERR = DE_MSG_NONOPTERR;
const char* MSG_LONGERR = DE_MSG_LONGERR;
const char* MSG_GENERR = DE_MSG_GENERR;
const char* MSG_ILC = DE_MSG_ILC;
const char* MSG_IGD = DE_MSG_IGD;
const char* MSG_IJDN = DE_MSG_IJDN;
const char* MSG_FORMATERR = DE_MSG_FORMATERR;
const char* pretty_format = de_pretty_format;
const char* default_format = de_default_format;
const char** short_days = de_short_days;
const char** days = de_days;
#endif

#ifdef DEF_ES
const char* helptext = es_helptext;
const char* MSG_CERR = ES_MSG_CERR;
const char* MSG_DERR = ES_MSG_DERR;
const char* MSG_JERR = ES_MSG_JERR;
const char* MSG_LERR = ES_MSG_LERR;
const char* MSG_OPTERR = ES_MSG_OPTERR;
const char* MSG_NONOPTERR = ES_MSG_NONOPTERR;
const char* MSG_LONGERR = ES_MSG_LONGERR;
const char* MSG_GENERR = ES_MSG_GENERR;
const char* MSG_ILC = ES_MSG_ILC;
const char* MSG_IGD = ES_MSG_IGD;
const char* MSG_IJDN = ES_MSG_IJDN;
const char* MSG_FORMATERR = ES_MSG_FORMATERR;
const char* pretty_format = es_pretty_format;
const char* default_format = es_default_format;
const char** short_days = es_short_days;
const char** days = es_days;
#endif

#ifdef DEF_PL
const char* helptext = pl_helptext;
const char* MSG_CERR = PL_MSG_CERR;
const char* MSG_DERR = PL_MSG_DERR;
const char* MSG_JERR = PL_MSG_JERR;
const char* MSG_LERR = PL_MSG_LERR;
const char* MSG_OPTERR = PL_MSG_OPTERR;
const char* MSG_NONOPTERR = PL_MSG_NONOPTERR;
const char* MSG_LONGERR = PL_MSG_LONGERR;
const char* MSG_GENERR = PL_MSG_GENERR;
const char* MSG_ILC = PL_MSG_ILC;
const char* MSG_IGD = PL_MSG_IGD;
const char* MSG_IJDN = PL_MSG_IJDN;
const char* MSG_FORMATERR = PL_MSG_FORMATERR;
const char* pretty_format = pl_pretty_format;
const char* default_format = pl_default_format;
const char** short_days = pl_short_days;
const char** days = pl_days;
#endif

#ifdef DEF_FR
const char* helptext = fr_helptext;
const char* MSG_CERR = FR_MSG_CERR;
const char* MSG_DERR = FR_MSG_DERR;
const char* MSG_JERR = FR_MSG_JERR;
const char* MSG_LERR = FR_MSG_LERR;
const char* MSG_OPTERR = FR_MSG_OPTERR;
const char* MSG_NONOPTERR = FR_MSG_NONOPTERR;
const char* MSG_LONGERR = FR_MSG_LONGERR;
const char* MSG_GENERR = FR_MSG_GENERR;
const char* MSG_ILC = FR_MSG_ILC;
const char* MSG_IGD = FR_MSG_IGD;
const char* MSG_IJDN = FR_MSG_IJDN;
const char* MSG_FORMATERR = FR_MSG_FORMATERR;
const char* pretty_format = fr_pretty_format;
const char* default_format = fr_default_format;
const char** short_days = fr_short_days;
const char** days = fr_days;
#endif

// a simple idea. for each character of the include, if it matches, we set the
// defaults. this is the entire runtime support, which could be bypassed.

int set_lang(const char *lang)
{
	const char *c = lang;
	switch(*c)
	{
		case 'e':			// currently covers en, es
		{
			c++;
			if (*c == 'n') {
				helptext = en_helptext;
				
				MSG_CERR = EN_MSG_CERR;
				MSG_DERR = EN_MSG_DERR;
				MSG_JERR = EN_MSG_JERR;
				MSG_LERR = EN_MSG_LERR;
				MSG_OPTERR = EN_MSG_OPTERR;
				MSG_NONOPTERR = EN_MSG_NONOPTERR;
				MSG_LONGERR = EN_MSG_LONGERR;
				MSG_GENERR = EN_MSG_GENERR;
				MSG_ILC = EN_MSG_ILC;
				MSG_IGD = EN_MSG_IGD;
				MSG_IJDN = EN_MSG_IJDN;
				MSG_FORMATERR = EN_MSG_FORMATERR;

				pretty_format = en_pretty_format;
				default_format = en_default_format;

				short_days = en_short_days;
				days = en_days;
			}
			else if (*c == 's') {
				helptext = es_helptext;
		
				MSG_CERR = ES_MSG_CERR;
				MSG_DERR = ES_MSG_DERR;
				MSG_JERR = ES_MSG_JERR;
				MSG_LERR = ES_MSG_LERR;
				MSG_OPTERR = ES_MSG_OPTERR;
				MSG_NONOPTERR = ES_MSG_NONOPTERR;
				MSG_LONGERR = ES_MSG_LONGERR;
				MSG_GENERR = ES_MSG_GENERR;
				MSG_ILC = ES_MSG_ILC;
				MSG_IGD = ES_MSG_IGD;
				MSG_IJDN = ES_MSG_IJDN;
				MSG_FORMATERR = ES_MSG_FORMATERR;

				pretty_format = es_pretty_format;
				default_format = es_default_format;

				short_days = es_short_days;
				days = es_days;
			}
			break;
		}

		case 'd':		// german
		{
			c++;
			if (*c == 'e')
			{
				helptext = de_helptext;

                MSG_CERR = DE_MSG_CERR;
                MSG_DERR = DE_MSG_DERR;
                MSG_JERR = DE_MSG_JERR;
                MSG_LERR = DE_MSG_LERR;
                MSG_OPTERR = DE_MSG_OPTERR;
				MSG_NONOPTERR = DE_MSG_NONOPTERR;
				MSG_LONGERR = DE_MSG_LONGERR;
				MSG_GENERR = DE_MSG_GENERR;
				MSG_ILC = DE_MSG_ILC;
				MSG_IGD = DE_MSG_IGD;
				MSG_IJDN = DE_MSG_IJDN;
				MSG_FORMATERR = DE_MSG_FORMATERR;

				pretty_format = de_pretty_format;
				default_format = de_default_format;

				short_days = de_short_days;
				days = de_days;
			}
			break;
		}

		case 'f':  // french
		{
			c++;
			if (*c == 'r') {
				helptext = fr_helptext;
				
				MSG_CERR = FR_MSG_CERR;
				MSG_DERR = FR_MSG_DERR;
				MSG_JERR = FR_MSG_JERR;
				MSG_LERR = FR_MSG_LERR;
				MSG_OPTERR = FR_MSG_OPTERR;
				MSG_NONOPTERR = FR_MSG_NONOPTERR;
				MSG_LONGERR = FR_MSG_LONGERR;
				MSG_GENERR = FR_MSG_GENERR;
				MSG_ILC = FR_MSG_ILC;
				MSG_IGD = FR_MSG_IGD;
				MSG_IJDN = FR_MSG_IJDN;
				MSG_FORMATERR = FR_MSG_FORMATERR;

				pretty_format = fr_pretty_format;
				default_format = fr_default_format;

				short_days = fr_short_days;
				days = fr_days;
			}
			break;
		}
		
		case 'p':		// polish
		{
			c++;
			if (*c == 'l') {
				helptext = pl_helptext;

				MSG_CERR = PL_MSG_CERR;
				MSG_DERR = PL_MSG_DERR;
				MSG_JERR = PL_MSG_JERR;
				MSG_LERR = PL_MSG_LERR;
				MSG_OPTERR = PL_MSG_OPTERR;
				MSG_NONOPTERR = PL_MSG_NONOPTERR;
				MSG_LONGERR = PL_MSG_LONGERR;
				MSG_GENERR = PL_MSG_GENERR;
				MSG_ILC = PL_MSG_ILC;
				MSG_IGD = PL_MSG_IGD;
				MSG_IJDN = PL_MSG_IJDN;
				MSG_FORMATERR = PL_MSG_FORMATERR;

				pretty_format = pl_pretty_format;
				default_format = pl_default_format;

				short_days = pl_short_days;
				days = pl_days;
			}
			break;
		}

		default:
			break;
	}
	return 0;
}
