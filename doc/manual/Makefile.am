## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2006 The Vaucanson Group.
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

# We ship and compiler vaucanson-user-manual.pdf, but
# vaucanson-developer-manual.pdf must be request by hand.
manual = $(srcdir)/vaucanson-user-manual.pdf

pdf: $(manual)

# We use vaucanson-g, which requires plain DVI compilation.
TEXI2PDF_FLAGS += --dvipdf -I manual.ext

dist_pdf_DATA = $(manual)

$(manual): manual.ext $(vaucanson_user_manual_sources)
$(srcdir)/vaucanson-developer-manual.pdf: manual.ext $(vaucanson_user_manual_sources)
vaucanson_user_manual_sources =			\
vaucanson-developer-manual.tex			\
vaucanson-user-manual.tex			\
introduction.tex				\
installation.tex				\
taf-kit.tex					\
library.tex					\
developer.tex					\
automata.tex					\
xml.tex

$(srcdir)/automata.tex: generate-automata.sh
# Use the TAF-Kit wrappers.
	PATH=$(top_builddir)/taf-kit/tests:$$PATH \
	$(srcdir)/generate-automata.sh >$@-t
	mv $@-t $@


EXTRA_DIST = $(vaucanson_user_manual_sources)

# Extract commands that must be run to produce figures.
manual.ext: $(vaucanson_user_manual_sources) $(srcdir)/extex.pl
	$(srcdir)/extex.pl			\
	  --output-dir=$@			\
	  --srcdir=$(srcdir)			\
	  --top_srcdir=$(top_srcdir)		\
	  --builddir=.				\
	  --top_builddir=$(top_builddir)	\
          $(vaucanson_user_manual_sources)
	$(MAKE) -C $@ dvi
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
