## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2006, 2007, 2008, 2009 The Vaucanson Group.
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

all: pdf

include $(top_srcdir)/vaucanson.mk

TEXI2PDF = texi2pdf
TEXI2PDF_FLAGS = --tidy --build-dir=tmp.t2d --batch

## ----- ##
## *.tex ##
## ----- ##

%.pdf: %.tex
	$(TEXI2PDF) $(TEXI2PDF_FLAGS) -o $@ $<

.PHONY: tex-mostlyclean
tex-mostlyclean:
	rm -rf tmp.t2d

# mostlyclean-local is an Automake special target.
.PHONY: mostlyclean-local
mostlyclean-local: tex-mostlyclean


# We compile and ship vaucanson-manual.pdf.
manual = $(srcdir)/vaucanson-manual.pdf

pdf: $(manual)

dist_pdf_DATA = $(manual)

$(manual): $(vaucanson_manual_sources)
	$(TEXI2PDF) $(TEXI2PDF_FLAGS) -o $@ $<

vaucanson_manual_sources =			\
vaucanson-manual.tex				\
vaucanswig.tex					\
developer.tex

EXTRA_DIST = $(vaucanson_manual_sources) $(manual) check_doc.py.in

CLEANFILES += $(srcdir)/check_doc.py
dist_noinst_SCRIPTS = $(srcdir)/check_doc.py

MAINTAINERCLEANFILES = $(vcsndldir_data)
maintainer-clean-local:
	rm -rf tmp.t2d

## ---------------------------- ##
## Installing on LRDE servers.  ##
## ---------------------------- ##

vcsndldir_data =				\
$(dist_pdf_DATA)

install-epita: $(vcsndldir_data)
	$(INSTALL_DATA) $(vcsndldir_data) $(vcsndldir)
.PHONY: install-epita


## ------------ ##
## Deep-clean.  ##
## ------------ ##

# Remove all the is generated, included if it requires maintainer
# tools, but do not call maintainer-clean nor distclean, since we do
# not want to have to reconfigure etc.
deep-clean: clean maintainer-clean-local
	-rm -f $(MAINTAINERCLEANFILES)

$(srcdir)/check_doc.py: check_doc.py.in Makefile.am
	sed 's|[@]vcsn_version[@]|$(VERSION)|' $(srcdir)/check_doc.py.in > $(srcdir)/$@
	chmod a+x $(srcdir)/$@

# Check the user manual
check-local: $(srcdir)/check_doc.py
	$(PYTHON) $(srcdir)/check_doc.py $(srcdir)/vaucanson-manual.tex
