xml_proposal.pdf:
	$(TEXI2DVI) $(srcdir)/xml_proposal.tex
	$(DVIPDF) xml_proposal.dvi

docdir = $(datadir)/doc/$(PACKAGE_TARNAME)
CLEANFILES = *.dvi *.aux *blg *.out *.toc *.lot *.tmp *.log

EXTRA_DIST = vaucanson.xsd
MAINTAINERCLEANFILES = $(dist_doc_DATA)

dist_doc_DATA = xml_proposal.pdf
