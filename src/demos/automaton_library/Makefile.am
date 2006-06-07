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

include ../demo.mk

GENERATORS = a1 b1 c1

XML_SAMPLES = $(srcdir)/a1.xml $(srcdir)/b1.xml $(srcdir)/c1.xml
EXTRA_DIST = $(XML_SAMPLES) dumper.hcc
MAINTAINERCLEANFILES = $(XML_SAMPLES)

a1_SOURCES = a1.cc
b1_SOURCES = b1.cc
c1_SOURCES = c1.cc

$(srcdir)/a1.xml: a1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) a1$(EXEEXT)
	./a1$(EXEEXT) > $@

$(srcdir)/b1.xml: b1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) b1$(EXEEXT)
	./b1$(EXEEXT) > $@

$(srcdir)/c1.xml: c1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) c1$(EXEEXT)
	./c1$(EXEEXT) > $@


TESTERS    = divkbaseb double_ring ladybird
divkbaseb_SOURCES = divkbaseb.cc
double_ring_SOURCES = double_ring.cc
ladybird_SOURCES = ladybird.cc
