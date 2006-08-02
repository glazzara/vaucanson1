include $(srcdir)/../share/make/tex.mk
include $(srcdir)/../share/make/pdf-figs.mk

%.tex: %.cmd
## Eval the cmd to preserve embedded redirections.
## Use the taf-kit wrappers.
	PATH=$(top_builddir)/taf-kit/tests:$$PATH	\
	eval $$(cat $<) >$*.out 2>$*.err;		\
	echo $$? >$*.sta
	rm -f $@
	echo '\begin{shell}'            >> $@
	echo "# \kbd{$$(cat $<)}" >> $@
	if test -s $*.err; then				\
	  sed -n -e 's/\([{|\\}]\)/\\\1/g'		\
		 -e '/./s/.*/error: &/p' $*.err >> $@;	\
	fi
	if test -s $*.out; then			\
	  expand $*.out |			\
	    sed -e 's/\([{|\\}]\)/\\\1/g'	\
		 >>$@;				\
	fi
## Display the exit status only if not 0, as it confuses the
## students to see so many `=> 0'.  But, if there is nothing output
## at all, it is even more confusing, so output `=> 0' only when
## needed.
	if test ! -e $@				\
	   || test $$(cat $*.sta) -ne 0; then	\
	  sed 's/.*/=> &/' $*.sta >> $@;	\
	fi
	echo '\end{shell}' >> $@

%.eps: %.dot
	dot -Tps2 $< -o $@.tmp
# This line: [ /CropBox [36 36 97 89] /PAGES pdfmark
# breaks the ps2pdf output.
	sed '/CropBox/d' $@.tmp >$@
	rm $@.tmp

%.pdf: %.eps
	epstopdf $*.eps -o $*.pdf

## HTML (PNG), using natural size.
%.png: %.dot
	dot -Tpng $*.dot -o $*.png

## And the text...
%.txt: %.dot
	cp $< $@
