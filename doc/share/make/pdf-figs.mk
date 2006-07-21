# Rules to convert several common figure formats to formats well
# supported by pdflatex (png, jpg, pdf).

# Formats to convert to PDF.
SHARE_EXTS_TO_PDF = dot fig fdp gif id tif
# Formats to convert to PNG.
SHARE_EXTS_TO_PNG = dia

# FILES
# convert_ext SRC-EXT, DST-EXT, FILEs
# -----------------------------------
# Return the sorted list of $(FILES) with SRC-EXT as extension,
# changing to DST-EXT.
share_convert_ext =					\
   $(sort						\
          $(patsubst %.$(1),%.$(2),			\
                     $(filter %.$(1),$(3))))


# FILES
# convert_exts SRC-EXTS, DST-EXT, FILES
# -------------------------------------
# Map all the extensions in SRC-EXTS to DST-EXT of the $(FILES) list.
share_convert_exts =				\
$(foreach ext,					\
          $(1),					\
          $(call share_convert_ext,$(ext),$(2),$(3)))


# FILES
# share_convert_to_pdf FILES
# --------------------------
# Choose the most appropriate format for PDFLaTeX for the FILES.
# Beware that no recognized formats are left out.
share_convert_to_pdf =						\
    $(call share_convert_exts,$(SHARE_EXTS_TO_PDF),pdf,$(1))	\
    $(call share_convert_exts,$(SHARE_EXTS_TO_PNG),png,$(1))


# There seems to be more bugs in dia -> fig -> pdf than dia -> png.
%.png: %.dia
	dia -n -e $@ $<

%.png: %.fdp
	fdp -Tpng $< -o $@


## This does not work properly, especially when the output is bigger
## than A4, in which case ps2epsi crops.
##
## %.eps: %.dot
## 	dot -Gpage=595.842 -Tps2 $< -o $*.ps
## # This line: [ /CropBox [36 36 97 89] /PAGES pdfmark
## # breaks the ps2pdf output.
## 	sed -i '/CropBox/d' $*.ps
## 	ps2epsi $*.ps $@

%.fig: %.dot
	dot -Tfig $< -o $@

%.fig: %.fdp
	fdp -Tfig $< -o $@
## There is a bug in fdp's fig output, see Debian bug 373005.
	perl -0777 -pi -e 's/^2 3 0.*\n.*\n//m' $@

%.pdf: %.fig
	fig2dev -Lpdf -p dummy $< $@

%.pdf: %.gif
	convert $< $@

%.pdf: %.id
	epstopdf $< -o $@

%.pdf: %.eps
	epstopdf $< -o $@

%.pdf: %.jpg
	convert $< $@

%.pdf: %.png
	convert $< $@

%.pdf: %.tif
	convert $< $@
