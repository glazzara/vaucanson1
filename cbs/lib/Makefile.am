## CBS, a C++ benchmarking suite.
##
## Copyright (C) 2007, 2008, 2009 The CBS authors.
##
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License
## as published by the Free Software Foundation; either version 2
## of the License, or (at your option) any later version.
##
## The complete GNU General Public Licence Notice can be found as the
## `COPYING' file in the root directory.
##
## The CBS Authors consists of people listed in the `AUTHORS' file.

include $(top_srcdir)/cbs.mk

AM_CPPFLAGS += $(CXXFLAGS_OPTIMIZE)

lib_LTLIBRARIES = libbench.la
libbench_la_SOURCES = bench.cc			\
                      memplot.cc		\
                      timer.cc			\
                      timer_graph.cc		\
                      timer_gathering.cc
libbench_la_CPPFLAGS = $(AM_CPPFLAGS)
