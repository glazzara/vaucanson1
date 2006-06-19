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

# We ship and compiler vaucanson-user-manual.pdf, but
# vaucanson-developer-manual.pdf must be request by hand.
manual = $(srcdir)/vaucanson-user-manual.pdf

pdf: $(manual)

# We use vaucanson-g, which requires plain DVI compilation.
TEXI2PDF_FLAGS += --dvipdf

dist_doc_DATA = $(manual)

$(manual): $(vaucanson_user_manual_sources)
$(srcdir)/vaucanson-developer-manual.pdf: $(vaucanson_user_manual_sources)
vaucanson_user_manual_sources =			\
vaucanson-developer-manual.tex			\
vaucanson-user-manual.tex			\
installation.tex				\
taf-kit.tex					\
library.tex					\
developer.tex					\
images/a1_det.ps

EXTRA_DIST = $(vaucanson_user_manual_sources)
