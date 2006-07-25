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

include $(top_srcdir)/src/tests/check/check.mk

check_PROGRAMS = \
	intrinsics_orphanage \
	intrinsics_link \
	intrinsics_extra \
	intrinsics_default \
	intrinsics_convert \
	intrinsics_assign \
	intrinsics_ops \
	intrinsics_orphanage_opt \
	intrinsics_link_opt \
	intrinsics_extra_opt \
	intrinsics_default_opt \
	intrinsics_convert_opt \
	intrinsics_assign_opt \
	intrinsics_ops_opt \
        intrinsics_size \
        intrinsics_size_opt \
	element-full-test

intrinsics_orphanage_SOURCES = intrinsics_orphanage.cc intrinsics.hh
intrinsics_link_SOURCES = intrinsics_link.cc intrinsics.hh
intrinsics_extra_SOURCES = intrinsics_extra.cc intrinsics.hh
intrinsics_default_SOURCES = intrinsics_default.cc intrinsics.hh
intrinsics_convert_SOURCES = intrinsics_convert.cc intrinsics.hh
intrinsics_assign_SOURCES = intrinsics_assign.cc intrinsics.hh
intrinsics_ops_SOURCES = intrinsics_ops.cc intrinsics.hh
intrinsics_size_SOURCES = intrinsics_size.cc intrinsics.hh
element_full_test_SOURCES = element-full-test.cc

intrinsics_orphanage_opt_SOURCES = $(intrinsics_orphanage_SOURCES)
intrinsics_orphanage_opt_CXXFLAGS = $(AM_CXXFLAGS) $(CXXFLAGS_OPTIMIZE)
intrinsics_link_opt_SOURCES = $(intrinsics_link_SOURCES)
intrinsics_link_opt_CXXFLAGS = $(AM_CXXFLAGS) $(CXXFLAGS_OPTIMIZE)
intrinsics_extra_opt_SOURCES = $(intrinsics_extra_SOURCES)
intrinsics_extra_opt_CXXFLAGS = $(AM_CXXFLAGS) $(CXXFLAGS_OPTIMIZE)
intrinsics_default_opt_SOURCES = $(intrinsics_default_SOURCES)
intrinsics_default_opt_CXXFLAGS = $(AM_CXXFLAGS) $(CXXFLAGS_OPTIMIZE)
intrinsics_convert_opt_SOURCES = $(intrinsics_convert_SOURCES)
intrinsics_convert_opt_CXXFLAGS = $(AM_CXXFLAGS) $(CXXFLAGS_OPTIMIZE)
intrinsics_assign_opt_SOURCES = $(intrinsics_assign_SOURCES)
intrinsics_assign_opt_CXXFLAGS = $(AM_CXXFLAGS) $(CXXFLAGS_OPTIMIZE)
intrinsics_ops_opt_SOURCES = $(intrinsics_ops_SOURCES)
intrinsics_ops_opt_CXXFLAGS = $(AM_CXXFLAGS) $(CXXFLAGS_OPTIMIZE)
intrinsics_size_opt_SOURCES = $(intrinsics_size_SOURCES)
intrinsics_size_opt_CXXFLAGS = $(AM_CXXFLAGS) $(CXXFLAGS_OPTIMIZE)

EXTRA_DIST = design_pattern-test.hh
