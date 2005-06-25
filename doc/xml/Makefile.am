LATEX = latex
DVIPDF = dvipdf

xml_proposal.pdf:
	$(LATEX) xml_proposal.tex
	$(LATEX) xml_proposal.tex
	$(DVIPDF) xml_proposal.dvi


docdir = $(datadir)/doc/$(PACKAGE_TARNAME)
CLEANFILES = *.dvi *.aux *blg *.out *.toc *.lot *.tmp *.log

EXTRA_DIST = vaucanson.xsd
MAINTAINERCLEANFILES = $(dist_doc_DATA)

dist_doc_DATA = xml_proposal.pdf
