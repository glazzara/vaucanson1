share_dir = .
include make/share.mk
include make/tex.mk

QUIET = @
papersdir = /lrde/doc/lrde/papers
papers_DATA = lrde.pdf lrde-private.pdf README-lrde.bib

dloaddir = /lrde/dload/papers
dload_DATA = lrde.pdf bib/lrde.bib


CLEANFILES = $(papers_DATA) $(dload_DATA) contents.html contents.txt list.bib \
list.pdf diffs.patch contents.bib contents_bib.html

all: check lrde.pdf

## ------- ##
## Check.  ##
## ------- ##

check: check-warning check-bib check-mnt-dload check-urllrde

maintainer-check: check check-wiki

check-warning:
	$(QUIET)echo >&2 "***"
	$(QUIET)echo >&2 "*** To ignore possible checking error, use -k"
	$(QUIET)echo >&2 "*** But please, first try to fix them"
	$(QUIET)echo >&2 "***"

check-bib:
	$(QUIET)echo >&2 "*** Checking for invalid characters: ..."
	$(QUIET)LC_ALL=C grep '[^[:print:][:blank:]]' bib/*.bib || exit 0
	$(QUIET)echo >&2 "*** Checking for invalid characters: OK"

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
	$(QUIET)bib2bib -c 'not urllrde : "."' -oc check.bib $(share_bib_dir)/lrde.bib >/dev/null 2>&1
	$(QUIET)if test -s check.bib; then					\
	  echo >&2 "lrde.bib entries that lack a urllrde field:";	\
	  sed >&2 -e 's/^/  /' check.bib;				\
	  exit 2;							\
	fi
	rm -f check.bib
	$(QUIET)echo >&2 "*** Checking for urllrde: OK"

check-wiki:
	$(QUIET)sed -ne 's/.*urllrde.*{\(.*\)\}.*/\1/p' $(share_bib_dir)/lrde.bib | \
	  while read u;								    \
	  do									    \
	    if ! wget -q -O /dev/null http://publis.lrde.epita.fr/$$; then	    \
	      echo >&2 "broken urllrde: $$u";					    \
	      fail=1;								    \
	    fi;									    \
	  done;									    \
	test -z "$$fail"

## ------------------------------- ##
## lrde.pdf and lrde-private.pdf.  ##
## ------------------------------- ##

%.txt: $(share_bib_dir)/%.bib
	rm -f $@.tmp
	$(QUIET)bibtex2html -q $<
	$(QUIET)html2text -nobs $*.html | \
	  sed -e 's/.*\[ bib .*//;/^==*$$/{s/.*//;q;}' >$@.tmp
	mv $@.tmp $@

# Create a LaTeX document to force the BibTeX check on lrde.bib.
make_bib = $(share_bin_dir)/make-bib.pl
%.tex: $(share_bib_dir)/%.bib $(make_bib)
	$(make_bib) $(share_bib_dir)/$*.bib >$*.tmp
	mv $*.tmp $*.tex

%-private.tex: $(share_bib_dir)/%.bib $(share_bin_dir)/make-bib.pl
	$(make_bib) --with-submitted $(share_bib_dir)/$*.bib >$*-private.tmp
	mv $*-private.tmp $*-private.tex


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

.PHONY: update

BIB_EXTERNALS = kernighan richie strategoxt
update:
	cd bib && chmod a+w $(BIB_EXTERNALS:=.bib)
	wget http://netlib.bell-labs.com/cm/cs/bib/bwk.bib -O bib/kernighan.bib
	wget http://cm.bell-labs.com/cm/cs/bib/dmr.bib -O bib/richie.bib
	wget http://www.cs.uu.nl/~visser/strategoxt/strategoxt.bib -O bib/strategoxt.bib
# There are many missing commas in this bibtex.
	cd bib && perl -pi -e 's/(.\})$/\1,/g' $(BIB_EXTERNALS:=.bib)
# Avoid accidental edition.
	cd bib && chmod a-w $(BIB_EXTERNALS:=.bib)
