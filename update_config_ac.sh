#!/bin/sh

tests=`find src/tests/tests-suites -name \*.defs | \
       sed 's,.*/\(.*\)\.defs,VCSN_TESTS([\1])\\\\,'`

mv configure.ac configure.ac.bak

sed "/GENERATED LINES/,/END OF GENERATED LINES/c \\
dnl GENERATED LINES FOR TESTS - DO NOT EDIT\\
$tests
dnl END OF GENERATED LINES FOR TESTS - DO NOT EDIT" configure.ac.bak > \
configure.ac
