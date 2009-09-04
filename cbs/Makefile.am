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

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = lib include bin

EXTRA_DIST = README README_LIBBENCH NEWS COPYING \
	     m4/ax_boost_base.m4 cbs.mk cbs.xsd bootstrap

bench:
	cd demo && $(MAKE) $(AM_MAKEFLAGS) bench
