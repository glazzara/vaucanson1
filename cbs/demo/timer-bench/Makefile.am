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

EXTRA_DIST = generate-figures.sh		\
	     timer-scoped-time.plot.in		\
	     timer-many-tasks-time.plot.in	\
	     timer-recursion-memory.plot.in	\
	     timer-recursion-time.plot.in	\
	     timer-scoped-memory.plot.in	\
	     timer-many-tasks-memory.plot.in

noinst_PROGRAMS = demo-timer-bench
demo_timer_bench_SOURCES = main.cc
demo_timer_bench_LDADD = $(top_builddir)/lib/libbench.la
demo_timer_bench_CPPFLAGS = $(AM_CPPFLAGS)

bench: all
	./demo-timer-bench
