## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The Vaucanson Group.
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

# Run "make share-up" to update the files from the share/ directory.
WGET = wget --no-check-certificate
WGETL = $(WGET) https://svn.lrde.epita.fr/svn/lrde-publis/trunk/
SHAREFILES = \
  share/bib/vaucanson.bib \
  share/bin/texi2dvi \
  share/styles/hevea.sty \
  share/styles/ldf/stl.sty \
  share/styles/ldf/vaucanson.sty \
  share/styles/misc.hva \
  share/styles/misc.sty \
  share/styles/myacronym.sty \
  share/styles/mybabel.hva \
  share/styles/mybabel.sty \
  share/styles/mycxx.sty \
  share/styles/myhyperref.hva \
  share/styles/myhyperref.sty \
  share/styles/myifthen.hva \
  share/styles/myifthen.sty \
  share/styles/myindex.hva \
  share/styles/myindex.sty \
  share/styles/texi.hva \
  share/styles/texi.sty \
  share/styles/vaucanson-g.sty \
  share/styles/Vaucanson-G.tex \
  share/styles/VCpatch-pstricks-1-10.tex

.PHONY: share-up
share-up:
	for f in $(SHAREFILES); do \
	  $(WGETL)$$f -O $(top_srcdir)/doc/$$f || exit 1; \
	done

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

uninstall-local:
	chmod -R 700 $(DESTDIR)$(htmldir)/$(DOCDIR)
	rm -rf $(DESTDIR)$(htmldir)/$(DOCDIR)

maintainer-clean-local:
	rm -rf $(DOCDIR) $(srcdir)/$(DOCDIR)

## ------------------- ##
## RST documentation.  ##
## ------------------- ##

dist_pdf_DATA = README.pdf FAQ.pdf HACKING.pdf NEWS.pdf
MAINTAINERCLEANFILES = $(dist_pdf_DATA) $(srcdir)/stamp

TEXI2DVI = $(srcdir)/share/bin/texi2dvi
TEXI2DVI_FLAGS = --tidy --build-dir=tmp.t2d --batch

TEXI2PDF = $(TEXI2DVI) --pdf
TEXI2PDF_FLAGS = $(TEXI2DVI_FLAGS)

SUFFIXES = .txt .tex .pdf

.tex.pdf:
	$(TEXI2PDF) $(TEXI2PDF_FLAGS) -o $@ $<

.txt.tex:
	$(RST2LATEX) --halt=warning --input-encoding=iso-8859-1 $< >$@.tmp
	mv $@.tmp $@


EXTRA_DIST = README.txt FAQ.txt HACKING.txt NEWS.txt \
	     $(SHAREFILES) share/README $(srcdir)/stamp $(srcdir)/$(DOCDIR)

## ------------------ ##
## Unit compilation.  ##
## ------------------ ##

dist_doc_DATA = unit-compile.mk

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
