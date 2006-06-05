#! /bin/sh

tests_m4=build-aux/tests.m4
subdirs_mk=src/tests/test-suites/subdirs.mk
pass=true

tests ()
{
  echo >>$tests_m4.tmp "$@"
}

subdirs ()
{
  echo >>$subdirs_mk.tmp "$@"
}


rm -f $tests_m4.tmp $subdirs_mk.tmp

tests "# Vaucanson test suite.                    -*- Autoconf -*-"
subdirs "## Vaucanson test suite."

tests "AC_CONFIG_FILES(["
subdirs "SUBDIRS = \\"
# We are interested in directories that have a .defs file.
for i in src/tests/test-suites/*
do
  if test -f $i.defs; then
      if test -d $i; then
	  tests   "  $i/Makefile"
	  subdirs "$(basename $i) \\"
      else
	  echo >&2 "$0: warning: defs without a directory: $i"
	  pass=false
      fi
  fi
done
tests "])"
subdirs "  ."

if $pass; then
  build-aux/move-if-change $tests_m4.tmp $tests_m4
  build-aux/move-if-change $subdirs_mk.tmp $subdirs_mk
  exit 0
else
  rm $tests_m4.tmp $subdirs_mk.tmp
  exit 1
fi
