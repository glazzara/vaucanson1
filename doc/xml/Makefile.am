TEXI2PDF = $(TEXI2DVI) --pdf

docdir = $(datadir)/doc/$(PACKAGE_TARNAME)
dist_tex_TEX = dev.tex format.tex
dist_doc_DATA = dev.txt dev.tex dev.pdf dev.dvi \
                format.txt format.tex format.pdf format.dvi

.txt.tex:
	$(RST2TEX) $< >$@

.tex.pdf:
	$(TEXI2PDF) -o $@ $<

.tex.dvi:
	$(TEXI2DVI) -o $@ $<

CLEANFILES = *.dvi *.aux *blg *.out *.toc *.lot *.tmp *.log
