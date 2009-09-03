## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 The Vaucanson Group.
##
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License
## as published by the Free Software Foundation; either version 2
## of the License, or (at your option) any later version.
##
## The complete GNU General Public Licence Notice can be found as the
## `COPYING' file in the root directory.
##
## The Vaucanson Group consists of people listed in the `AUTHORS' file.

include $(top_srcdir)/vaucanson.mk

SUBDIRS = manual

all-local: $(srcdir)/stamp

# Run "make doc" to forcefully rebuild the Doxygen documentation.
.PHONY: doc
doc:
	-rm -f $(srcdir)/stamp
	$(MAKE) $(srcdir)/stamp

## ----------------------- ##
## Doxygen documentation.  ##
## ----------------------- ##

DOCDIR = ref
DOXYFILE = doc.doxy

$(srcdir)/stamp: $(srcdir)/$(DOXYFILE).in $(top_srcdir)/configure.ac
	-rm -rf $(DOCDIR).tmp
	$(MAKE) $(AM_MAKEFLAGS) $(DOXYFILE)
	$(DOXYGEN) $(DOXYFILE)
	-rm -rf $(srcdir)/$(DOCDIR)
## FIXME: moving directories between file systems is not portable.
	mv $(DOCDIR).tmp $(srcdir)/$(DOCDIR)
	touch $(srcdir)/stamp

$(srcdir)/$(DOCDIR): $(srcdir)/stamp

# We install by hand, otherwise Automake produces "install .../srcdoc
# .../srcdoc", which installs our dir into the previous one, instead
# of replacing it.
install-data-local:
	rm -rf $(DESTDIR)$(htmldir)/$(DOCDIR)
	$(mkdir_p) $(DESTDIR)$(htmldir)
	cp -r $(srcdir)/$(DOCDIR) $(DESTDIR)$(htmldir)
## Try GNU chmod's X mode before resorting to something slower but
## more standard.
	chmod -R a+rX $(DESTDIR)$(htmldir) || \
	find $(DESTDIR)$(htmldir) \( -type d -a -exec chmod a+rx {} \; \) \
             -o -exec chmod a+r {} \;

uninstall-local:
	chmod -R 700 $(DESTDIR)$(htmldir)/$(DOCDIR)
	rm -rf $(DESTDIR)$(htmldir)/$(DOCDIR)

maintainer-clean-local:
	rm -rf $(DOCDIR) $(srcdir)/$(DOCDIR)

mostlyclean-local:
	rm -rf *.t2d

## ------------------- ##
## RST documentation.  ##
## ------------------- ##

dist_pdf_DATA = README.pdf HACKING.pdf NEWS.pdf
MAINTAINERCLEANFILES = $(dist_pdf_DATA) $(srcdir)/stamp

TEXI2PDF = texi2pdf
TEXI2PDF_FLAGS = --tidy --batch

SUFFIXES = .txt .pdf

# We used to have two .txt.tex and .tex.pdf rules, but BSD Make will always
# rebuilt the missing .tex file.  So use a single rule instead.
.txt.pdf:
	$(RST2LATEX) --halt=warning --input-encoding=iso-8859-1 $< >$*.tex
	$(TEXI2PDF) $(TEXI2PDF_FLAGS) -o $@ $*.tex
	rm -f $*.tex


EXTRA_DIST = README.txt HACKING.txt NEWS.txt \
	     $(srcdir)/stamp $(srcdir)/$(DOCDIR)

## ---------------------------- ##
## Installing on LRDE servers.  ##
## ---------------------------- ##
vcsndldir_data = $(DOCDIR) $(dist_pdf_DATA)

install-epita: $(DOCDIR) $(dist_pdf_DATA)
	$(mkdir_p) $(vcsndldir)
	$(INSTALL_DATA) $(dist_pdf_DATA) $(vcsndldir)
	cp -r $(DOCDIR) $(vcsndldir)
	cd $(dloaddir)/vaucanson
	ln -sf latest-beta $(VERSION)
	cd manual && $(MAKE) $(AM_MAKEFLAGS) install-epita
.PHONY: install-epita
