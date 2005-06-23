# Makefile.am
#
# $Id$

SUBDIRS = makefiles xml
include $(srcdir)/Makefile.doc

dist_doc_DATA = ref.tar.gz

ref.tar.gz: doc.doxy.in
	mkdir -p ref
	$(DOXYGEN) doc.doxy
	$(TAR) -czf $@ `test -d ref || echo '$(srcdir)/'`ref

MAINTAINERCLEANFILES = ref

dist_doc_DATA += README.pdf README.tex README.html \
		 INSTALL.pdf INSTALL.tex INSTALL.html \
		 FAQ.pdf FAQ.tex FAQ.html \
		 NEWS.pdf NEWS.tex NEWS.html

EXTRA_DIST = README.txt INSTALL.txt FAQ.txt NEWS.txt

MAINTAINERCLEANFILES += $(dist_doc_DATA)
