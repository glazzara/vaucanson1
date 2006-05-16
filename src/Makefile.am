# Makefile.am
#
#
# $Id$

SUBDIRS = tests	\
	  benchs \
	  demos \
	  $(VCSN_VAUCANSWIG_SUBDIR) \
	  taf-kit

.PHONY: demos benchs

demos:
	cd demos && $(MAKE) $(AM_MAKEFLAGS) demos

benchs:
	cd benchs && $(MAKE) $(AM_MAKEFLAGS) benchs


# The XSD file will be installed in a data directory.
dist_pkgdata_DATA = vaucanson.xsd
