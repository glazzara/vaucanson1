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

include $(top_srcdir)/vaucanson.mk

EXTRA_PROGRAMS = t1 u1

dist_tdc_automata_DATA =			\
	$(srcdir)/t1.xml			\
	$(srcdir)/u1.xml

EXTRA_DIST = $(XML_SAMPLES)
MAINTAINERCLEANFILES = $(dist_tdc_automata_DATA)

t1_SOURCES = t1.cc

$(srcdir)/t1.xml: t1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) t1$(EXEEXT)
	./t1$(EXEEXT) >$@.tmp
	mv $@.tmp $@


u1_SOURCES = u1.cc

$(srcdir)/u1.xml: u1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) u1$(EXEEXT)
	./u1$(EXEEXT) >$@.tmp
	mv $@.tmp $@
