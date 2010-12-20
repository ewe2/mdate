// French translation (c) 2003 by François-Xavier Coudert
// <coudert@users.sourceforge.net>
 
// version 1.5.1
// $Id: fr.h 30 2010-12-04 12:00:35Z ewe2 $

// ============================= Mdate help ===============================

#ifdef STATIC_HELP
static char fr_helptext[] __attribute__ ((unused)) =
"\n"
"Mdate retourne des dates simples au calendrier maya.\n"
"Utilisation: mdate [OPTION]... [+FORMAT]\n"
"   -h, --help                Affiche ce message d'aide et quitte\n"
"   -V, --version             Affiche le numéro de version et quitte\n"
"   -p, --parseable           sortie à format fixe (par défaut : non)\n"
"   -g, --gmt                 utilise la corrélation GTM (par défaut : non)\n"
"   -L, --lang=LANGUE         change la langue (par défaut : en)\n"
"   -c, --correlation=DOUBLE  corrélation optionnelle (par défaut : non)\n"
"   -d, --dmy=CHAîNE          jour mois année (calendrier grégorien)\n"
"   -j, --julian=DOUBLE       numéro du jour dans le calendrier julien\n"
"   -l, --longcount=CHAîNE    compte long\n"
"\n"
"Les indicatifs de LANGUE valables sont :\n"
"  fr  français\n"
"  en  anglais\n"
"  de  allemand\n"
"  es  espagnol\n"
"  pl  polonais\n"
"\n"
"Les indicatifs de FORMAT valables sont :\n"
"  @a  nom du jour de la semaine en abrégé\n"
"  @A  nom du jour de la semaine\n"
"  @b  nom du mois en abrégé\n"
"  @B  nom du mois\n"
"  @d  jour du mois (01..31)\n"
"  @e  jour du mois, sans zéro inutile (1..31)\n"
"  @F  Date au calendrier grégorien, format ISO (%Y-%m-%d)\n"
"  @f  Date au calendrier grégorien, format ISO (%Y%m%d)\n"
"  @h  date Haab, sans zéro inutile\n"
"  @H  date Haab, format fixe\n"
"  @l  Compte Long\n"
"  @M  nom du mois grégorien\n"
"  @m  mois grégorien numérique\n"
"  @t  date Tzolkin, sans zéro inutile\n"
"  @T  date Tzolkin, format fixe\n"
"  @y  année dans le siècle (27 pour 2027)\n"
"  @Y  année grégorienne\n"
"  @n  retour à la ligne\n"
"  @j  tabulation\n"
"\n";
#endif

// ============================= Mdate messages ===========================

const char* FR_MSG_CERR = "Mdate: `--correlation' (`-c') a été utilisé plus d'une fois\n";
const char* FR_MSG_DERR = "Mdate: `--dmy' (`-d') a été utilisé plus d'une fois\n";
const char* FR_MSG_JERR = "Mdate: `--julian' (`-j') a été utilisé plus d'une fois\n";
const char* FR_MSG_LERR = "Mdate: `--longcount' (`-l') a été utilisé plus d'une fois\n";
const char* FR_MSG_OPTERR = "Mdate: option inconnue: ";
const char* FR_MSG_NONOPTERR = "Trop d'arguments qui ne sont pas des options !\n";
const char* FR_MSG_LONGERR = "Le compte long spécifié n'est pas valable !\n";
const char* FR_MSG_GENERR = "erreur !\n";
const char* FR_MSG_ILC = "Ce compte long n'est pas valable !\n";
const char* FR_MSG_IGD = "Cette date grégorienne n'est pas valable !\n";
const char* FR_MSG_IJDN = "Cette date au calendrier julien n'est pas valable !\n";
const char* FR_MSG_FORMATERR = "Format inconnu !\n";

// ============================= Mdate formats ============================

static char fr_pretty_format[] __attribute__ ((unused)) =
"\n"
"Jour grégorien : @d-@B-@Y (@d/@m/@Y)\n"
"Jour julien    : @J\n"
"Compte long    : @l\n"
"Date Tzolkin   : @T\n"
"Date Haab      : @h\n";


static char fr_default_format[] __attribute__ ((unused)) = "JDN: @J date: @d @m @Y  @l @T @H";

// ============================= Mdate days ===============================

static const char *fr_short_days[] __attribute__ ((unused)) = {
	"Lun","Mar","Mer","Jeu","Ven","Sam","Dim"
};

static const char *fr_days[] __attribute__ ((unused)) = {
	"Lundi","Mardi","Mercredi","Jeudi","Vendredi","Samedi","Dimanche"
};
