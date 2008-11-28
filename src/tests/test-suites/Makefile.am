## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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

include $(srcdir)/subdirs.mk

$(srcdir)/subdirs.mk: $(top_srcdir)/build-aux/find_tests.sh
	cd $(top_srcdir) && build-aux/find_tests.sh && $(MAKE) am--refresh

EXTRA_DIST += generate-all.sh test-suite.mk
