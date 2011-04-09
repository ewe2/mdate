# q&d makefile to just make the boost testbed. as this continues we'll add
# mdate.cpp for fuller testing.
PACKAGE=mdate
VERSION=v1.7.1
LIBS=-lboost_program_options
CXX=g++
DEFS+=-DDEF_EN -DHAVE_CONFIG_H -DTEST -DPACKAGE=\"$(PACKAGE)\" -DVERSION=\"$(VERSION)\"
CFLAGS=$(DEFS)
CXXFLAGS=$(CFLAGS)
OBJS=lang.o bparse.o

bparse: $(OBJS) 
	$(CXX) $(CFLAGS) -o bparse $(OBJS) $(LIBS)


clean:
	rm -f bparse *.o *~
##
lang.o: lang.cpp config.h lang.h
bparse.o: bparse.cpp config.h mdate.h
