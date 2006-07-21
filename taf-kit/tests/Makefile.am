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

include check.mk

XFAIL_TESTS =

TESTS =						\
vcsn-b.test					\
vcsn-z.test

EXTRA_DIST = $(TESTS)

# Each test case depends on defs.
check_SCRIPTS = defs vcsn-z vcsn-b

distclean-local:
	-rm -rf testSubDir
