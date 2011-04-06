// Translation of mdate to Castilian (Spanish)
// This file is distributed under the same license as the mdate package.
// Copyright (C) 1998-2009 Sean Dwyer <ewe2@users.sourceforge.net>
// Quique <quique@sindominio.net>, 2003, 2004
//
// version 1.5.1
// $Id$

// ============================= Mdate help ===============================

#ifdef STATIC_HELP
static char es_helptext[] __attribute__ ((unused)) =
"\n"
"Mdate muestra fechas mayas simples.\n"
"Sintaxis: mdate [OPCIÓN]... [+FORMATO]\n"
"   -h, --help                Muestra este mensaje de ayuda y acaba.\n"
"   -V, --version             Muestra la versión del programa y acaba.\n"
"   -g, --gmt                 Usa la correlación Goodman-Martínez-Thompson.\n"
"                             (por omisión: desactivado).\n"
"   -L, --lang=IDIOMA         Cambia de idioma (por omisión: en).\n"
"   -c, --correlation=DOBLE   Correlación opcional (por omisión: no).\n"
"   -d, --dmy=CADENA          Día mes año (gregoriano).\n"
"   -j, --julian=DOBLE        Número de día juliano.\n"
"   -l, --longcount=CADENA    Cuenta larga.\n"
"\n"
"Se aceptan los siguientes identificadores de IDIOMA:\n"
"  en Inglés\n"
"  es Castellano\n"
"  pl Polaco\n"
"  de Alemán\n"
"  fr Francés\n"
"\n"
"Se aceptan los siguientes identificadores de FORMATO:\n"
"  @a nombre del día de la semana abreviado\n"
"  @A nombre del día de la semana completo\n"
"  @b nombre del mes abreviado\n"
"  @B nombre del mes completo\n"
"  @d día del mes (01 - 31)\n"
"  @e día del mes sin cero inicial\n"
"  @F fecha gregoriana en formato ISO (%Y-%m-%d)\n"
"  @f fecha gregoriana en formato ISO (%Y%m%d)\n"
"  @h fecha Haab sin relleno\n"
"  @H fecha Haab con relleno\n"
"  @l cuenta larga\n"
"  @M nombre del mes gregoriano\n"
"  @m número del mes gregoriano\n"
"  @t fecha Tzolkin con relleno\n"
"  @T fecha Tzolkin sin relleno\n"
"  @y año como decimal de 00 a 99\n"
"  @Y año gregoriano\n"
"  @n añadir un salto de línea a la salida\n"
"  @j añadir un tabulador a la salida\n"
"\n";
#endif

// ============================= Mdate messages ===========================

const char* ES_MSG_CERR = "Mdate: La opción `--correlation' (`-c') aparece más de una vez.\n";
const char* ES_MSG_DERR =  "Mdate: La opción `--dmy' (`-d') aparece más de una vez.\n";
const char* ES_MSG_JERR = "Mdate: La opción `--julian' (`-j') aparece más de una vez.\n";
const char* ES_MSG_LERR = "Mdate: La opción `--longcount' (`-l') aparece más de una vez.\n";
const char* ES_MSG_OPTERR = "Mdate: Opción desconocida: ";
const char* ES_MSG_NONOPTERR = "Demasiados argumentos que no eran opciones.\n";
const char* ES_MSG_LONGERR = "La cuenta larga producida por esta fecha no es válida.\n";
const char* ES_MSG_GENERR = "¡Error!\n";
const char* ES_MSG_ILC = "La cuenta larga introducida no es válida.\n";
const char* ES_MSG_IGD = "La fecha gregoriana introducida no es válida.\n";
const char* ES_MSG_IJDN = "El número de día juliano introducido no es válido.\n";
const char* ES_MSG_FORMATERR = "¡Formato desconocido!\n";

static char es_default_format[] __attribute__ ((unused)) = "NDJ: @J fecha: @d @m @Y  @l @T @H";

// ============================= Mdate days ===============================

static const char *es_short_days[] __attribute__ ((unused)) = {
	"lun","mar","mié","jue","vie","sáb","dom"
};

static const char *es_days[] __attribute__ ((unused)) = {
	"lunes","martes","miércoles","jueves","viernes","sábado","domingo"
};
