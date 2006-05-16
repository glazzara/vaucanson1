# -*- Makefile -*-

share_dir = $(top_srcdir)/doc/share
# Cannot factor here because Automake needs to be able to read
# the full path and does not accept variables.
include $(top_srcdir)/doc/share/make/share.mk
include $(top_srcdir)/doc/share/make/tex.mk

%.tex: %.txt
	$(RST2TEX) --input-encoding=iso-8859-1 $< >$@

%.html: %.txt
	$(RST2HTML) --input-encoding=iso-8859-1 $< >$@

docdir = $(datadir)/doc/$(PACKAGE_TARNAME)
CLEANFILES = *.dvi *.aux *blg *.out *.toc *.lot *.tmp *.log
