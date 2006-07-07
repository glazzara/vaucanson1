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


include $(top_srcdir)/src/vaucanson.mk
AM_CPPFLAGS += $(XSD_CPPFLAGS)

TESTS_ENVIRONMENT= SRCDIR=$(srcdir)

b_tester_SOURCES = xml_automaton_tester.cc
b_tester_CPPFLAGS = $(AM_CPPFLAGS)				\
	-DCONTEXT_HEADER="<vaucanson/boolean_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::boolean_automaton"

z_tester_SOURCES = xml_automaton_tester.cc
z_tester_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/z_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::z_automaton"

r_tester_SOURCES = xml_automaton_tester.cc
r_tester_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/r_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::r_automaton"

z_max_plus_tester_SOURCES = xml_automaton_tester.cc
z_max_plus_tester_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/z_max_plus_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::z_max_plus_automaton"

z_min_plus_tester_SOURCES = xml_automaton_tester.cc
z_min_plus_tester_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/z_min_plus_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::z_min_plus_automaton"

fmp_tester_SOURCES = xml_fmp_tester.cc

trans_tester_SOURCES = xml_trans_tester.cc

session_tester_SOURCES = xml_session_tester.cc

geometry_tester_SOURCES = xml_geometry_tester.cc

label_node_tester_SOURCES = xml_label_node_tester.cc

Progs =	b_tester				\
	r_tester				\
	z_tester				\
	z_max_plus_tester			\
	z_min_plus_tester			\
	fmp_tester				\
	trans_tester				\
	session_tester				\
	geometry_tester				\
	label_node_tester

check_SCRIPTS = 				\
	tester.sh

if XML_CHECK
  TESTS = $(check_SCRIPTS)
  check_PROGRAMS = $(Progs)
else
  EXTRA_PROGRAMS = $(Progs)
endif

CLEANFILES = 					\
	b_result.tmp				\
	fmp_result.tmp				\
	trans_result.tmp			\
	z_result.tmp				\
	session_result.tmp			\
	z_max_plus_result.tmp			\
	r_result.tmp				\
	z_min_plus_result.tmp			\
	b_result.dot.tmp			\
	fmp_result.dot.tmp			\
	trans_result.dot.tmp			\
	z_result.dot.tmp			\
	session_result.dot.tmp			\
	z_max_plus_result.dot.tmp		\
	r_result.dot.tmp			\
	z_min_plus_result.dot.tmp		\
	geometry_result.tmp			\
	geometry_result.dot.tmp			\
	label_node_result.tmp			\
	label_node_result.dot.tmp

EXTRA_DIST =					\
	tester.sh				\
	b_ref.xml				\
	z_ref.xml				\
	r_ref.xml				\
	z_max_plus_ref.xml			\
	z_min_plus_ref.xml			\
	fmp_ref.xml				\
	trans_ref.xml				\
        b_ref.dot				\
        fmp_ref.dot				\
        r_ref.dot				\
        trans_ref.dot				\
        z_max_plus_ref.dot			\
        z_min_plus_ref.dot			\
        z_ref.dot				\
        b_ref.xml				\
        fmp_ref.xml				\
        r_ref.xml				\
        trans_ref.xml				\
        z_max_plus_ref.xml			\
        z_min_plus_ref.xml			\
        z_ref.xml				\
	session_ref.xml				\
	session_ref.dot				\
	geometry_ref.xml			\
	geometry_ref.dot			\
	label_node_ref.xml			\
	label_node_ref.dot
