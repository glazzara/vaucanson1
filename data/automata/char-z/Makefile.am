## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2009 The
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

# Z automata.
noinst_PROGRAMS = c1 d2

nodist_char_z_automata_DATA =		\
  b1.xml				\
  c1.xml				\
  d2.xml

CLEANFILES += $(nodist_char_z_automata_DATA)

# This automaton counts the number of bs.
b1.xml: ../char-b/b1.xml
	sed -e 's/set="B"/set="Z"/g' $< >$@.tmp
	mv $@.tmp $@

c1_CPPFLAGS = $(AM_CPPFLAGS)
c1_SOURCES = c1.cc
c1.xml: c1$(EXEEXT)
	./c1$(EXEEXT) xml >$@.tmp
	mv $@.tmp $@

d2_CPPFLAGS = $(AM_CPPFLAGS)
d2_SOURCES = d2.cc
d2.xml: d2$(EXEEXT)
	./d2$(EXEEXT) xml >$@.tmp
	mv $@.tmp $@
