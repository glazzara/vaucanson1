## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2009 The Vaucanson Group.
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

EXTRA_DIST = one_rule_rewriting.hh one_rule_rewriting.hxx shortest.hh

noinst_PROGRAMS = \
  fibonacci_demo \
  fibonacci_rw \
  fibonacci_rw_comp \
  fibonacci_fmp \
  ORR_demo \
  ORR_iterate \
  ORR_rw \
  ORR_fmp \
  check_rw

LDADD = $(top_builddir)/lib/libvcsn-common.la

fibonacci_demo_SOURCES = fibonacci_demo.cc
fibonacci_rw_comp_SOURCES = fibonacci_rw_composition.cc
fibonacci_rw_SOURCES = fibonacci_rw_gen.cc
fibonacci_fmp_SOURCES = fibonacci_fmp_gen.cc
check_rw_SOURCES = check_rw_composition.cc
ORR_demo_SOURCES = ORR_demo.cc
ORR_iterate_SOURCES = ORR_iterate.cc
ORR_rw_SOURCES = ORR_rw_gen.cc
ORR_fmp_SOURCES = ORR_fmp_gen.cc

check-local: check_rw
	./check_rw
