# Makefile.am
#
# $Id$

TEXI2PDF = $(TEXI2DVI) --pdf

# tex_TEX = tutorial.tex

# tutorial_tex_TEX =  macros.tex packages.tex definitions.tex

# tutorial.dvi: $(tex_TEX) $(tutorial_tex_TEX)
#	$(TEXI2DVI) `test -f '$(tex_TEX)' || echo '$(srcdir)/'`$(tex_TEX)
#tutorial.pdf: $(tex_TEX) $(tutorial_tex_TEX)
#	$(TEXI2PDF) `test -f '$(tex_TEX)' || echo '$(srcdir)/'`$(tex_TEX)

docdir = $(datadir)/doc/@PACKAGE_TARNAME@
# dist_doc_DATA = tutorial.dvi tutorial.pdf tutorial.tex macros.tex \
#                 packages.tex definitions.tex

CLEANFILES = *.dvi *.aux *blg *.out *.toc *.lot *.tmp
