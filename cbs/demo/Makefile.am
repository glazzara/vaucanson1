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

SUBDIRS = timer bench timer-bench memplot comparison memplot-bench

EXTRA_DIST = generate-plot-files.sh

bench: bench.do

bench.do:
	cd timer-bench && $(MAKE) $(AM_MAKEFLAGS) bench
	cd memplot-bench && $(MAKE) $(AM_MAKEFLAGS) bench
