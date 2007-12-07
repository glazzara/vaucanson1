share_dir = .
include make/share.mk
include make/tex.mk

QUIET = @
papersdir = /lrde/doc/lrde/papers
papers_DATA = lrde.pdf lrde-private.pdf README-lrde.bib

dloaddir = /lrde/dload/papers
dload_DATA = lrde.pdf bib/lrde.bib


CLEANFILES = lrde.pdf lrde-private.pdf contents.html contents.txt list.bib \
list.pdf diffs.patch contents.bib contents_bib.html

all: check lrde.pdf

## ------- ##
## Check.  ##
## ------- ##

# Our own *.bib that should obey our rules.
BIBS = lrde.bib csi.bib

# We don't use the dependencies here so that all the checks are run.
check:
	$(MAKE) -k check-warning check-bib check-style \
                   check-mnt-dload check-urllrde

maintainer-check: check check-wiki

check-warning:
	$(QUIET)echo >&2 "***"
	$(QUIET)echo >&2 "*** To ignore possible checking error, use -k"
	$(QUIET)echo >&2 "*** But please, first try to fix them"
	$(QUIET)echo >&2 "***"

check-bib:
	$(QUIET)echo >&2 "*** Checking for invalid characters: ..."
	$(QUIET)LC_ALL=C grep '[^[:print:][:blank:]]' bib/*.bib && exit 1; \
	echo >&2 "*** Checking for invalid characters: OK"

check-style:
	$(QUIET)echo >&2 "*** Checking for double-quotes: ..."
	$(QUIET)for b in $(BIBS); do					\
	  LC_ALL=C grep '=[	 ]*"' bib/$$b /dev/null && exit 1;	\
	done;								\
	echo >&2 "*** Checking for double-quotes: OK"

check-mnt-dload:
	$(QUIET)echo >&2 "*** Checking for BibTeX/PDF correspondance: ..."
	$(QUIET)(cd $(papersdir) && ls -1 *.pdf) | \
	   grep -Ev '^lrde(-private)?\.pdf$$' | \
	   sed -e 's/\.pdf$$//' | \
	   sort >/tmp/list.pdf
	$(QUIET)sed -ne '/^@.*{[ \t]*/{s///;s/,//;p}' $(share_bib_dir)/lrde.bib | \
	   sort >/tmp/list.bib
	$(QUIET)if cmp -s /tmp/list.pdf /tmp/list.bib; then :; else	\
	  echo "Files in $(papersdir) not registered in lrde.bib:";	\
	  comm -23 /tmp/list.pdf /tmp/list.bib;				\
	  echo;								\
	  echo "Files not available as PDF in $(papersdir):";		\
	  comm -13 /tmp/list.pdf /tmp/list.bib;				\
	  echo;								\
	  exit 2;							\
	fi
	$(QUIET)echo >&2 "*** Checking for BibTeX/PDF correspondance: OK"

check-urllrde:
	$(QUIET)echo >&2 "*** Checking for urllrde: ..."
	$(QUIET)for b in $(BIBS); do					\
	  bib2bib -q -c 'not urllrde : "."' -oc check.bib		\
	    $(share_bib_dir)/$$b >/dev/null &&				\
	  if test -s check.bib; then					\
	    echo >&2 "$$b: entries that lack an urllrde field:";	\
	    sed >&2 -e 's/^/  /' check.bib;				\
	    fail=1;							\
	  fi &&								\
	  rm -f check.bib;						\
	done;								\
	test -z "$$fail"

check-wiki:
	$(QUIET)for b in $(BIBS); do						\
	  sed -ne 's/.*urllrde.*{\(.*\)\}.*/\1/p' $(share_bib_dir)/$$b |	\
	    while read u;							\
	    do									\
	      if ! wget -q -O /dev/null http://publis.lrde.epita.fr/$$; then	\
	        echo >&2 "$$b: broken urllrde: $$u";				\
	        fail=1;								\
	      fi;								\
	    done;								\
	done; 									\
	test -z "$$fail"


## normalization

bibneat = $(share_bin_dir)/bibneat
.PHONY: neat
neat:
	for b in $(BIBS); do \
	  $(bibneat) $(share_bib_dir)/$$b; \
	done

## ------------------------------- ##
## lrde.pdf and lrde-private.pdf.  ##
## ------------------------------- ##

%.txt: $(share_bib_dir)/%.bib
	rm -f $@.tmp
	$(QUIET)bibtex2html -q $<
	$(QUIET)html2text -nobs $*.html | \
	  sed -e 's/.*\[ bib .*//;/^==*$$/{s/.*//;q;}' >$@.tmp
	chmod a-w $@.tmp
	mv -f $@.tmp $@

# Create a LaTeX document to force the BibTeX check on lrde.bib.
make_bib = $(share_bin_dir)/make-bib.pl
%.tex: $(share_bib_dir)/%.bib
	perl $(make_bib) $(share_bib_dir)/$*.bib >$*.tmp
	chmod a-w $*.tmp
	mv -f $*.tmp $*.tex

lrde.tex:  $(make_bib)

%-private.tex: $(share_bib_dir)/%.bib
	$(make_bib) --with-submitted $(share_bib_dir)/$*.bib >$*-private.tmp
	chmod a-w $*-private.tmp
	mv -f $*-private.tmp $*-private.tex

lrde-private.tex:  $(make_bib)

view: lrde.pdf
	xpdf lrde.pdf


## ------------------ ##
## Wrappers for svn.  ##
## ------------------ ##

diff:
	bin/svndiff

up svnupdate:
	svn up

install: svnupdate $(papers_DATA) $(dload_DATA)
## The "doc" group rights should allow this.
	install -m 644 $(dload_DATA) $(dloaddir)
	install -m 644 $(papers_DATA) $(papersdir)

ci checkin: diff check
	bin/svnci
	$(MAKE) $(MAKEFLAGS) install


## ----------------------- ##
## Updating from masters.  ##
## ----------------------- ##

.PHONY: update update-bib update-styles

update: update-bib
update-bib:
	bin/update-bib

# Sources.
GASTEX_STYLES = http://www.lsv.ens-cachan.fr/~gastin/gastex
FR_BIB_STYLES = http://www.lsv.ens-cachan.fr/~markey/BibTeX/bst

update: update-styles
update-styles:
	wget $(GASTEX_STYLES)/gastex.sty -O styles/gastex.sty
	wget $(GASTEX_STYLES)/gastex.pro -O styles/gastex.pro
	wget http://igm.univ-mlv.fr/~lombardy/Vaucanson-G/vaucanson-g.tgz
	tar zxvf vaucanson-g.tgz
	rm vaucanson-g/VCManual.ps.gz
	mv vaucanson-g/* styles/
	rm -rf vaucanson-g vaucanson-g.tgz
	wget $(FR_BIB_STYLES)/abbrv-fr.bst -O styles/abbrv-fr.bst
	wget $(FR_BIB_STYLES)/abbrvnat-fr.bst -O styles/abbrvnat-fr.bst
	wget $(FR_BIB_STYLES)/alpha-fr.bst -O styles/alpha-fr.bst
	wget $(FR_BIB_STYLES)/apalike-fr.bst -O styles/apalike-fr.bst
	wget $(FR_BIB_STYLES)/ieeetr-fr.bst -O styles/ieeetr-fr.bst
	wget $(FR_BIB_STYLES)/plain-fr.bst -O styles/plain-fr.bst
	wget $(FR_BIB_STYLES)/plainnat-fr.bst -O styles/plainnat-fr.bst
	wget $(FR_BIB_STYLES)/siam-fr.bst -O styles/siam-fr.bst
	wget $(FR_BIB_STYLES)/unsrt-fr.bst -O styles/unsrt-fr.bst
	wget $(FR_BIB_STYLES)/unsrtnat-fr.bst -O styles/unsrtnat-fr.bst
