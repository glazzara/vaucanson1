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

## ---------------------------------------------------------- ##
## Generating $(manual).pdf from $(manual).tex using dvipdf.  ##
## ---------------------------------------------------------- ##

include $(top_srcdir)/doc/doc.mk

# $(manual_name) and $(manual_sources) must be defined by the includer.

manual = $(srcdir)/$(manual_name).pdf
EXTRA_DIST = $(manual_sources)

pdf: $(manual)

# We use vaucanson-g, which requires plain DVI compilation.  Don't
# depend on users_manual.dvi directly, since it is not shipped, so
# that would trigger a user-side compilation.
$(manual): $(manual_sources) $(share_tex_dependencies)
	$(MAKE) $(AM_MAKEFLAGS) $(manual_name).dvi
# Help dvipdf find the images/ directory.
	TEXINPUTS=$(srcdir): $(DVIPDF) $(manual_name).dvi $(manual)

$(manual_name).dvi: $(manual_sources) $(share_tex_dependencies)
dist_doc_DATA = $(manual)
