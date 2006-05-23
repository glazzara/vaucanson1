%-handout.tex: %.tex
	perl -pe 's/(documentclass)({.*})/$$1\[handout]$$2/' $< >$@

%-handout-4.pdf: %-handout.pdf
	PATH=$(bin_dir):$$PATH $(bin_dir)/beamer2handout $< 4up $@

clean: handout-clean

handout-clean:
	rm -f *-handout-4.pdf
