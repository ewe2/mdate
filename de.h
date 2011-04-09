// German translation (c) 2003 by Sean Dwyer <ewe2@users.sourceforge.net>.

// Portions of this translation derived from Matthias' work on a really old
// mdate translation, and careful scrutiny of date(1) German translation :)
// This is probably really bad, but write a better one than my schreklicher
// Höchschuler Deutsch :)

 
// version 1.7.0.3
// $Id$

// ============================= Mdate help ===============================

#ifdef STATIC_HELP
static char de_helptext[] __attribute__ ((unused)) =
"\n"
"Mdate gibt Mayan Datum.\n"
"Aufruf: mdate [OPTION]... [+FORMAT]\n"
"  -h, --help                    Gibt Hilfe aus und beendet\n"
"  -V, --version                 Gibt die Version und beendet\n"
"  -L, --lang=SPRACHE            Sprache (Standard en)\n"
"  -c, --correlation=DOUBLE      Benutzen Sie Korrelation (Standard=nein)\n"
"  -d, --dmy=ZEICHENKETTE        Tag, Monat, Jahr (Gregorianisch)\n"
"  -j, --julian=DOUBLE           Julianische Tagezahl\n"
"  -l, --longcount=ZEICHENKETTE  Langzahl (bis zu 9 Stellen)\n"
"\n"
"Gültige SPRACHE:\n"
"  en Englisch\n"
"  es Spanisch\n"
"  pl Polisch\n"
"  de Deutsch\n"
"  fr Französisch\n"
"\n"
"Gültige FORMAT:\n"
"  @a abgekürzter Name des Wochentags\n"
"  @A voller Name des Wochentags\n"
"  @b abgekürzter Monatsname\n"
"  @B voller Monatsname\n"
"  @d Tag des Monats (01..31)\n"
"  @e Tag des Monats, mit Leerzeichen aufgefüllt\n"
"  @F ISO Format Gregorianische Datum (%Y-%m-%d)\n"
"  @f ISO format Gregorianische Datum (%Y%m%d)\n"
"  @h Haab Datum\n"
"  @H Haab Datum mit Leerzeichen aufgefüllt\n"
"  @l Langezahl\n"
"  @M Monat (January..December)\n"
"  @m Monat (01..12)\n"
"  @T Tzolkin Datum mit Leerzeichen aufgefüllt\n"
"  @t Tzolkin Datum\n"
"  @y die letzen zwei Ziffern des Jahres (00 to 99)\n"
"  @Y voller Jahre\n"
"  @n neue Zeile (»newline«)\n"
"  @j horizontaler Tabulatorstopp\n"
"\n";
#endif

// ============================= Mdate messages ===========================

const char* DE_MSG_CERR = "Mdate: `--correlation' (`-c') Zuviele Optionen angegeben\n";
const char* DE_MSG_DERR = "Mdate: `--dmy' (`-d') Zuviele Optionen angegeben\n";
const char* DE_MSG_JERR = "Mdate: `--julian' (`-j') Zuviele Optionen angegeben\n";
const char* DE_MSG_LERR = "Mdate: `--longcount' (`-l') Zuviele Optionen angegeben\n";
const char* DE_MSG_OPTERR = "Mdate: Unbekannte Option: ";
const char* DE_MSG_NONOPTERR = "Zuviele Argumente!\n";
const char* DE_MSG_LONGERR = "Ungültige Langae Zahl specified!\n";
const char* DE_MSG_GENERR = "Fehler!\n";
const char* DE_MSG_ILC = "Ungültige Lange Zahl!\n";
const char* DE_MSG_IGD = "Ungültige Gregorianische Datum!\n";
const char* DE_MSG_IJDN = "Ungültige Julianische Tage Zahl\n";
const char* DE_MSG_FORMATERR = "Unbekannte Format!\n";

static char de_default_format[] __attribute__ ((unused)) = "JTZ: @J Datei: @d @m @Y  @l @T @H";

// ============================= Mdate days ===============================

static const char *de_short_days[] __attribute__ ((unused)) = {
	"Mon","Dienst","Mitt","Donner","Frei","Sams","Sonn"
};

static const char *de_days[] __attribute__ ((unused)) = {
	"Montag","Dienstag","Mittwoch","Donnerstag","Freitag","Samstag","Sonntag"
};
