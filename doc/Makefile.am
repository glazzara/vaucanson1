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

# VCSN_USE_XML is tested in the `xml' subdirectory.

SUBDIRS = makefiles manual xml
include $(srcdir)/doc.mk

dist_doc_DATA = ref.tar.gz

ref: doc.doxy.in
	rm -rf ref
	mkdir -p ref
	$(MAKE) $(AM_MAKEFLAGS) doc.doxy
	$(DOXYGEN) doc.doxy

ref.tar.gz: doc.doxy.in
	$(MAKE) $(AM_MAKEFLAGS) ref
	$(TAR) -czf $@ `test -d ref || echo '$(srcdir)/'`ref

dist_doc_DATA += README.pdf README.tex README.html \
		 FAQ.pdf FAQ.tex FAQ.html \
		 NEWS.pdf NEWS.tex NEWS.html \
	         README-IO.pdf README-IO.tex README-IO.html

EXTRA_DIST = README.txt FAQ.txt NEWS.txt README-IO.txt \
	     share

MAINTAINERCLEANFILES = $(dist_doc_DATA)
maintainer-clean-local:
	rm -rf ref
