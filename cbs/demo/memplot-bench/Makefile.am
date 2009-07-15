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

EXTRA_DIST = generate-figures.sh results-memory.plot.in results-time.plot.in

noinst_PROGRAMS = demo-memplot-bench
demo_memplot_bench_SOURCES = main.cc
demo_memplot_bench_LDADD = $(top_builddir)/lib/libbench.la
demo_memplot_bench_CPPFLAGS = $(AM_CPPFLAGS)

bench: all
	./demo-memplot-bench
