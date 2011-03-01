################################################################################
# Makefile for mdate
# $Id$
#
# Usage:
#	make target=linux					# linux
#	make target=cygwin					# cygwin 1.3.x
#	make target=mingw64-cross mdate.exe	# linux (Debian) win32 cross-compile
#	gmake target=freebsd				# FreeBSD 4.x target
#	make target=beos					# BeOS r5
#	make target=osx						# Mac OSX 32-bit console
#
# The default target is linux on x86 with a pentium-class processor.
# I can't guarantee the other targets will work, I haven't used Cygwin for
# quite a while now, it's probably out of date. Fixes would be most welcome.
#
# I use the default 32bit target for mingw64 at present. If there is need I
# can provide a 64bit target also.
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
VERSION=1.7.0
DEVVER=1.7.0

# tagging for release and development. development branch should be tagged
# DEVTAG when release master is done.
RELTAG=v$(VERSION)
DEVTAG=v$(DEVVER)

#SVNVERSION = 1-5-7

# Obsolete repositories that are recently current.
# Moved to github
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

ifeq ($(target),mingw64-cross)
	nogetopt=1
	noi18n=1
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


## Default compiler. On Debian, we're up to gcc-4.2, so check your cflags!
# Updated for the nuisance deprecation of string conversions 
CXX=g++
CC=gcc
INC=-I/usr/include -I.
DEFS+=-DHAVE_CONFIG_H -D$(DEFLANG) -DPACKAGE=\"$(PACKAGE)\" -DVERSION=\"$(VERSION)\"
CFLAGS=-O -Wall -Wno-write-strings -ffloat-store $(DEFS)
CXXFLAGS=$(CFLAGS) -fno-rtti
LIBS=-lm

## define debug if you want to help debug mdate with gdb. otherwise, ignore.
debug=1

ifeq ($(debug),1)
	CFLAGS+=-g
endif

## linux Target.
## If you're not sure about your -march or -mcpu, try uname -a: it will tell
## you what cpu your kernel supports. Also see /proc/cpuinfo.
## gcc 2.95 and below do NOT support -march=athlon !!
## new gcc versions (4.1.x and above) prefer -mtune to -march, if your gcc
## doesn't work with this parameter, revert

ifeq ($(target),linux)
# A Pentium II or above is i686. Doubtful that multiprocessor optimizations are
# useful here.
	CFLAGS += -mtune=core2 $(INC)
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

## linux mingw64 cross-compiler, can output both 64 and 32bit code. Default to
## 64bit unless you need 32bit help (alter the x86_64 to i686).
ifeq ($(target),mingw64-cross)
	CC = x86_64-w64-mingw32-gcc
	CXX = x86_64-w64-mingw32-g++
	CFLAGS += -mconsole -I.
endif

## BeOS has different paths
ifeq ($(target),beos)
	INC=
	CXXFLAGS += -I/boot/home/config/include -I./
	CC= gcc
	LIBS=-L/boot/home/config/lib -lintl
endif

## OSX target: this builds native binaries
ifeq ($(target),osx)
	DEFS +=-DIS_OSX
endif

## builds universal binaries, this will likely become default. ld up to 10.4.6
## does not support the -Wl syntax but may in the future, search Xcode docs for
## compiling universal binaries in the porting guide section. You shouldn't
## need them here as gcc will pass the link flags on.
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

.PHONY: help clean docclean distclean gitch updategit reltag devtag
# need this for directory search

mdate: $(OBJS)
	$(CXX) $(CFLAGS) $(INC) -o mdate $(OBJS) $(LDFLAGS) $(LIBS)

ifeq ($(target),mingw64-cross)
mdate.exe: all
	-cp mdate mdate.exe
endif

## documentation targets

# pass the doc stuff off to a submake in doc/
createdoc:
	cd doc && $(MAKE)

## install targets

install: installbin

installbin: mdate installman
	@[ -d $(BINDIR) ] || mkdir -p $(BINDIR); \
	install -m 755 mdate $(BINDIR)/mdate

installman: mdate
	[ -d $(MANDIR) ] || mkdir -p $(MANDIR); \
    install -m 644 doc/mdate.1 $(MANDIR); \
    gzip -9f $(MANDIR)/mdate.1
		

installdoc: createdoc installman
	[ -d $(DOCDIR) ] || mkdir -p $(DOCDIR); \
	install -m 644  README NEWS ChangeLog GPL API $(DOCDIR); \
	install -m 644  AUTHORS Translators $(DOCDIR); \
	[ -d $(HTMLDIR) ] || mkdir -p $(HTMLDIR); \
	install -m 644  *.html $(HTMLDIR)
	cp $(HTMLDIR)/mdate.html $(HTMLDIR)/index.html

## dependencies
$(OBJS): config.h 
lang.o cmdline.o: lang.h
mdate.o main.o: mdate.h
cmdline.o main.o: cmdline.h
cmdline.o main.o getopt.o getopt1.o: getopt.h

#lang.o: lang.cpp lang.h
#mdate.o: mdate.cpp mdate.h
#cmdline.o: cmdline.cpp mdate.h cmdline.h getopt.h lang.h
#main.o: main.cpp mdate.h cmdline.h getopt.h
#getopt.o: getopt.c getopt.h
#getopt1.o: getopt1.c getopt.h
#snprintf.o: snprintf.c

distclean: clean docclean

SOURCES=*.cpp *.c *.h
DOX=doc/mdate.html doc/mdate.pdf doc/mdate.txt NEWS README GPL API ChangeLog \
AUTHORS doc/mdate.xml Translators doc/mdate.1 BUGS ChangeLog.old README.devel
CONFS=Makefile mdate.spec ChangeLog.header .gitattributes .gitignore
DEBCONF=debian/*
DISTFILES= $(SOURCES) $(DOX) $(CONFS)

# developers targets only!

# the simple way to log!
gitch:
	cat ChangeLog.header > ChangeLog
	git log --name-only >> ChangeLog


# tagging commits for different purposes. we use a version tag to mark them.
# remember tags are just a shorthand for commits they aren't the actual
# branches which have their own name, but it's easier to refer to the tags if
# releases should be made from a branch.


reltag:
	GIT_COMMITER_DATE=`date +'%F %R'` git tag -s -m "mdate $(RELTAG)" $(RELTAG) $(com)

devtag:
	GIT_COMMITTER_DATE=`date +'%f %R'` git tag -s -m "mdate $(DEVTAG)" $(DEVTAG) $(com)

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

# tarballs via git
# You can choose HEAD or a tag here
# assumes you've committed, etc.
reldist:
	git archive --format=tar --prefix=mdate-$(RELTAG)/ HEAD | gzip>mdate-$(VERSION).tar.gz
devdist:
	git archive --format=tar --prefix=mdate-dev$(DEVTAG)/ $(DEVTAG) | gzip>mdate-dev$(DEVVER).tar.gz

# both these targets are heavily system-dependent and prone to syntax changes.
rpm:
	rpmbuild -bb mdate.spec

deb:
	fakeroot debian/rules binary

clean:
	-rm -f mdate $(OBJS) *.o mdate.exe *~ *core

docclean: 
	cd doc && $(MAKE) docclean

help:
	@echo " "
	@echo "Usage:"
	@echo "	make target=linux"
	@echo "	make target=cygwin"
	@echo "	make target=mingw64-cross mdate.exe"
	@echo "	make target=beos"
	@echo "	gmake target=freebsd"
	@echo "	make target=osx"
	@echo "	make target=uniosx"
	@echo " "
	@echo "Dev targets:"
	@echo "	make gitch     - use git to update Changelog"
	@echo "	make devtag    - tag src for development"
	@echo "	make reltag    - tag src for release"
	@echo "	make devdist   - nightly tarballs"
	@echo "	make reldist   - release tarballs"
	@echo " make createdoc - generate documentation"
	@echo "	make rpm       - rpm package"
	@echo "	make deb       - deb package"
