#! /bin/sh

pass=true

# We are interested in directories that have a .defs file.
for i in src/tests/test-suites/*
do
  if test -f $i.defs; then
      if test -d $i; then
	  echo "VCSN_TESTS([$(basename $i)])"
      else
	  echo >&2 "$0: warning: defs without a directory: $i"
	  pass=false
      fi
  fi
done > build-aux/tests.m4

$pass
