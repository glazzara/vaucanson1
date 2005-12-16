SUBDIRS = makefiles xml
include $(srcdir)/Makefile.doc

dist_doc_DATA = ref.tar.gz

ref: doc.doxy.in
	rm -rf ref
	mkdir -p ref
	$(MAKE) doc.doxy
	$(DOXYGEN) doc.doxy

ref.tar.gz: ref
	$(TAR) -czf $@ `test -d ref || echo '$(srcdir)/'`ref

MAINTAINERCLEANFILES = ref

dist_doc_DATA += README.pdf README.tex README.html \
		 FAQ.pdf FAQ.tex FAQ.html \
		 NEWS.pdf NEWS.tex NEWS.html

EXTRA_DIST = README.txt FAQ.txt NEWS.txt

MAINTAINERCLEANFILES += $(dist_doc_DATA)
