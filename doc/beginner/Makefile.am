# Makefile.am
#
# $Id$

include $(srcdir)/../Makefile.doc

dist_doc_DATA = help.tex macros.tex packages.tex 

help.dvi: $(dist_tex_TEX) $(dist_help_tex_TEX)
help.pdf: $(dist_tex_TEX) $(dist_help_tex_TEX)

dist_doc_DATA += help.dvi help.pdf 

MAINTAINERCLEAN = $(dist_doc_DATA)
