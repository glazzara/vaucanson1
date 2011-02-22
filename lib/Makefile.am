## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2007, 2008, 2009 The Vaucanson Group.
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

include $(top_srcdir)/vaucanson.mk

AUTOMAKE_OPTIONS = subdir-objects

lib_LTLIBRARIES =
MAINTAINERCLEANFILES =

include src/libcommon.mk
include vcsn-b/libvcsn-b.mk
include vcsn-int-b/libvcsn-int-b.mk
include vcsn-r/libvcsn-r.mk
include vcsn-q/libvcsn-q.mk
include vcsn-z/libvcsn-z.mk
include vcsn-int-z/libvcsn-int-z.mk
include vcsn-z-max/libvcsn-z-max.mk
include vcsn-z-min/libvcsn-z-min.mk
include vcsn-fmp-tdc/libvcsn-fmp-tdc.mk
include vcsn-tdc/libvcsn-tdc.mk
include vcsn-z-fmp-tdc/libvcsn-z-fmp-tdc.mk
include vcsn-z-tdc/libvcsn-z-tdc.mk
include vcsn-int-fmp-tdc/libvcsn-int-fmp-tdc.mk
include vcsn-int-z-fmp-tdc/libvcsn-int-z-fmp-tdc.mk
include vcsn-char-char-b/libvcsn-char-char-b.mk
include vcsn-char-char-z/libvcsn-char-char-z.mk
include vcsn-char-int-b/libvcsn-char-int-b.mk
include vcsn-int-int-b/libvcsn-int-int-b.mk
include vcsn-int-int-z/libvcsn-int-int-z.mk

maintainer-clean-local:
	rm -rf $(top_builddir)/lib/vcsn-b		\
	       $(top_builddir)/lib/vcsn-int-b		\
	       $(top_builddir)/lib/vcsn-r		\
	       $(top_builddir)/lib/vcsn-q		\
	       $(top_builddir)/lib/vcsn-z		\
	       $(top_builddir)/lib/vcsn-int-z		\
	       $(top_builddir)/lib/vcsn-z-min		\
	       $(top_builddir)/lib/vcsn-z-max		\
	       $(top_builddir)/lib/vcsn-z-fmp-tdc	\
	       $(top_builddir)/lib/vcsn-int-z-fmp-tdc	\
	       $(top_builddir)/lib/vcsn-z-tdc		\
	       $(top_builddir)/lib/vcsn-fmp-tdc		\
	       $(top_builddir)/lib/vcsn-int-fmp-tdc	\
	       $(top_builddir)/lib/vcsn-tdc		\
	       $(top_builddir)/lib/vcsn-char-char-b	\
	       $(top_builddir)/lib/vcsn-char-char-z	\
	       $(top_builddir)/lib/vcsn-char-int-b	\
	       $(top_builddir)/lib/vcsn-int-int-b	\
	       $(top_builddir)/lib/vcsn-int-int-z
	rm -rf $(top_srcdir)/lib/vcsn-b			\
	       $(top_srcdir)/lib/vcsn-int-b		\
	       $(top_srcdir)/lib/vcsn-r			\
	       $(top_srcdir)/lib/vcsn-q			\
	       $(top_srcdir)/lib/vcsn-z			\
	       $(top_srcdir)/lib/vcsn-int-z		\
	       $(top_srcdir)/lib/vcsn-z-min		\
	       $(top_srcdir)/lib/vcsn-z-max		\
	       $(top_srcdir)/lib/vcsn-z-fmp-tdc		\
	       $(top_srcdir)/lib/vcsn-int-z-fmp-tdc	\
	       $(top_srcdir)/lib/vcsn-z-tdc		\
	       $(top_srcdir)/lib/vcsn-fmp-tdc		\
	       $(top_srcdir)/lib/vcsn-int-fmp-tdc	\
	       $(top_srcdir)/lib/vcsn-tdc		\
	       $(top_srcdir)/lib/vcsn-char-char-b	\
	       $(top_srcdir)/lib/vcsn-char-char-z	\
	       $(top_srcdir)/lib/vcsn-char-int-b	\
	       $(top_srcdir)/lib/vcsn-int-int-b		\
	       $(top_srcdir)/lib/vcsn-int-int-b
