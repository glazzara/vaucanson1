# vcsn.m4
# $Id$

AC_DEFUN([VCSN_TESTS], [
if test -d src/tests/tests-suites/$1; then
   VCSN_TESTS_SUBDIRS="$VCSN_TESTS_SUBDIRS $1"
   AC_CONFIG_FILES([src/tests/tests-suites/$1/Makefile])
fi
])
