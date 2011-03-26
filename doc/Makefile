# Makefile for mdate documentation
# $Id$
#
# TODO our hacky converters. we need to move to a format like asciidoc and make
# this all go away.
D2H=./db2html
D2F=./db2fo

mdoc: mdate.pdf mdate.html mdate.ps mdate.txt

# prevent the HTML docs being acppidently remade
mdate.html:	mdate.xml
	[ -f mdate.html ] || $(D2H) $< > mdate.html 

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
	$(D2F) --ps $<

mdate.pdf: mdate.xml
	$(D2F) $<

# Generate html and xml api documentation. Quite optional and usually
# pregenerated.
apidoc:
	doxygen Doxyfile

apiclean:
	rm -rf html/ xml/
