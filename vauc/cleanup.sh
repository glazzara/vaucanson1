#!/bin/sh

find . -name core \
   -or -name \*.out \
   -or -name \*.output \
   -or -name \*~ \
   -or -name \*.log \
| xargs rm -f

if [ "x$1" != "x" ]; then 

find . -name \*.o \
   -or -name \*.lo \
   -or -name \*.a \
   -or -name \*.la \
   -or -name .libs \
| xargs rm -rf

fi

if [ "x$1" = "xall" ]; then

make distclean 2>/dev/null >/dev/null

find . -name .deps \
   -or -name Makefile \
   -or -name Makefile.in \
| xargs rm -rf

rm -f \
 ylwrap \
 libtool \
 aclocal.m4 \
 config.* \
 configure \
 depcomp \
 install-sh \
 ltmain.sh \
 missing \
 mkinstalldirs \
 stamp-h1 config-h.in \
 config/config.guess \
 config/config.* \
 config/depcomp \
 config/install-sh \
 config/ltmain.sh \
 config/missing \
 config/mkinstalldirs \
 config/ylwrap 
rm -rf libltdl autom4te.cache 

fi
