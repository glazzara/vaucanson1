# Make sure we don't become promoted as default target.
all:
.PHONY: all

share_style_dir = $(share_dir)/styles
share_bib_dir = $(share_dir)/bib
ChangeLog ?= ChangeLog

TEXI2DVI = $(share_bin_dir)/texi2dvi
TEXI2DVI_FLAGS = --tidy --build-dir=tmp.t2d --batch -I $(share_style_dir) -I $(share_bib_dir)

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



## ------- ##
## rev.tex ##
## ------- ##

# Create a file defining \SvnRev as the revision of the ChangeLog.
# Robust to new existing svn.
svn_to_tex =				\
's<^([\w\s]+):\s+(.*)$$>			\
<$$val = $$2;				\
 ($$var = $$1) =~ s| ||g;		\
 "\\newcommand{\\Svn$$var}{$$val}">ex'

rev.tex: $(ChangeLog)
	if svn --version >/dev/null 2>&1; then			\
	  LC_ALL=C svn info $< |				\
	  (perl -pe $(svn_to_tex) &&				\
	   echo '\newcommand{\SvnRev}{\SvnRevision}')		\
	   >$@;							\
	elif test -f $@; then					\
	  touch $@;						\
	else							\
	  echo '\\newcommand{\\SvnRev}{}' >$@;			\
	fi

CLEANFILES += rev.tex

tex-mostlyclean:
	rm -rf tmp.t2d
.PHONY: tex-mostlyclean
# mostlyclean-local is an Automake special target.
mostlyclean-local: tex-mostlyclean
.PHONY: mostlyclean-local
