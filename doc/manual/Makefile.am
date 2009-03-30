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

share_dir = $(top_srcdir)/doc/share
share_bin_dir = $(share_dir)/bin
share_style_dir = $(share_dir)/styles
share_bib_dir = $(share_dir)/bib

TEXI2DVI = $(share_bin_dir)/texi2dvi
TEXI2DVI_FLAGS = --tidy --build-dir=tmp.t2d --batch -I $(share_style_dir) -I $(share_bib_dir)

TEXI2PDF = $(TEXI2DVI) --pdf
TEXI2PDF_FLAGS = $(TEXI2DVI_FLAGS)

share_tex_dependencies = \
$(wildcard $(share_style_dir)/* $(share_bib_dir)/*)

## ----- ##
## *.tex ##
## ----- ##

%.pdf: %.tex $(share_tex_dependencies)
	$(TEXI2PDF) $(TEXI2PDF_FLAGS) -o $@ $<

%.dvi: %.tex $(share_tex_dependencies)
	$(TEXI2DVI) $(TEXI2DVI_FLAGS) -o $@ $<

.PHONY: tex-mostlyclean
tex-mostlyclean:
	rm -rf tmp.t2d

# mostlyclean-local is an Automake special target.
.PHONY: mostlyclean-local
mostlyclean-local: tex-mostlyclean


# We compile and ship vaucanson-manual.pdf.
manual = $(srcdir)/vaucanson-manual.pdf

pdf: $(manual)

# We use vaucanson-g, which requires plain DVI compilation.
TEXI2PDF_FLAGS += --dvipdf

dist_pdf_DATA = $(manual)

$(manual): $(vaucanson_manual_sources)
	$(TEXI2PDF) $(TEXI2PDF_FLAGS) -o $@ $<

vaucanson_manual_sources =			\
vaucanson-manual.tex				\
introduction.tex				\
installation.tex				\
taf-kit.tex					\
vaucanswig.tex					\
library.tex					\
developer.tex					\
theory.tex					\
automata.tex					\
xml.tex						\
specification.tex				\
version.tex

$(srcdir)/version.tex: $(top_srcdir)/configure.ac
	echo '\def\VcsnVersion{$(VERSION)}' > $*.tmp
	echo "\def\VcsnDate{`LANG=C date +%Y-%m-%d`}" >> $*.tmp
	mv -f $*.tmp $@

EXTRA_DIST = $(vaucanson_manual_sources) $(manual)

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


## ---------- ##
## minidist.  ##
## ---------- ##

# Useful to ship just the sources.  It would be nice to be able to
# ship share/ too, but it's one level higher currently.

EXTRA_MINIDIST = $(EXTRA_DIST)
MINIDISTDIR = vaucanson-manual
# Files to remove from the tarball.
MINIDIST_IGNORE = \
  -name '*~' -o -name '.svn' -o -name '+committed'
minidistdir:
	rm -rf $(MINIDISTDIR)
	mkdir $(MINIDISTDIR)
# Use tar, not cp, to preserve the directory parts (cp bar/baz foo/ yields
# foo/baz, not foo/bar/baz).
	(cd $(srcdir) && tar cf - $(EXTRA_MINIDIST)) | (cd $(MINIDISTDIR) && tar xf -)
	find $(MINIDISTDIR) $(MINIDIST_IGNORE) | xargs rm -fr


minidist: minidistdir
	tar zcf $(MINIDISTDIR).tar.gz $(MINIDISTDIR)
	rm -rf $(MINIDISTDIR)
