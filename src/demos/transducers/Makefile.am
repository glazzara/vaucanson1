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

SUBDIRS = one_rule_rewriting

AM_CPPFLAGS += $(XSD_CPPFLAGS)

EXTRA_PROGRAMS = u1 t1

demos: $(EXTRA_PROGRAMS)

XML_SAMPLES = $(srcdir)/u1.xml $(srcdir)/t1.xml
EXTRA_DIST = $(XML_SAMPLES)
MAINTAINERCLEANFILES = $(XML_SAMPLES)

u1_SOURCES = u1.cc
t1_SOURCES = t1.cc

$(srcdir)/u1.xml: u1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) u1$(EXEEXT)
	./u1$(EXEEXT) > $@

$(srcdir)/t1.xml: t1.cc $(top_srcdir)/configure.ac
	$(MAKE) $(AM_MAKEFLAGS) t1$(EXEEXT)
	./t1$(EXEEXT) > $@
