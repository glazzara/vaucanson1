# src/bench/Makefile.am                       -*- Makefile -*-
#
# Vaucanson, a generic library for finite state machines.  
# Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The
# Vaucanson Group.
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
#


SUBDIRS = common determinization 				\
	  minimization_debruijn	minimization_2n derived_terms	\
	  quotient composition eps_removal			\
	  iterators

BENCHDIRS = determinization minimization_debruijn 		\
	    derived_terms minimization_2n quotient		\
	    composition eps_removal				\
	    iterators

bench:
	for f in $(BENCHDIRS); do				\
	  (cd $$f && $(MAKE) $(AM_MAKEFLAGS) bench || exit 1)	\
	done
