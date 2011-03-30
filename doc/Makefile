# Makefile for mdate documentation
# $Id$
#
# TODO our hacky converters. we need to move to a format like asciidoc and make
# this all go away.
D2H=./db2html
D2P=./db2pdf

mdoc: mdate.xml mdate.pdf mdate.html mdate.txt

# Force rewriting
mdate.xml: mdate.txt
	asciidoc -a toc -b docbook $<

mdate.html:	mdate.xml
	$(D2H) $< > mdate.html 

# optional tidy target. it upsets make but works
htmltidy: mdate.html
	cat $< | tidy -q -m -o mdate.html

mdate.pdf: mdate.xml
	$(D2P) $<

docclean:
	rm -f *.fo
	rm -f *.pdf
	rm -f *.xml
	rm -f *.html

# Generate html and xml api documentation. Quite optional and usually
# pregenerated.
apidoc:
	doxygen Doxyfile

apiclean:
	rm -rf html/ xml/
