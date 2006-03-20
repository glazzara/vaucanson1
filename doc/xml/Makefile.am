xml_proposal.pdf: vaucanson-g.sty Vaucanson-G.tex
	$(TEXI2DVI) $(srcdir)/xml_proposal.tex
	$(DVIPDF) xml_proposal.dvi

Vaucanson-G.tex:
	ln -sf $(top_srcdir)/doc/Vaucanson-G.tex $@

vaucanson-g.sty:
	ln -sf $(top_srcdir)/doc/vaucanson-g.sty $@

docdir = $(datadir)/doc/$(PACKAGE_TARNAME)
CLEANFILES = *.dvi *.aux *blg *.out *.toc *.lot *.tmp *.log \
Vaucanson-G.tex vaucanson-g.sty

MAINTAINERCLEANFILES = $(dist_doc_DATA)

dist_doc_DATA = xml_proposal.pdf
