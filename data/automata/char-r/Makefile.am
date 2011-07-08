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

noinst_PROGRAMS =

nodist_char_r_automata_DATA = \
  b1.xml				\
  c1.xml				\
  d1.xml

b1.xml: ../char-b/b1.xml
	sed -e 's/set="B"/set="R"/g' ../char-b/b1.xml >$@.tmp
	mv $@.tmp $@

c1.xml: ../char-z/c1.xml
	sed -e 's/set="Z"/set="R"/g' ../char-z/c1.xml >$@.tmp
	mv $@.tmp $@

d1.xml: ../char-z/d1.xml
	sed -e 's/set="Z"/set="R"/g' ../char-z/d1.xml >$@.tmp
	mv $@.tmp $@

CLEANFILES += $(nodist_char_r_automata_DATA)



