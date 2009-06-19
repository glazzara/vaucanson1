#!/bin/sh

CCFILES=`find . -name "*.cc" | wc -l`
HHFILES=`find . -name "*.hh" | wc -l`
HXXFILES=`find . -name "*.hxx" | wc -l`
TOTALCPPFILES=`expr $CCFILES + $HHFILES + $HXXFILES`
CPPFILELIST="`find . -name "*.cc"` `find . -name "*.hh"` `find . -name "*.hxx"`"
TOTALCPPLINES=`cat $CPPFILELIST | wc -l`

SHFILES=`find demo -name "*.sh" | wc -l`
PLFILES=`find bin -name "*.pl" | wc -l`
PLOTFILES=`find demo -name "*.plot.in" | wc -l`
TOTALSCRIPTFILES=`expr $SHFILES + $PLOTFILES`
SCRIPTFILELIST="`find bin -name "*.pl"` `find demo -name "*.sh"` `find . -name "*.plot.in"`"
TOTALSCRIPTLINES=`cat $SCRIPTFILELIST | wc -l`

READMEFILES=`find . -name "README*" | wc -l`
READMEFILELIST="`find . -name "README*"`"
READMELINES=`cat $READMEFILELIST | wc -l`

GITCOMMITS=`git log --pretty=oneline | wc -l`

echo "CBS Statistics - `date`"
echo "------------------------------------------------------------"
echo "C++ source code files: ${TOTALCPPFILES}"
echo "C++ source code lines (including comments): $TOTALCPPLINES"
echo "Script files & helpers: ${TOTALSCRIPTFILES}"
echo "Total script lines (including comments): $TOTALSCRIPTLINES"
echo "README files: ${READMEFILES}"
echo "Total README lines: $READMELINES"
echo "Git repository creation date: Mon Mar 23 20:04:06 2009 +0100"
echo "Git commits on current branch: $GITCOMMITS"
