# Make sure we don't become promoted as default target.
all:

share_style_dir = $(share_dir)/styles
share_bib_dir = $(share_dir)/bib

TEXI2DVI = $(share_bin_dir)/texi2dvi
TEXI2DVI_FLAGS = --tidy --build-dir=tmp.t2d --batch -I figs -I $(share_style_dir) -I $(share_bib_dir)

TEXI2PDF = $(TEXI2DVI) --pdf
TEXI2PDF_FLAGS = $(TEXI2DVI_FLAGS)

TEXI2HTML = $(TEXI2DVI) --html
TEXI2HTML_FLAGS = $(TEXI2DVI_FLAGS)

TEXI2TEXT = $(TEXI2DVI) --text
TEXI2TEXT_FLAGS = $(TEXI2DVI_FLAGS)

TEXI2INFO = $(TEXI2DVI) --info
TEXI2INFO_FLAGS = $(TEXI2DVI_FLAGS)

share_tex_dependencies = \
$(STYLES) \
$(share_bib_dir)/lrde.bib \
$(wildcard $(share_style_dir)/* $(share_bib_dir)/*)


## ----- ##
## *.tex ##
## ----- ##

%.pdf: %.tex $(share_tex_dependencies)
	$(TEXI2PDF) $(TEXI2PDF_FLAGS) -o $@ $<

%.dvi: %.tex $(share_tex_dependencies)
	$(TEXI2DVI) $(TEXI2DVI_FLAGS) -o $@ $<

%.html: %.tex $(share_tex_dependencies)
	$(TEXI2HTML) $(TEXI2HTML_FLAGS) -o $@ $<

%.txt: %.tex $(share_tex_dependencies)
	$(TEXI2TEXT) $(TEXI2TEXT_FLAGS) -o $@ $<

%.info: %.tex $(share_tex_dependencies)
	$(TEXI2INFO) $(TEXI2INFO_FLAGS) -o $@ $<


## ----- ##
## *.ltx ##
## ----- ##

%.pdf: %.ltx $(share_tex_dependencies)
	$(TEXI2PDF) $(TEXI2PDF_FLAGS) -o $@ $<

%.dvi: %.ltx $(share_tex_dependencies)
	$(TEXI2DVI) $(TEXI2DVI_FLAGS) -o $@ $<

%.html: %.ltx $(share_tex_dependencies)
	$(TEXI2HTML) $(TEXI2HTML_FLAGS) -o $@ $<

%.txt: %.ltx $(share_tex_dependencies)
	$(TEXI2TEXT) $(TEXI2TEXT_FLAGS) -o $@ $<

%.info: %.ltx $(share_tex_dependencies)
	$(TEXI2INFO) $(TEXI2INFO_FLAGS) -o $@ $<


# lrde.bib.  Make sure it is always there.
# all: $(share_bib_dir)/lrde.bib
$(share_bib_dir)/lrde.bib:
	cd $(share_dir)/.. && share/bin/update-share --lrde.bib


# Handouts.
%-handout-4.pdf: %-handout.pdf
	PATH=$(share_bin_dir):$$PATH $(share_bin_dir)/beamer2handout $< 4up $@

tex-mostlyclean:
	rm -rf tmp.t2d

# mostlyclean-local is an Automake special target.
mostlyclean-local: tex-mostlyclean
