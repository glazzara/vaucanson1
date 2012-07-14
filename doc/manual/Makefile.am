## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2006, 2007, 2008, 2009, 2011, 2012 The Vaucanson Group.
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

TEXI2PS = texi2dvi
TEXI2PS_FLAGS = --ps --tidy --build-dir=tmp.t2d --batch
PS2PDF = ps2pdf

## ----- ##
## *.tex ##
## ----- ##

.tex.ps:
	$(TEXI2PS) $(TEXI2PS_FLAGS) -o $@.ps $<
.ps.pdf:
	ps2ps $< $<.tmp
	ps2pdf $<.tmp $@

.PHONY: tex-mostlyclean
tex-mostlyclean:
	rm -rf tmp.t2d

# mostlyclean-local is an Automake special target.
.PHONY: mostlyclean-local
mostlyclean-local: tex-mostlyclean


# We compile and ship TAFK.pdf.
manual = $(srcdir)/TAFK.pdf

pdf: $(manual)

dist_pdf_DATA = $(manual)

$(manual): TAFK.tex $(vaucanson_manual_sources)
	$(TEXI2PS) $(TEXI2PS_FLAGS) -o $(@:.pdf=.ps) $(srcdir)/TAFK.tex
	ps2ps $(@:.pdf=.ps) $(@:.pdf=.ps.tmp)
	ps2pdf -sPAPERSIZE=a4 -dOptimize=true $(@:.pdf=.ps.tmp) $@

vaucanson_manual_sources =			\
  TAFK.tex					\
  TFKD-bib-ind.tex				\
  TFKD-ch0.tex					\
  TFKD-ch0-vm.tex				\
  TFKD-ch1.tex					\
  TFKD-ch1-1.tex				\
  TFKD-ch2.tex					\
  TFKD-ch2-1.tex				\
  TFKD-ch2-2.tex				\
  TFKD-ch2-3.tex				\
  TFKD-ch2-4.tex				\
  TFKD-ch2-5.tex				\
  TFKD-ch2-6.tex				\
  TFKD-chA.tex					\
  TFKD-chB.tex					\
  TFKD-chC.tex					\
  TFKD-chD.tex					\
  TFKD-chE.tex					\
  TFKD-chVGI.tex				\
  TFKD-chZ.tex					\
  TFKD-intro.tex				\
  TFKD-table.tex				\
  TFKD-title.tex				\
  texinputs/accent_keys.tex			\
  texinputs/js_macros3.tex			\
  texinputs/js_symboles3.tex

EXTRA_DIST = \
  $(vaucanson_manual_sources) \
  figures

MAINTAINERCLEANFILES = $(dist_pdf_DATA)
maintainer-clean-local:
	rm -rf tmp.t2d
