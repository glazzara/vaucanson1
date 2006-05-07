# Makefile.am
#
#
# $Id$

SUBDIRS = tests	\
	  benchs \
	  demos

if VCSN_TAF_KIT
  SUBDIRS += taf-kit
endif

# The XSD file will be installed in a data directory.
dist_pkgdata_DATA = vaucanson.xsd
