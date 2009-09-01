## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2009 The Vaucanson Group.
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

LDADD = $(top_builddir)/lib/libvcsn-common.la

# Note: To enable/disable Libbench in xml tests,
# use the flag -DBENCH_DISABLED below and link
# with $(benchlib) as needed.
AM_CPPFLAGS += $(XSD_CPPFLAGS) -DBENCH_DISABLED

TESTS_ENVIRONMENT = srcdir=$(srcdir)

## ---------------- ##
## Check Programs.  ##
## ---------------- ##

check_PROGRAMS =				\
b_tester					\
fmp_tester					\
z_fmp_tester					\
geometry_tester					\
label_node_tester				\
r_tester					\
trans_tester					\
z_trans_tester					\
z_max_plus_tester				\
z_min_plus_tester				\
z_tester					\
int_b_tester					\
int_z_tester					\
int_z_max_plus_tester				\
int_z_min_plus_tester				\
int_fmp_tester					\
int_z_fmp_tester				\
int_trans_tester				\
int_z_trans_tester


b_tester_SOURCES = xml_automaton_tester.cc
b_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="boolean_automaton"

int_b_tester_SOURCES = xml_automaton_tester.cc
int_b_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="int_boolean_automaton"

z_tester_SOURCES = xml_automaton_tester.cc
z_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="z_automaton"

int_z_tester_SOURCES = xml_automaton_tester.cc
int_z_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="int_z_automaton"

r_tester_SOURCES = xml_automaton_tester.cc
r_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="r_automaton"

z_max_plus_tester_SOURCES = xml_automaton_tester.cc
z_max_plus_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="z_max_plus_automaton" -DMAX_PLUS

int_z_max_plus_tester_SOURCES = xml_automaton_tester.cc
int_z_max_plus_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="int_z_max_plus_automaton" -DMAX_PLUS

z_min_plus_tester_SOURCES = xml_automaton_tester.cc
z_min_plus_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="z_min_plus_automaton" -DMIN_PLUS

int_z_min_plus_tester_SOURCES = xml_automaton_tester.cc
int_z_min_plus_tester_CPPFLAGS = $(AM_CPPFLAGS) -DCONTEXT="int_z_min_plus_automaton" -DMIN_PLUS

fmp_tester_SOURCES = xml_fmp_tester.cc

z_fmp_tester_SOURCES = xml_z_fmp_tester.cc

int_z_fmp_tester_SOURCES = xml_int_z_fmp_tester.cc

int_fmp_tester_SOURCES = xml_int_fmp_tester.cc

trans_tester_SOURCES = xml_trans_tester.cc

z_trans_tester_SOURCES = xml_z_trans_tester.cc

int_trans_tester_SOURCES = xml_int_trans_tester.cc

int_z_trans_tester_SOURCES = xml_int_z_trans_tester.cc

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
