TEXI2PDF = $(TEXI2DVI) --pdf

dev_tex_TEX = dev.tex
format_tex_TEX = format.tex

dev.dvi: $(dev_tex_TEX)
	$(TEXI2DVI) -o $@ \
	  `test -f '$(dev_tex_TEX)' || echo '$(srcdir)/'`$(dev_tex_TEX)
format.dvi: $(format_tex_TEX)
	$(TEXI2DVI) -o $@ \
	  `test -f '$(format_tex_TEX)' || echo '$(srcdir)/'`$(format_tex_TEX)

dev.pdf: $(dev_tex_TEX)
	$(TEXI2PDF) -o $@ \
	  `test -f '$(dev_tex_TEX)' || echo '$(srcdir)/'`$(dev_tex_TEX)
format.pdf: $(format_tex_TEX)
	$(TEXI2PDF) -o $@ \
	  `test -f '$(format_tex_TEX)' || echo '$(srcdir)/'`$(format_tex_TEX)

.sgml.tex:
	$(SGML2LATEX) $<

SUFFIXES = .tex .sgml

docdir = $(datadir)/doc/@PACKAGE_TARNAME@
dist_doc_DATA = dev.dvi format.dvi dev.pdf format.pdf dev.sgml format.sgml

EXTRA_DIST = dev.sgml format.sgml $(dev_tex_TEX) $(format_tex_TEX)

CLEANFILES = *.aux *blg *.out *.toc *.lot *.tmp *.log
