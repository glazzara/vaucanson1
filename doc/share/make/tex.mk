# Make sure we don't become promoted as default target.
all:

style_dir = $(share_dir)/styles
bib_dir = $(share_dir)/bib

TEXI2DVI = $(bin_dir)/texi2dvi
TEXI2DVI_FLAGS = --tidy --build-dir=tmp.t2d --batch -I figs -I $(style_dir) -I $(bib_dir)

TEXI2PDF = $(TEXI2DVI) --pdf
TEXI2PDF_FLAGS = $(TEXI2DVI_FLAGS)

TEXI2HTML = $(TEXI2DVI) --html
TEXI2HTML_FLAGS = $(TEXI2DVI_FLAGS)

%.pdf: %.tex $(STYLES) $(wildcard $(style_dir)/* $(bib_dir)/*)
	$(TEXI2PDF) $(TEXI2PDF_FLAGS) -o $@ $<

%.dvi: %.tex $(STYLES) $(wildcard $(style_dir)/* $(bib_dir)/*)
	$(TEXI2DVI) $(TEXI2DVI_FLAGS) -o $@ $<

%.html: %.tex $(STYLES) $(wildcard $(style_dir)/* $(bib_dir)/*)
	$(TEXI2HTML) $(TEXI2HTML_FLAGS) -o $@ $<


%.pdf: %.ltx $(STYLES) $(wildcard $(style_dir)/* $(bib_dir)/*)
	$(TEXI2PDF) $(TEXI2PDF_FLAGS) -o $@ $<

%.dvi: %.ltx $(STYLES) $(wildcard $(style_dir)/* $(bib_dir)/*)
	$(TEXI2DVI) $(TEXI2DVI_FLAGS) -o $@ $<

%.html: %.ltx $(STYLES) $(wildcard $(style_dir)/* $(bib_dir)/*)
	$(TEXI2HTML) $(TEXI2HTML_FLAGS) -o $@ $<


# lrde.bib.  Make sure it is always there.
all: $(bib_dir)/lrde.bib
$(bib_dir)/lrde.bib:
	cd $(share_dir) && bin/update-share --lrde.bib


# Handouts.
%-handout-4.pdf: %-handout.pdf
	PATH=$(bin_dir):$$PATH $(bin_dir)/beamer-handout $< $@

tex-mostlyclean:
	rm -rf tmp.t2d

# mostlyclean-local is an Automake special target.
mostlyclean-local: tex-mostlyclean
