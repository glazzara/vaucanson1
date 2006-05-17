# -*- Makefile -*-

# Issue these rules before including tex.mk so that txt -> html is
# preferred over txt -> tex -> html.  The latter is longer, but
# because we actually also provide the tex output, so in fact the path
# has the same length: tex -> html.
%.html: %.txt
	$(RST2HTML) --input-encoding=iso-8859-1 $< >$@

%.tex: %.txt
	$(RST2TEX) --input-encoding=iso-8859-1 $< >$@

share_dir = $(top_srcdir)/doc/share
# Cannot factor here because Automake needs to be able to read
# the full path and does not accept variables.
include $(top_srcdir)/doc/share/make/share.mk
include $(top_srcdir)/doc/share/make/tex.mk

docdir = $(datadir)/doc/$(PACKAGE_TARNAME)
CLEANFILES = *.dvi *.aux *blg *.out *.toc *.lot *.tmp *.log
