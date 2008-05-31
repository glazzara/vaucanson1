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

include $(top_srcdir)/vaucanson.mk
include $(top_srcdir)/build-aux/check.mk

AM_CPPFLAGS += $(XSD_CPPFLAGS) -I$(top_srcdir)/lib/krat_exp
LDADD = $(top_builddir)/lib/libkrat_exp.la 

TESTS_ENVIRONMENT = srcdir=$(srcdir)

## ---------------- ##
## Check Programs.  ##
## ---------------- ##

check_PROGRAMS =				\
b_tester					\
fmp_tester					\
geometry_tester					\
label_node_tester				\
r_tester					\
session_tester					\
trans_tester					\
z_max_plus_tester				\
z_min_plus_tester				\
z_tester

b_tester_SOURCES = xml_automaton_tester.cc
b_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="boolean_automaton"

z_tester_SOURCES = xml_automaton_tester.cc
z_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="z_automaton"

r_tester_SOURCES = xml_automaton_tester.cc
r_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="r_automaton"

z_max_plus_tester_SOURCES = xml_automaton_tester.cc
z_max_plus_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="z_max_plus_automaton"

z_min_plus_tester_SOURCES = xml_automaton_tester.cc
z_min_plus_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="z_min_plus_automaton"

fmp_tester_SOURCES = xml_fmp_tester.cc

trans_tester_SOURCES = xml_trans_tester.cc

session_tester_SOURCES = xml_session_tester.cc

geometry_tester_SOURCES = xml_geometry_tester.cc

label_node_tester_SOURCES = xml_label_node_tester.cc


## ------------------------ ##
## Running the test suite.  ##
## ------------------------ ##

nodist_check_SCRIPTS = $(check_PROGRAMS:=.test)
TESTS = $(nodist_check_SCRIPTS)

$(nodist_check_SCRIPTS):
	echo "#! /bin/sh"     	      >$@-t
	echo ". ${srcdir}/tester.sh" >>$@-t
	chmod +x $@-t
	mv $@-t $@

CLEANFILES += 							\
	$(check_PROGRAMS)					\
	$(check_PROGRAMS:_tester=_result.tmp)			\
	$(check_PROGRAMS:_tester=_result.dot.tmp)		\
	$(nodist_check_SCRIPTS)

EXTRA_DIST =						\
	tester.sh					\
	$(check_PROGRAMS:_tester=_ref.xml)		\
	$(check_PROGRAMS:_tester=_ref.dot)
