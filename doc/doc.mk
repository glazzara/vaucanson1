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

# Issue these rules before including tex.mk so that txt -> html is
# preferred over txt -> tex -> html.  The latter is longer, but
# because we actually also provide the tex output, so in fact the path
# has the same length: tex -> html.
%.html: %.txt
	$(RST2HTML) --halt=warning --input-encoding=iso-8859-1 $< >$@

%.tex: %.txt
	$(RST2LATEX) --halt=warning --input-encoding=iso-8859-1 $< >$@

share_dir = $(top_srcdir)/doc/share
# Cannot factor here because Automake needs to be able to read
# the full path and does not accept variables.
include $(top_srcdir)/doc/share/make/share-am.mk
include $(top_srcdir)/doc/share/make/tex.mk

# Disable rules from share/ we don't use, and that lead to circular
# tex -> txt -> tex dependencies.
%.txt: %.tex $(share_tex_dependencies)
