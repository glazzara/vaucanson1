if VCSN_USE_XML

xml_proposal.pdf: xml_proposal.tex
	env TEXINPUTS=$(top_srcdir)/doc:$$TEXINPUTS 		\
		$(TEXI2DVI) $(srcdir)/xml_proposal.tex
	$(DVIPDF) xml_proposal.dvi

docdir = $(datadir)/doc/$(PACKAGE_TARNAME)
CLEANFILES = *.dvi *.aux *blg *.out *.toc *.lot *.tmp *.log

MAINTAINERCLEANFILES = $(dist_doc_DATA)

dist_doc_DATA = xml_proposal.pdf

endif
