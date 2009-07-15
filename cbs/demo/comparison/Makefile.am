## CBS, a C++ benchmarking suite.
##
## Copyright (C) 2007, 2009 The CBS Authors.
##
## This program is free software; you can redistribute it and/or
## modify it under the terms of the Do What The Fuck You Want To
## Public License (WTFPL) version 2.
##
## The complete WTFPL license text can be found as the
## `COPYING' file in the root directory.
##
## The CBS Authors consists of people listed in the `AUTHORS' file.

include $(top_srcdir)/cbs.mk

noinst_PROGRAMS = demo-cbs demo-gprof demo-generic

demo_cbs_SOURCES = main.cc
demo_cbs_LDADD = $(top_builddir)/lib/libbench.la
demo_cbs_CPPFLAGS = $(AM_CPPFLAGS)

demo_gprof_SOURCES = main.cc
demo_gprof_LDADD =
demo_gprof_CPPFLAGS = $(AM_CPPFLAGS) -DBENCH_DISABLED -pg
demo_gprof_LDFLAGS = -pg

demo_generic_SOURCES = main.cc
demo_generic_LDADD =
demo_generic_CPPFLAGS = $(AM_CPPFLAGS) -DBENCH_DISABLED
