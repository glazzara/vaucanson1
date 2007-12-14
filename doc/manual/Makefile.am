## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2006, 2007 The Vaucanson Group.
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
include $(top_srcdir)/doc/doc.mk

# We ship and compile vaucanson-user-manual.pdf, but
# vaucanson-developer-manual.pdf must be requested by hand.
manual = $(srcdir)/vaucanson-user-manual.pdf

pdf: $(manual)

# We use vaucanson-g, which requires plain DVI compilation.
TEXI2PDF_FLAGS += --dvipdf -I manual.ext

dist_pdf_DATA = $(manual)

$(manual): $(vaucanson_user_manual_sources) $(srcdir)/extex.pl
	$(MAKE) $(AM_MAKEFLAGS) manual.ext
	cd manual.ext && $(MAKE) $(AM_MAKEFLAGS) dvi
	$(TEXI2PDF) $(TEXI2PDF_FLAGS) -o $@ $<

$(srcdir)/vaucanson-developer-manual.pdf: manual.ext $(vaucanson_user_manual_sources)
vaucanson_user_manual_sources =			\
vaucanson-user-manual.tex			\
vaucanson-developer-manual.tex			\
introduction.tex				\
installation.tex				\
taf-kit.tex					\
vaucanswig.tex					\
library.tex					\
developer.tex					\
theory.tex					\
$(srcdir)/automata.tex				\
xml.tex						\
specification.tex				\
$(srcdir)/version.tex

$(srcdir)/automata.tex: generate-automata.sh
# Use the TAF-Kit wrappers.
	PATH=$(top_builddir)/taf-kit/tests:$$PATH \
	$(srcdir)/generate-automata.sh >$@-t
	mv $@-t $@

$(srcdir)/version.tex: $(top_srcdir)/configure.ac
	echo '\def\VcsnVersion{$(VERSION)}' > $*.tmp
	echo "\def\VcsnDate{`LANG=C date +%Y-%m-%d`}" >> $*.tmp
	mv -f $*.tmp $@

EXTRA_DIST = $(vaucanson_user_manual_sources) $(manual)  \
	 generate-automata.sh extex.pl extex.mk

# Extract commands that must be run to produce figures.
manual.ext: $(vaucanson_user_manual_sources) $(srcdir)/extex.pl
	perl -I$(top_srcdir)/build-aux -w	\
	  $(srcdir)/extex.pl			\
	  --output-dir=$@			\
	  --srcdir=$(srcdir)			\
	  --top_srcdir=$(top_srcdir)		\
	  --builddir=.				\
	  --top_builddir=$(top_builddir)	\
          $(vaucanson_user_manual_sources)
	touch $@

MAINTAINERCLEANFILES = $(vcsndldir_data) automata.tex
maintainer-clean-local:
	rm -rf manual.ext tmp.t2d

## ---------------------------- ##
## Installing on LRDE servers.  ##
## ---------------------------- ##

vcsndldir_data =				\
$(dist_pdf_DATA)				\
$(srcdir)/vaucanson-developer-manual.pdf

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
MINIDISTDIR = vaucanson-user-manual
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
