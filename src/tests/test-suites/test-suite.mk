## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2006, 2007, 2009 The Vaucanson Group.
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

## This file is used by the Makefile.am of generated test suites.
include $(top_srcdir)/src/tests/check/check.mk

TESTS += failcomp.sh
EXTRA_DIST = failcomp.sh

AM_CPPFLAGS += $(BOOST_CPPFLAGS) -DEXCEPTION_TRAPS -DVCSN_SRC_DIR=\"'$(top_srcdir)'\"

LDADD += $(top_builddir)/lib/libvcsn-common.la 

TESTS_ENVIRONMENT = CXX="$(CXX)" \
		    CXXFLAGS="$(AM_CPPFLAGS) $(CPPFLAGS)"
## ------------------------ ##
## Makefile.am generation.  ##
## ------------------------ ##

tests_dir = $(top_srcdir)/src/tests
generate_all = $(tests_dir)/test-suites/generate-all.sh
generate_test_suite = $(tests_dir)/bin/generate-test-suite.sh

$(srcdir)/Makefile.am: $(generate_all) $(generate_test_suite)
	cd $(tests_dir)/test-suites && ./generate-all.sh

CLEANFILES += coherence_state_transition_test.xml
