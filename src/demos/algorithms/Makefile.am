# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2009 The Vaucanson Group.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# The complete GNU General Public Licence Notice can be found as the
# `COPYING' file in the root directory.
#
# The Vaucanson Group consists of people listed in the `AUTHORS' file.

include ../demo.mk

AM_CPPFLAGS += $(XSD_CPPFLAGS)

EXTRA_DIST = equivalent_functions.hh

noinst_PROGRAMS = universal aut_are_equivalent exp_are_equivalent

universal_SOURCES = universal.cc

aut_are_equivalent_SOURCES = aut_are_equivalent.cc equivalent_functions.cc
aut_are_equivalent_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/boolean_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::boolean_automaton"

exp_are_equivalent_SOURCES = exp_are_equivalent.cc equivalent_functions.cc
exp_are_equivalent_CPPFLAGS = $(AM_CPPFLAGS)			\
	-DCONTEXT_HEADER="<vaucanson/boolean_automaton.hh>"	\
	-DCONTEXT_NAMESPACE="vcsn::boolean_automaton"
