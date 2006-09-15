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

include $(top_srcdir)/doc/doc.mk
manual = $(srcdir)/xml_proposal.pdf
pdf: $(manual)

# We use vaucanson-g, which requires plain DVI compilation.
TEXI2PDF_FLAGS += --dvipdf

xml_proposal_sources = \
xml_proposal.tex
$(manual): $(xml_proposal_sources)

dist_pdf_DATA = $(manual)
EXTRA_DIST = $(xml_proposal_sources)
