# Makefile.am
#
# $Id$

.PHONY: doc

tex_TEX = tutorial.tex

CLEANFILES= *.dvi *.aux *blg *.out *.toc *.lot *.tmp

doc: tutorial.dvi

tutorial.dvi: $(tex_TEX) 
	$(LATEX) `test -f '$(tex_TEX)' || echo '$(srcdir)/'`$(tex_TEX)

