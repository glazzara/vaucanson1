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

AM_CPPFLAGS =					\
-I$(top_builddir)				\
-I$(top_builddir)/include			\
-I$(top_srcdir)/include				\
$(BOOST_CPPFLAGS)

AM_CXXFLAGS = $(CXXFLAGS_STRICT)

AM_LDFLAGS = $(BOOST_LDFLAGS)
