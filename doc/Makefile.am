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

SUBDIRS = makefiles manual xml


## ----------------------- ##
## Doxygen documentation.  ##
## ----------------------- ##

all: $(srcdir)/ref
$(srcdir)/ref: doc.doxy.in
	rm -rf ref.tmp $(srcdir)/ref
	$(MAKE) $(AM_MAKEFLAGS) doc.doxy
	$(DOXYGEN) doc.doxy
	mv ref.tmp $(srcdir)/ref

install-data-local:
	rm -rf $(DESTDIR)$(htmldir)/ref
	$(mkdir_p) $(DESTDIR)$(htmldir)
	cp -r $(srcdir)/ref $(DESTDIR)$(htmldir)

dist_pdf_DATA = README.pdf FAQ.pdf NEWS.pdf

EXTRA_DIST = README.tex FAQ.tex NEWS.tex \
	     share

MAINTAINERCLEANFILES = $(dist_pdf_DATA)
maintainer-clean-local:
	rm -rf ref $(srcdir)/ref

## ---------------------------- ##
## Installing on LRDE servers.  ##
## ---------------------------- ##
vcsndldir_data = ref $(dist_pdf_DATA)

install-epita: ref $(dist_pdf_DATA)
	$(mkdir_p) $(vcsndldir)
	$(INSTALL_DATA) $(dist_pdf_DATA) $(vcsndldir)
	cp -r ref $(vcsndldir)
	cd $(dloaddir)/vaucanson
	ln -sf latest-beta $(VERSION)
	cd manual && $(MAKE) $(AM_MAKEFLAGS) install-epita
.PHONY: install-epita
