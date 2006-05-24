## ---------------------------------------------------------- ##
## Generating $(manual).pdf from $(manual).tex using dvipdf.  ##
## ---------------------------------------------------------- ##

include $(top_srcdir)/doc/doc.mk

# $(manual_name) and $(manual_sources) must be defined by the includer.

manual = $(srcdir)/$(manual_name).pdf
EXTRA_DIST = $(manual_sources)

pdf: $(manual)

# We use vaucanson-g, which requires plain DVI compilation.  Don't
# depend on users_manual.dvi directly, since it is not shipped, so
# that would trigger a user-side compilation.
$(manual): $(manual_sources) $(share_tex_dependencies)
	$(MAKE) $(AM_MAKEFLAGS) $(manual_name).dvi
# Help dvipdf find the images/ directory.
	TEXINPUTS=$(srcdir): $(DVIPDF) $(manual_name).dvi $(manual)

$(manual_name).dvi: $(manual_sources) $(share_tex_dependencies)
dist_doc_DATA = $(manual)
