# Makefile.am
#
# $Id$

SUBDIRS= tutorial

doc: doc.doxy	
	cd tutorial && $(MAKE) doc
	@DOXYGEN@ doc.doxy

clean-local:
	rm -fr ref