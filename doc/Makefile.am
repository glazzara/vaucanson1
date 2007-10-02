## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
include $(srcdir)/doc.mk

SUBDIRS = manual xml


## ----------------------- ##
## Doxygen documentation.  ##
## ----------------------- ##

DOCDIR = ref
DOXYFILE = doc.doxy
docs: $(DOXYFILE).in
	rm -rf $(DOCDIR).tmp $(srcdir)/$(DOCDIR)
	$(MAKE) $(AM_MAKEFLAGS) $(DOXYFILE)
	$(DOXYGEN) $(DOXYFILE)
	mv $(DOCDIR).tmp $(srcdir)/$(DOCDIR)

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

## ----------------------- ##
## Doxygen documentation.  ##
## ----------------------- ##

dist_pdf_DATA = README.pdf FAQ.pdf NEWS.pdf
MAINTAINERCLEANFILES = $(dist_pdf_DATA)

EXTRA_DIST = README.tex FAQ.tex NEWS.tex \
	     share

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
