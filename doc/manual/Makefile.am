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

.tex.pdf:
	$(TEXI2PDF) $(TEXI2PDF_FLAGS) -o $@ $<

.PHONY: tex-mostlyclean
tex-mostlyclean:
	rm -rf tmp.t2d

# mostlyclean-local is an Automake special target.
.PHONY: mostlyclean-local
mostlyclean-local: tex-mostlyclean


# We compile and ship taf-kit-manual.pdf.
manual = $(srcdir)/taf-kit-manual.pdf

pdf: $(manual)

dist_pdf_DATA = $(manual)

$(manual): taf-kit-manual.tex
	$(TEXI2PDF) $(TEXI2PDF_FLAGS) -o $@ $(srcdir)/taf-kit-manual.tex

vaucanson_manual_sources =			\
taf-kit-manual.tex				\
vaucanswig.tex					\
developer.tex

EXTRA_DIST = $(vaucanson_manual_sources)

MAINTAINERCLEANFILES = $(dist_pdf_DATA)
maintainer-clean-local:
	rm -rf tmp.t2d

maintainer-check: taf-kit-manual.tex
	grep "^\\\\def\\\\VcsnVersion{$(VERSION)}" taf-kit-manual.tex
