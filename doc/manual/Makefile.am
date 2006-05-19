include $(top_srcdir)/doc/doc.mk

manual = $(srcdir)/vaucanson-users-manual.pdf
manual_sources = \
users_manual.tex \
installation.tex \
vaucanson_toolkit.tex \
vaucanson_library.tex \
images/a1_det.ps
EXTRA_DIST = $(manual_sources)

pdf: $(manual)

# We use vaucanson-g, which requires plain DVI compilation.  Don't
# depend on users_manual.dvi directly, since it is not shipped, so
# that would trigger a user-side compilation.
$(manual): $(manual_sources)
	$(MAKE) $(AM_MAKEFLAGS) users_manual.dvi
	$(DVIPDF) users_manual.dvi $(manual)

dist_doc_DATA = $(manual)
