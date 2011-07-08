## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2009, 2011 The
## Vaucanson Group.
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

LDADD = $(top_builddir)/lib/libvcsn-common.la
AM_CPPFLAGS += -DBENCH_DISABLED

noinst_PROGRAMS = minab sag

nodist_char_zmin_automata_DATA =			\
  minab.xml \
  sag.xml

CLEANFILES += $(nodist_char_zmin_automata_DATA)

minab_CPPFLAGS = $(AM_CPPFLAGS)
minab_SOURCES = minab.cc

minab.xml: minab$(EXEEXT)
	./minab$(EXEEXT) xml >$@.tmp
	mv $@.tmp $@

sag_CPPFLAGS = $(AM_CPPFLAGS)
sag_SOURCES = sag.cc

sag.xml: sag$(EXEEXT)
	./sag$(EXEEXT) xml >$@.tmp
	mv $@.tmp $@

