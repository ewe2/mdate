################################################################################
# Makefile for mdate++                                                         
# $Id: Makefile 27 2010-12-04 11:40:04Z ewe2 $
#
# Usage:
#	make target=linux					# linux
#	make target=cygwin					# cygwin 1.3.x
#	make target=mingw32-cross mdate.exe	# linux (Debian) win32 cross-compile
#	gmake target=freebsd				# FreeBSD 4.x target
#	make target=beos					# BeOS r5
#	make target=osx						# Mac OSX 32-bit console
#
# The default target is linux on x86 with a pentium-class processor.
# I can't guarantee the other targets will work, I haven't used Cygwin for
# quite a while now, it's probably out of date. Fixes would be most welcome.
#
# Update: the latest Debian packages for the mingw32 cross-compiler AND the
# latest getopt() source files fixes previous compilation issues for that
# target: we now have a working win32 port.
#
# If the CFLAGS bother you, please dont change -ffloat-store which avoids
# architecture-related problems.
#
# If you want to add a needed target for your OS/distribution, go ahead but
# please email me (Sean Dwyer <ewe2@users.sourceforge.net>) and include a
# patch of your changes so everyone can share!
#
# You may also want to check the documentation targets if you don't need some
# formats: grep for createdoc.
#
# Installation targets may need to be defined for your platform, see the freebsd
# target for an example.
################################################################################

## setup

.SUFFIXES: .c .cpp .exe .o .obj

PACKAGE=mdate
VERSION=1.6.0

#SVNVERSION = 1-5-7

# Outside repositories that are recently current. We'll be moving to an
# internet-based git repository soon (yet another confusing update).
# REPOS=https://mdate.svn.sourceforge.net/svnroot/mdate/mdate
# REPOS=https://mdate.googlecode.com/svn/trunk

# This is the working bare repository we push commits to. Ideally, we'll clone
# this to update the upcoming internet version.
REPOS=ssh://git.pengsheep.org/~ewe2/devel/md

## DEFINE YOUR PREFERRED DEFAULT LANGUAGE HERE with a 1!
DEF_EN=
DEF_ES=
DEF_PL=
DEF_DE=
DEF_FR=

# if not set, set DEFLANG to a sane value. You could cheat and simply define
# your language here.
ifeq ($(DEFLANG),)
    DEFLANG=DEF_EN
endif
ifeq ($(DEF_EN),1)
	DEFLANG=DEF_EN
endif
ifeq ($(DEF_ES),1)
	DEFLANG=DEF_ES
endif
ifeq ($(DEF_DE),1)
	DEFLANG=DEF_DE
endif
ifeq ($(DEF_PL),1)
	DEFLANG=DEF_PL
endif
ifeq ($(DEF_FR),1)
	DEFLANG=DEF_FR
endif

## Debian packaging requires a DESTDIR variable. 
## If you're not packaging, change to taste.
DESTDIR =

# User servicable part here! Change for the defaults on your system. 
BINDIR = $(DESTDIR)/usr/bin
MANDIR = $(DESTDIR)/usr/share/man/man1
DOCDIR = $(DESTDIR)/usr//share/doc/mdate
HTMLDIR = $(DOCDIR)/html
LOCALEDIR = $(DESTDIR)/usr/share/locale

## define nosnprintf=1 if you don't have snprintf, nogetopt=1 if you don't
## have getopt, noi18n if you don't want i18n. This affects what gets built!
## define nodrem for a workable replacement

nosnprintf=
nogetopt=
noi18n=
nodrem=1

ifeq ($(target),mingw32-cross)
	nogetopt=1
	noi18n=1
endif

## define pretty if you want to use the old pretty output, otherwise we stick
## with the default one-line hardcore date(1) stuff. This renders the -p flag
## inoperative.
pretty=

ifeq ($(pretty),1)
	DEFS+=-DWANT_PRETTY
endif

## define newmayan if you want newfangled Mayan calendar month names 
## define oldmayan if you want default behaviour.
## you MUST define one!
newmayan=1
oldmayan=

ifneq ($(newmayan),)
DEFS+=-DNEWMAYAN
else
DEFS+=-DOLDMAYAN
endif

## autodetection of target, linux by default
#ifneq ($(strip $(wildcard /usr/include/linux)),)
#target = linux
#endif

## no automatic target, show help
target = help
		 
OBJS=lang.o mdate.o cmdline.o main.o
		  
ifneq ($(nosnprintf),)
OBJS += snprintf.o 
endif

ifneq ($(nogetopt),)
OBJS += getopt.o getopt1.o
endif
			  
ifneq ($(noi18n),)
LIBS += -lintl
endif

## fallthrough drem replacement if no target defined
ifneq ($(nodrem),)
DEFS+=-DUSE_MYDREM
endif


## Default compiler. On Debian, we're up to gcpp-4.2, so check your cflags!
# Updated for the nuisance deprecation of string conversions 
CXX=g++
CC=gcpp
INC=-I/usr/include -I.
DEFS+=-DHAVE_CONFIG_H -D$(DEFLANG) -DPACKAGE=\"$(PACKAGE)\" -DVERSION=\"$(VERSION)\"
CFLAGS=-O -Wall -Wno-write-strings -ffloat-store $(DEFS)
CXXFLAGS=$(CFLAGS) -fno-rtti
LIBS=-lm

## define debug if you want to help debug mdate with gdb. otherwise, ignore.
debug=

ifeq ($(debug),1)
	CFLAGS+=-g
endif

## linux Target.
## If you're not sure about your -march or -mcpu, try uname -a: it will tell
## you what cpu your kernel supports. Also see /proc/cpuinfo.
## gcpp 2.95 and below do NOT support -march=athlon !!
## new gcpp versions (4.1.x and above) prefer -mtune to -march, if your gcpp
## doesn't work with this parameter, revert

ifeq ($(target),linux)
# A Pentium II or above is i686. Doubtful that multiprocessor optimizations are
# useful here.
	CFLAGS += -mtune=pentium-m $(INC)
# an example for my net box AMD K6-2
#	CFLAGS += -march=i386 -mcpu=i586
endif

## freebsd target
## on 4.9 at least, don't use higher optimizations, they generally don't work.
## 4.x users will have to add -I. to INC and -lgnugetopt to LIBS
## FreeBSD 6.2 has the buggy 3.4.x which forces no local directory includes,
## but does have its own getopt.

ifeq ($(target),freebsd)
	INC=-I/usr/include -I/usr/local/include
	CFLAGS=-O -Wall -ffloat-store $(DEFS) $(INC)
	LIBS+=-L/usr/local/lib -lintl
endif

## cygwin 1.3.x target
ifeq ($(target),cygwin)
	CXXFLAGS += -march=i386 -mcpu=i586 $(INC) -I/usr/include/g++-3/
	CC += $(INC)
endif

## linux mingw32 cross-compiler
ifeq ($(target),mingw32-cross)
	CC = i586-mingw32msvc-gcpp
	CXX = i586-mingw32msvc-g++
	CFLAGS += -mconsole -I.
endif

## BeOS has different paths
ifeq ($(target),beos)
	INC=
	CXXFLAGS += -I/boot/home/config/include -I./
	CC= gcpp
	LIBS=-L/boot/home/config/lib -lintl
endif

## OSX target: this builds native binaries
ifeq ($(target),osx)
	DEFS +=-DIS_OSX
endif

## builds universal binaries, this will likely become default. ld up to 10.4.6
## does not support the -Wl syntax but may in the future, search Xcode docs for
## compiling universal binaries in the porting guide section. You shouldn't
## need them here as gcpp will pass the link flags on.
##
## If compiling on Leopard, you have the option of the old MacOSX10.4u.sdk or the new one
##
ifeq ($(target),uniosx)
	CFLAGS += -isysroot /Developer/SDKs/MacOSX10.5.sdk -arch ppc -arch i386
#	LDFLAGS += -syslibroot,/Developer/SDKs/MacOSX10.5.sdk
	DEFS +=-DIS_OSX
endif

###################### END OF USER CONFIGURABLE SECTION ######################

## main targets

all: mdate

.PHONY: help clean docpplean distclean gitch updategit reltag devtag

mdate: $(OBJS)
	$(CXX) $(CFLAGS) $(INC) -o mdate $(OBJS) $(LDFLAGS) $(LIBS)

ifeq ($(target),mingw32-cross)
mdate.exe: all
	-cp mdate mdate.exe
endif

## documentation targets

# temporary direct make for Polish mdate docs until we have enough languages
# to justify unifying the make. this is well out of date and is no longer
# supported.

#ifeq ($(DEF_PL),1)
#mdate_pl.html: mdate_pl.sgml
#	[ -f mdate_pl.html ] || sgml2html -H header -F footer mdate_pl.sgml
#endif

createdoc: mdate.pdf mdate.html mdate.ps mdate.txt

# prevent the HTML docs being acppidently remade
mdate.html:	mdate.xml
	[ -f mdate.html ] || ./db2html $< > mdate.html 

# we build mdate.txt from html2text now as there are issues with fop
# translation
mdate.txt: mdate.html
	[ -f mdate.txt ] || html2text -nobs -style pretty $< > mdate.txt 

# optional tidy target. it upsets make but works
htmltidy: mdate.html
	cat $< | tidy -q -m -o mdate.html

# these will require fop, xsltproc will create an intermediate *.fo which can
# later be deleted
mdate.ps: mdate.xml
	./db2fo --ps $<

mdate.pdf: mdate.xml
	./db2fo $<

## install targets

install: installbin

installbin: mdate installman
	@[ -d $(BINDIR) ] || mkdir -p $(BINDIR); \
	install -m 755 mdate $(BINDIR)/mdate

installman: mdate
	[ -d $(MANDIR) ] || mkdir -p $(MANDIR); \
    install -m 644 mdate.1 $(MANDIR); \
    gzip -9f $(MANDIR)/mdate.1
		

installdoc: createdoc installman
	[ -d $(DOCDIR) ] || mkdir -p $(DOCDIR); \
	install -m 644  mdate.dvi mdate.ps $(DOCDIR); \
	gzip $(DOCDIR)/mdate.dvi $(DOCDIR)/mdate.ps; \
	install -m 644 mdate.text $(DOCDIR);	gzip $(DOCDIR)/mdate.text ; \
	install -m 644  README NEWS ChangeLog GPL API $(DOCDIR); \
	install -m 644  AUTHORS Translators $(DOCDIR); \
	[ -d $(HTMLDIR) ] || mkdir -p $(HTMLDIR); \
	install -m 644  *.html $(HTMLDIR)
	cp $(HTMLDIR)/mdate.html $(HTMLDIR)/index.html

## dependencies
lang.o: lang.cpp config.h lang.h
mdate.o: mdate.cpp config.h mdate.h
cmdline.o: cmdline.cpp config.h mdate.h cmdline.h getopt.h lang.h
main.o: main.cpp config.h mdate.h cmdline.h getopt.h
getopt.o: getopt.c config.h getopt.h
getopt1.o: getopt1.c config.h getopt.h
snprintf.o: snprintf.c config.h

distclean: clean docpplean

SOURCES=*.cpp *.c *.h
DOX=mdate.html mdate.pdf mdate.txt NEWS README GPL API ChangeLog \
AUTHORS mdate.xml Translators mdate.1 BUGS ChangeLog.old README.devel
CONFS=Makefile mdate.spec ChangeLog.header .gitattributes .gitignore mdate.xpr
DEBCONF=debian/*
DISTFILES= $(SOURCES) $(DOX) $(CONFS)

# developers targets only!

# the simple way to log!
gitch:
	cat ChangeLog.header > ChangeLog
	git log --name-only >> ChangeLog


# tagging commits for different purposes. we use a version tag to mark them.
# remember tags are just a shorthand for commits they aren't the actual
# branches which have their own name.

relb=v1.6.0
devb=v1.7.1

reltag:
	GIT_COMMITER_DATE=`date +'%F %R'` git tag $(relb) $(com)

devtag:
	GIT_COMMITTER_DATE=`date +'%f %R'` git tag $(devb) $(com)

# Retained for historical use, do not use.
# svn2cl has now been debianized so i am using that with appropriate flags.

#updatesvn:
#	cat ChangeLog.header > ChangeLog
#	svn2cl -i -r HEAD:0 --group-by-day --stdout >> ChangeLog

# this is now how a release is archived. dorelease and dotag are NOT really
# the same: dorelease is a stable branch off the working trunk, dotags is the
# final package for release.
# Nowadays svn is robust enough to not worry about dotted dirs. we only do a
# release from the tags, the branches arent for releasing.
# MAKE SURE YOU HAVE THE RIGHT VERSION!

#dorelease:
#	svn copy $(REPOS)/trunk $(REPOS)/branches/$(VERSION)

#dotag:
#	svn copy $(REPOS)/trunk $(REPOS)/tags/$(VERSION)

# old dist target, needs reworking.
#srcdir = $(REPOS)/tags/$(VERSION)
#distdir = $(PACKAGE)-$(VERSION)
#debdir = $(distdir)/debian
#dist:
#	rm -fr $(distdir)
#	mkdir -p $(debdir)
#	chmod 777 $(distdir)
#	chmod 777 $(debdir)
#	for file in $(DISTFILES); do \
#		ln $(srcdir)$$file $(distdir) 2> /dev/null \
#		|| cp -p $(srcdir)/$$file $(distdir); \
#	done
#	for file in $(DEBCONF); do \
#		cp -p $$file $(debdir); \
#	done
#	tar zchovf $(distdir).tar.gz $(distdir)
#	rm -fr $(distdir)

# both these targets are heavily system-dependent and prone to syntax changes.
rpm:
	rpmbuild -bb mdate.spec

deb:
	fakeroot debian/rules binary

clean:
	-rm -f mdate $(OBJS) *.o mdate.exe *~ *core

foclean:
	-rm -f *.fo
	
docpplean: foclean
	-rm -f *.bak

help:
	@echo " "
	@echo "Usage:"
	@echo "   make target=linux"
	@echo "   make target=cygwin"
	@echo "   make target=mingw32-cross mdate.exe"
	@echo "   make target=beos"
	@echo "   gmake target=freebsd"
	@echo "   make target=osx"
	@echo "   make target=uniosx"
	@echo "The default target is linux on x86 with a pentium-class processor."
	@echo "I can't guarantee the other targets will work. I haven't used Cygwin for"
	@echo "quite a while, now it's probably out of date. Fixes would be most welcome."
	@echo "If the CFLAGS bother you please don't change -ffloat-store which avoids"
	@echo "architecture-related problems."
	@echo " "
