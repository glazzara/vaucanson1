# Makefile.am
#
# $Id$

SUBDIRS = tutorial beginner

docdir = $(datadir)/doc/@PACKAGE_TARNAME@
dist_doc_DATA = ref.tar.gz

ref.tar.gz: doc.doxy.in
	mkdir -p ref
	$(DOXYGEN) doc.doxy
	$(TAR) -czf $@ `test -d ref || echo '$(srcdir)/'`ref

MAINTAINERCLEANFILES = ref
