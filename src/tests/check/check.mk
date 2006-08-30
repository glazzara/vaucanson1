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

## This file is used in all the test suites (hand written and
## generated) of libvaucanson.  It is tailored to be used for unit
## tests, that is to say, tests that can simply be run *once*, and
## whose result cannot change if the sources did not change.
## 
## It expects its users to define EXTRA_PROGRAMS, not check_PROGRAMS.
## 
## Enable unit-test supports from our build-aux/check.mk:
LAZY_TEST_SUITE = 1

include $(top_srcdir)/src/tests/check/check-flags.mk
LDADD = $(top_builddir)/src/tests/check/libcheck.a

TESTS = $(EXTRA_PROGRAMS)
TEST_LOGS = $(TESTS:=.log)

# Parallel replacement of Automake's check-TESTS target.
# Include it last: TEST_LOGS has a default value there.
include $(top_srcdir)/build-aux/check.mk
