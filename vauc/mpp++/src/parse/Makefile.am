# Makefile.am
#
#
INCLUDES = -I$(srcdir)/.. 

AM_YFLAGS = -dv 

noinst_LTLIBRARIES = libparse.la

libparse_la_SOURCES = \
   class_spec_parse.hh \
   class_spec.h class_spec.yy \
   class_spec_scan.cc \
   fun_spec_parse.hh \
   fun_spec.h fun_spec.yy \
   fun_spec_scan.cc \
   module_spec_parse.hh \
   module_spec.h module_spec.yy \
   module_spec_scan.cc \
   location.hh location.cc \
   libparse.hh libparse.cc

EXTRA_DIST = fun_spec_scan.ll module_spec_scan.ll class_spec_scan.ll

LEX_OUTPUT_ROOT = lex.yy

fun_spec_scan.cc: fun_spec_scan.ll
	$(LEX) $< && mv $(LEX_OUTPUT_ROOT).c tmpscan.cc
	-cat tmpscan.cc | \
	sed -e 's/lex.yy.c/fun_spec_scan.cc/g' \
	-e 's/class *istream/#include <iostream> $$ using std::istream;/' | \
	grep -v isatty | \
	tr '$$' '\n' > fun_spec_scan.cc
	rm -f tmpscan.cc

module_spec_scan.cc: module_spec_scan.ll
	$(LEX) $< && mv $(LEX_OUTPUT_ROOT).c tmpscan.cc
	-cat tmpscan.cc | \
	sed -e 's/lex.yy.c/module_spec_scan.cc/g' \
	-e 's/class *istream/#include <iostream> $$ using std::istream;/' | \
	grep -v isatty | \
	tr '$$' '\n' > module_spec_scan.cc
	rm -f tmpscan.cc

class_spec_scan.cc: class_spec_scan.ll
	$(LEX) $< && mv $(LEX_OUTPUT_ROOT).c tmpscan.cc
	-cat tmpscan.cc | \
	sed -e 's/lex.yy.c/class_spec_scan.cc/g' \
	-e 's/class *istream/#include <iostream> $$ using std::istream;/' | \
	grep -v isatty | \
	tr '$$' '\n' > class_spec_scan.cc
	rm -f tmpscan.cc

