# design_pattern/Makefile.am
#
#
# $Id$




include ../check/Makefile.check

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
	intrinsics_ops_opt

#	element-full-test

intrinsics_orphanage_SOURCES = intrinsics_orphanage.cc intrinsics.hh
intrinsics_link_SOURCES = intrinsics_link.cc intrinsics.hh
intrinsics_extra_SOURCES = intrinsics_extra.cc intrinsics.hh
intrinsics_default_SOURCES = intrinsics_default.cc intrinsics.hh
intrinsics_convert_SOURCES = intrinsics_convert.cc intrinsics.hh
intrinsics_assign_SOURCES = intrinsics_assign.cc intrinsics.hh
intrinsics_ops_SOURCES = intrinsics_ops.cc intrinsics.hh

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

EXTRA_DIST = design_pattern-test.hh
