#! /bin/sh

ls -d src/tests/test-suites/*/ | sed 's,.*/\(.*\)/$,VCSN_TESTS([\1]),' > \
	config/tests.m4

