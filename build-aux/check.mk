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
# Do not use a regular `.test.log:' rule here, since in that case the
# following rule (without incoming extension) will mask this one.
%.log: %.test
	@if test -f ./$<; then dir=./;			\
	elif test -f $<; then dir=;			\
	else dir="$(srcdir)/"; fi;			\
	$(TESTS_ENVIRONMENT) $${dir}$< >$@-t 2>&1;	\
	case $$?:" $(XFAIL_TESTS) " in			\
	    0:*"$<"*) res="XPASS";;			\
	    0:*)      res="PASS" ;;			\
	    77:*)     res="SKIP" ;;			\
	    *:*"$<"*) res="XFAIL";;			\
	    *:*)      res="FAIL" ;;			\
	   esac;					\
	echo "$$res: $$(basename $<)";			\
	echo "$$res: $$(basename $<)" >$@
	@cat $@-t >>$@
	@rm $@-t

# The exact same commands, but for programs without extensions.
%.log: %
	@if test -f ./$<; then dir=./;			\
	elif test -f $<; then dir=;			\
	else dir="$(srcdir)/"; fi;			\
	$(TESTS_ENVIRONMENT) $${dir}$< >$@-t 2>&1;	\
	case $$?:" $(XFAIL_TESTS) " in			\
	    0:*"$<"*) res="XPASS";;			\
	    0:*)      res="PASS" ;;			\
	    77:*)     res="SKIP" ;;			\
	    *:*"$<"*) res="XFAIL";;			\
	    *:*)      res="FAIL" ;;			\
	   esac;					\
	echo "$$res: $$(basename $<)";			\
	echo "$$res: $$(basename $<)" >$@
	@cat $@-t >>$@
	@rm $@-t

TEST_LOGS ?= $(TESTS:.test=.log)
TEST_SUITE_LOG = test-suite.log
# Run all the tests.
check-TESTS:
	@rm -f $(TEST_SUITE_LOG) $(TEST_LOGS);					\
	$(MAKE) $(TEST_LOGS);							\
	results=$$(for f in $(TEST_LOGS); do sed 1q $$f; done);			\
	all=$$(echo "$$results" | wc -l | sed -e 's/^[ \t]*//');		\
	fail=$$(echo "$$results" | grep -c '^FAIL');				\
	pass=$$(echo "$$results" | grep -c '^PASS');				\
	skip=$$(echo "$$results" | grep -c '^SKIP');				\
	xfail=$$(echo "$$results" | grep -c '^XFAIL');				\
	xpass=$$(echo "$$results" | grep -c '^XPASS');				\
	case fail=$$fail:xfail=$$xfail:xpass=$$xpass in				\
	  fail=0:xfail=0:xpass=*)						\
	    banner="All $$all tests passed";;					\
	  fail=0:xfail=*:xpass=*)						\
	    banner="All $$all tests behaved as expected";			\
	    banner="$$banner ($$xfail expected failures)";;			\
	  fail=*:xfail=*:xpass=0)						\
	    banner="$$fail of $$all tests failed";;				\
	  fail=*:xfail=*:xpass=*)						\
	    banner="$$fail of $$all tests did not behave as expected";		\
	    banner="$$banner ($$xpass unexpected passes)";;			\
	  *)									\
            echo >&2 "incorrect case"; exit 4;;					\
	esac;									\
	for f in $(TEST_LOGS);							\
	do									\
	  case $$(sed 1q $$f) in						\
	    SKIP:*|PASS:*|XFAIL:*);;						\
	    *) cat $$f >>$(TEST_SUITE_LOG);					\
	  esac;									\
	done;									\
	dashes="$$banner";							\
	skipped="";								\
	if test "$$skip" -ne 0; then						\
	  skipped="($$skip tests were not run)";				\
	  test `echo "$$skipped" | wc -c` -le `echo "$$banner" | wc -c` ||	\
	    dashes="$$skipped";							\
	fi;									\
	report="";								\
	if test "$$fail" -ne 0 && test -n "$(PACKAGE_BUGREPORT)"; then		\
	  report="Please report $(TEST_SUITE_LOG) to $(PACKAGE_BUGREPORT)";	\
	  test `echo "$$report" | wc -c` -le `echo "$$banner" | wc -c` ||	\
	    dashes="$$report";							\
	fi;									\
	dashes=`echo "$$dashes" | sed s/./=/g`;					\
	echo "$$dashes";							\
	echo "$$banner";							\
	test -z "$$skipped" || echo "$$skipped";				\
	test -z "$$report" || echo "$$report";					\
	echo "$$dashes";							\
	test "$$fail" -eq 0
