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

noinst_PROGRAMS = b1 c1 d1

nodist_char_q_automata_DATA =\
  b1.xml				\
  c1.xml				\
  d1.xml

CLEANFILES += $(nodist_char_q_automata_DATA)

b1_CPPFLAGS = $(AM_CPPFLAGS)
b1_SOURCES = b1.cc
b1.xml: b1$(EXEEXT)
	$(AM_V_GEN) ./b1$(EXEEXT) xml >$@.tmp && mv $@.tmp $@

c1_CPPFLAGS = $(AM_CPPFLAGS)
c1_SOURCES = c1.cc
c1.xml: c1$(EXEEXT)
	$(AM_V_GEN) ./c1$(EXEEXT) xml >$@.tmp && mv $@.tmp $@

d1_CPPFLAGS = $(AM_CPPFLAGS)
d1_SOURCES = d1.cc
d1.xml: d1$(EXEEXT)
	$(AM_V_GEN) ./d1$(EXEEXT) xml >$@.tmp && mv $@.tmp $@



