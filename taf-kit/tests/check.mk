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


# Override the definition from Automake to generate a log file
# with failed tests.

SUFFIXES = .log .test
# From a test file to a log file.
.test.log:
	@$(TESTS_ENVIRONMENT) $< >$@-t 2>&1;	\
	case $$?:" $(XFAIL_TESTS) " in		\
	    0:*"$<"*) res="XPASS";;		\
	    0:*)      res="PASS" ;;		\
	    77:*)     res="SKIP" ;;		\
	    *:*"$<"*) res="XFAIL";;		\
	    *:*)      res="FAIL" ;;		\
	   esac;				\
	echo "$$(basename $<): $$res";		\
	echo "$$(basename $<): $$res" >$@;	\
	case $$res in				\
	  XFAIL | XPASS | FAIL) cat $@-t >>$@;;	\
	esac;					\
	rm $@-t;

TEST_LOGS = $(TESTS:.test=.log)

# Run all the tests.
check-TESTS:
	@rm -f $(TEST_LOGS);									   \
	$(MAKE) $(TEST_LOGS);									   \
	results=$$(for f in $(TEST_LOGS); do sed 1q $$f; done);					   \
	all=$$(echo "$$results" | wc -l);							   \
	fail=$$(echo "$$results" | grep 'FAIL' | wc -l);					   \
	pass=$$(echo "$$results" | grep 'PASS' | wc -l);					   \
	skip=$$(echo "$$results" | grep 'SKIP' | wc -l);					   \
	xfail=$$(echo "$$results" | grep 'XFAIL' | wc -l);					   \
	xpass=$$(echo "$$results" | grep 'XPASS' | wc -l);					   \
	if test "$$fail" -eq 0; then								   \
	  if test "$$xfail" -eq 0; then								   \
	    banner="All $$all tests passed";							   \
	  else											   \
	    banner="All $$all tests behaved as expected ($$xfail expected failures)";		   \
	  fi;											   \
	else											   \
	  if test "$$xpass" -eq 0; then								   \
	    banner="$$fail of $$all tests failed";						   \
	  else											   \
	    banner="$$fail of $$all tests did not behave as expected ($$xpass unexpected passes)"; \
	  fi;											   \
	fi;											   \
	dashes="$$banner";									   \
	skipped="";										   \
	if test "$$skip" -ne 0; then								   \
	  skipped="($$skip tests were not run)";						   \
	  test `echo "$$skipped" | wc -c` -le `echo "$$banner" | wc -c` ||			   \
	    dashes="$$skipped";									   \
	fi;											   \
	report="";										   \
	if test "$$fail" -ne 0 && test -n "$(PACKAGE_BUGREPORT)"; then				   \
	  report="Please report to $(PACKAGE_BUGREPORT)";					   \
	  test `echo "$$report" | wc -c` -le `echo "$$banner" | wc -c` ||			   \
	    dashes="$$report";									   \
	fi;											   \
	dashes=`echo "$$dashes" | sed s/./=/g`;							   \
	echo "$$dashes";									   \
	echo "$$banner";									   \
	test -z "$$skipped" || echo "$$skipped";						   \
	test -z "$$report" || echo "$$report";							   \
	echo "$$dashes";									   \
	cat $(TEST_LOGS) >test-suite.log;							   \
	test "$$fail" -eq 0
