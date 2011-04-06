// POLISH TRANSLATION.
// by Krzysztof "Tuvok" Borowczyk
 
// Wszelkie b³êdy/niejasno¶ci w t³umaczeniu zg³aszaæ na adres:
// tuvokhome@interia.pl
 
// version 1.5.1
// $Id$

// ============================= Mdate help ===============================

#ifdef STATIC_HELP
static char pl_helptext[] __attribute__ ((unused)) =
"\n"
"Mdate podaje proste daty wg. kalendarza Majów.\n"
"U¿ycie: mdate [OPCJE]... [+FORMAT]\n"
"   -h, --help                wy¶wietla pomoc i koñczy dzia³anie\n"
"   -V, --version             wy¶wietla wersjê programu i koñczy dzia³anie\n"
"   -g, --gmt                 korelacja GMT (standardowo wy³±czone)\n"
"   -L, --lang=LANGUAGE       wybór jêzyka\n"
"   -c, --correlation=DOUBLE  opcjonalna korelacja (standardowo brak)\n"
"   -d, --dmy=STRING          dzieñ miesi±c rok (wg. kalendarza Gregoriañskiego)\n"
"   -j, --julian=DOUBLE       numer dnia wg. kalendarza Juliañskiego\n"
"   -l, --longcount=STRING    data wg. D³ugiej Rachuby Kalendarzowej Majów\n"
"\n"
"Proprawne identyfikatory LANGUAGE:\n"
"  en Angielski\n"
"  es Hiszpañski\n"
"  pl Polski\n"
"  de Niemiecki\n"
"  fr Francuski\n"
"\n"
"Poprawne identyfikatory FORMAT'u:\n"
"  @a skrót nazwy dnia tygodnia\n"
"  @A pe³na nazwa dnia tygodnia\n"
"  @b skrót nazwy miesi±ca\n"
"  @B pe³na nazwa miesi±ca\n"
"  @d numer dnia miesi±ca (01..31)\n"
"  @e numer dnia bez poprzedzaj±cego zera \n"
"  @F format ISO daty Gregoriañskiej (%R-%m-%d)\n"
"  @f format ISO daty Gregoriañskiej (%R%m%d)\n"
"  @h data Haab bez poprzedzaj±cej spacji i zera\n"
"  @H data Haab z poprzedzaj±c± spacj± i zerem\n"
"  @l D³uga Rachuba Kalendarzowa\n"
"  @M nazwa miesi±ca Gregoriañskiego\n"
"  @m numer miesi±ca Gregoriañskiego\n"
"  @t data Tzolkin bez poprzedzaj±cej spacji i zera\n"
"  @T data Tzolkin z poprzedzaj±c± spacj± i zerem\n"
"  @y rok jako dwie cyfry (00-99)\n"
"  @Y rok Gregoriañski\n"
"  @n dodaje znak nowej lini\n"
"  @j dodaje dodaje znak tab\n"
"\n";
#endif

// ============================= Mdate messages ===========================

const char* PL_MSG_CERR = "Mdate: `--correlation' (`-c') opcja podana wiêcej ni¿ jeden raz\n";
const char* PL_MSG_DERR = "Mdate: `--dmy' (`-d') opcja podana wiêcej ni¿ jeden raz\n";
const char* PL_MSG_JERR = "Mdate: `--julian' (`-j') opcja podana wiêcej ni¿ jeden raz\n";
const char* PL_MSG_LERR = "Mdate: `--longcount' (`-l') opcja podana wiêcej ni¿ jeden raz\n";
const char* PL_MSG_OPTERR = "Mdate: nieznana opcja: ";
const char* PL_MSG_NONOPTERR = "Zbyt wiele argumentów nie bêd±cych opcjami!\n";
const char* PL_MSG_LONGERR = "Podana data nie jest dozwolona!\n";
const char* PL_MSG_GENERR = "b³±d!\n";
const char* PL_MSG_ILC = "Nieprawid³owo podana D³uga Rachuba Kalendarzowa!\n";
const char* PL_MSG_IGD = "Nieprawid³owo podana data Gregoriañska!\n";
const char* PL_MSG_IJDN = "Nieprawid³owo podany Juliañski numer dnia!\n";
const char* PL_MSG_FORMATERR = "Nieznany format!\n";

static char pl_default_format[] __attribute__ ((unused)) = "JND: @J data: @d @m @Y  @l @T @H";

// ============================= Mdate days ===============================

static const char *pl_short_days[] __attribute__ ((unused)) = {
	"Pon","Wto","¦ro","Czw","Pi±","Sob","Nie"
};

static const char *pl_days[] __attribute__ ((unused)) = {
	"Poniedzia³ek","Wtorek","¦roda","Czwartek","Pi±tek","Sobota","Niedziela"
};
