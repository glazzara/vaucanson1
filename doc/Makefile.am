# VCSN_USE_XML is tested in the `xml' subdirectory.

SUBDIRS = makefiles manual xml
include $(srcdir)/Makefile.doc

dist_doc_DATA = ref.tar.gz

ref: doc.doxy.in
	rm -rf ref
	mkdir -p ref
	$(MAKE) $(AM_MAKEFLAGS) doc.doxy
	$(DOXYGEN) doc.doxy

ref.tar.gz: doc.doxy.in
	$(MAKE) $(AM_MAKEFLAGS) ref
	$(TAR) -czf $@ `test -d ref || echo '$(srcdir)/'`ref

MAINTAINERCLEANFILES = ref

dist_doc_DATA += README.pdf README.tex README.html \
		 FAQ.pdf FAQ.tex FAQ.html \
		 NEWS.pdf NEWS.tex NEWS.html \
	         README-IO.pdf README-IO.tex README-IO.html

EXTRA_DIST = README.txt FAQ.txt NEWS.txt README-IO.txt

MAINTAINERCLEANFILES += $(dist_doc_DATA)
