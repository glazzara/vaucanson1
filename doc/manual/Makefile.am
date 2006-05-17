include $(top_srcdir)/doc/doc.mk

SRC_FILES = \
users_manual.tex \
installation.tex \
vaucanson_toolkit.tex \
vaucanson_library.tex \
images/a1_det.ps

EXTRA_DIST = $(SRC_FILES)

# We use vaucanson-g, which requires plain DVI compilation.
users_manual.pdf: users_manual.dvi
	$(DVIPDF) users_manual.dvi

dist_doc_DATA = users_manual.pdf
