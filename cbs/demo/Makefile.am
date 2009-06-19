## CBS, a C++ benchmarking suite.
##
## Copyright (C) 2007, 2009 The CBS Authors.
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

SUBDIRS = timer bench timer-bench memplot comparison memplot-bench

bench: bench.do

bench.do:
	cd timer-bench && $(MAKE) $(AM_MAKEFLAGS) bench
	cd memplot-bench && $(MAKE) $(AM_MAKEFLAGS) bench
