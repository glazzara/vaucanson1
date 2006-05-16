include $(top_srcdir)/doc/doc.mk

SRC_FILES = users_manual.tex vaucanson_toolkit.tex installation.tex
EXTRA_DIST = $(SRC_FILES)

users_manual.pdf: users_manual.dvi
	$(DVIPDF) users_manual.dvi

dist_doc_DATA = users_manual.pdf
