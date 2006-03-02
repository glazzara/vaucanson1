SRC_FILES = users_manual.tex vaucanson_toolkit.tex installation.tex

users_manual.pdf: $(SRC_FILES)
	$(TEXI2DVI) $(srcdir)/users_manual.tex
	$(DVIPDF) users_manual.dvi

docdir = $(datadir)/doc/$(PACKAGE_TARNAME)
CLEANFILES = *.dvi *.aux *blg *.out *.toc *.lot *.tmp *.log *.idx

##EXTRA_DIST = vaucanson.xsd

dist_doc_DATA = users_manual.pdf
