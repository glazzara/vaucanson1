# Makefile.am
#
# $Id$


include Makefile.flags

check_LIBRARIES = libcheck.a

TESTS = assert_test
XFAIL_TESTS = assert_test$(EXEEXT)
check_PROGRAMS = assert_test
assert_test_SOURCES = assert_test.cc


libcheck_a_SOURCES =				\
  tests_stuff.hh				\
  tests_stuff.cc					

EXTRA_DIST = Makefile.flags Makefile.check
