# Makefile.am
#
# $Id$

TEXI2PDF = $(TEXI2DVI) --pdf

tex_TEX = help.tex

help_tex_TEX =  macros.tex packages.tex 

help.dvi: $(tex_TEX) $(help_tex_TEX)
	$(TEXI2DVI) `test -f '$(tex_TEX)' || echo '$(srcdir)/'`$(tex_TEX)
help.pdf: $(tex_TEX) $(help_tex_TEX)
	$(TEXI2PDF) `test -f '$(tex_TEX)' || echo '$(srcdir)/'`$(tex_TEX)

docdir = $(datadir)/doc/$(PACKAGE_TARNAME)
dist_doc_DATA = help.dvi help.pdf help.tex macros.tex packages.tex

CLEANFILES = *.dvi *.aux *blg *.out *.toc *.lot *.tmp
