# Makefile.am
#
#
# $Id$

AUTOMAKE_OPTIONS = foreign 1.7

SUBDIRS = include src doc 

EXTRA_DIST = THANKS README LICENCE 

###
### Autoconf needs additional macros. 
### Tell it where to find them.
###
ACLOCAL_AMFLAGS = -I config
CONFIGURE_DEPENDENCIES = $(srcdir)/config/vcsn.m4
EXTRA_DIST += config/vcsn.m4

###
### Autoconf macros are installable.
###

m4datadir = $(datadir)/aclocal
dist_m4data_DATA = config/vcsn.m4

###
### Check headers for sanity.
###

# This is totally experimental. Comments are welcome.
maintainer-check:
	if cppi --version >/dev/null 2>&1; then \
	  find $(srcdir) -name '*.{cc,hh,hxx}' | \
	    xargs cppi --check; \
	else \
	  echo "$@: GNU cppi is required" >&2; \
	fi
