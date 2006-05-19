include $(top_srcdir)/doc/doc.mk

SRC_FILES = \
users_manual.tex \
installation.tex \
vaucanson_toolkit.tex \
vaucanson_library.tex \
images/a1_det.ps

EXTRA_DIST = $(SRC_FILES)

# We use vaucanson-g, which requires plain DVI compilation.
manual = vaucanson-users-manual.pdf
pdf: $(manual)
$(manual): users_manual.dvi
	$(DVIPDF) users_manual.dvi $(manual)

dist_doc_DATA = $(manual)
