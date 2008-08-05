## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The Vaucanson Group.
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

include $(top_srcdir)/build-aux/check.mk

TESTS =						\
  vcsn-char-b.test				\
  vcsn-char-z.test				\
  vcsn-char-fmp.test				\
  vcsn-int-b.test				\
  vcsn-int-z.test				\
  vcsn-int-fmp.test				\
  completeness.test

XFAIL_TESTS = completeness.test

EXTRA_DIST = $(TESTS)				\
  automata/char-b/ambiguous1.xml		\
  automata/char-b/ambiguous2.xml		\
  automata/char-b/b_to_transpose.xml		\
  automata/char-b/b_transposed.xml		\
  automata/char-b/non_ambiguous1.xml		\
  automata/char-b/void_b_automaton.xml		\
  automata/char-fmp/inverted_t1.xml		\
  automata/char-fmp/t1_compose_u1.xml		\
  automata/char-fmp/t2_u-compose_u2.xml		\
  automata/char-fmp/t2.xml			\
  automata/char-fmp/u2.xml			\
  automata/char-z/standard_c1.xml		\
  automata/char-z/void_z_automaton.xml		\
  automata/int-b/int-b.xml			\
  automata/int-z/int-z.xml

# Each test case depends on defs.
check_SCRIPTS =					\
  defs						\
  vcsn-char-b					\
  vcsn-char-fmp					\
  vcsn-char-z					\
  vcsn-int-b					\
  vcsn-int-fmp					\
  vcsn-int-z

distclean-local:
	-rm -rf $(TESTS:.test=.dir)
