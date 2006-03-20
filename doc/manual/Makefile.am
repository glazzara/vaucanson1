SRC_FILES = users_manual.tex vaucanson_toolkit.tex installation.tex

users_manual.pdf: $(SRC_FILES) Vaucanson-G.tex vaucanson-g.sty
	$(TEXI2DVI) $(srcdir)/users_manual.tex
	$(DVIPDF) users_manual.dvi

Vaucanson-G.tex:
	ln -sf $(top_srcdir)/doc/Vaucanson-G.tex $@

vaucanson-g.sty:
	ln -sf $(top_srcdir)/doc/vaucanson-g.sty $@

docdir = $(datadir)/doc/$(PACKAGE_TARNAME)
CLEANFILES = *.dvi *.aux *blg *.out *.toc *.lot *.tmp *.log *.idx \
Vaucanson-G.tex vaucanson-g.sty

##EXTRA_DIST = vaucanson.xsd

dist_doc_DATA = users_manual.pdf
