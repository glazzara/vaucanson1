## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2006 The Vaucanson Group.
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

include $(top_srcdir)/src/tests/check/check.mk

XFAIL_TESTS = assert_test$(EXEEXT)

EXTRA_PROGRAMS = assert_test koenig unique selectors static random \
	check_limits bitset window char_traits

check_limits_SOURCES = limits.cc
assert_test_SOURCES = assert_test.cc
koenig_SOURCES = koenig.cc
unique_SOURCES = unique.cc
selectors_SOURCES = selectors.cc
static_SOURCES = static.cc
random_SOURCES = random.cc
bitset_SOURCES = bitset.cc
window_SOURCES = window.cc
char_traits_SOURCES = char_traits.cc
