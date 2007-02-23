## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2007 The Vaucanson Group.
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

#SUBDIRS = vcsn-b vcsn-r vcsn-z vcsn-z-max vcsn-z-min \
	  vcsn-fmp-tdc vcsn-tdc vcsn-z-fmp-tdc vcsn-z-tdc

#OBJDIR = vcsn-b vcsn-z-tdc vcsn-z-fmp-tdc vcsn-z-min \
#	 vcsn-r vcsn-fmp-tdc vcsn-b vcsn-z-max vcsn-tdc vcsn-z

noinst_LTLIBRARIES =
MAINTAINERCLEANFILES =

include vcsn-b/libvcsn-b.mk
include vcsn-r/libvcsn-r.mk
include vcsn-z/libvcsn-z.mk
include vcsn-z-max/libvcsn-z-max.mk
include vcsn-z-min/libvcsn-z-min.mk
include vcsn-fmp-tdc/libvcsn-fmp-tdc.mk
include vcsn-tdc/libvcsn-tdc.mk
include vcsn-z-fmp-tdc/libvcsn-z-fmp-tdc.mk
include vcsn-z-tdc/libvcsn-z-tdc.mk

distclean-local:
	rm -rf vcsn-b vcsn-z-tdc vcsn-z-fmp-tdc vcsn-z-min \
	  vcsn-r vcsn-fmp-tdc vcsn-b vcsn-z-max vcsn-tdc vcsn-z

