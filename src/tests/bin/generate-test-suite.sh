#!/bin/sh

# Check args
if [ $# -le 2 ]; then
  echo 'usage: '
  echo 'generate-test-suite destination_directory description_file tests_dirs'
  exit 1
fi

DEST_DIR=$1
DESCRIPTION_FILE=$2
shift 2
TEST_DIRS=$@

# Verbose mode
if [ -n "$VERBOSE" ]; then
  cat << EOF
* Arguments are:
 test directories        : $TEST_DIRS
 destination directories : $DEST_DIR
 description files       : $DESCRIPTION_FILE
EOF
fi

# if DEST_DIR does not exists
if [ ! -d $DEST_DIR ]; then
    mkdir $DEST_DIR
fi

# Get all _test.hh
ALL_TEST=''
for TEST_DIR in $TEST_DIRS; do
    ALL_TEST="$ALL_TEST `find $TEST_DIR/ -name \*_test.hh`"
done

# Get all _failcomp.hh (Tests which are expected not to compile).
ALL_FAILCOMP=''
for TEST_DIR in $TEST_DIRS; do
    ALL_FAILCOMP="$ALL_FAILCOMP `find $TEST_DIR/ -name \*_failcomp.hh`"
done

#
# For each header file in $1, this function generates a corresponding .cc
# file which includes a license, the .def definitions, a inclusion to the
# header file and a main() function.
#
# All the header files in $1 must be ended with a common suffix given to this
# function in $2.
#
# As another output, this function prints a space separated list with the names
# of the generated .cc files, without the extension.
#
generate_CCs()
{
  TESTS="$1"
  SUFFIX="$2"

  # Generate corresponding .cc
  for NAME in $TESTS; do
    BNAME=`basename $NAME`
    FUN_NAME=`echo $BNAME | sed s/'.hh'/''/`
    FUN_SNAME=`echo $FUN_NAME | sed s/"_$SUFFIX"/''/`
    NAME_TEST_FILE=$NAME
    for TEST_DIR in $TEST_DIRS; do
      NAME_TEST_FILE=`echo $NAME_TEST_FILE | sed s,$TEST_DIR//\*,,`
    done

    # Include licence.
    cat > $DEST_DIR/$FUN_SNAME-$SUFFIX.cc <<EOF
/*  Vaucanson, a generic library for finite state machines.
Copyright (C) 2001, 2002, 2004 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
EOF

    # Include necessary Vaucanson header
    cat >> $DEST_DIR/$FUN_SNAME-"$SUFFIX".cc<<EOF
#include <cassert>
#include <vaucanson/design_pattern/design_pattern.hh>
EOF

    # Include headers inclusion.
    cat $DESCRIPTION_FILE >> $DEST_DIR/$FUN_SNAME-$SUFFIX.cc;

    # Include "main".
    cat >> $DEST_DIR/$FUN_SNAME-$SUFFIX.cc<<EOF

#include <check/tester.hh>
#include <$NAME_TEST_FILE>

  int main(int argc, char **argv)
  {
  using namespace vcsn;
  tests::verbose_level verbose = tests::low;
  srand(time(0));

  if (argc > 1)
    {
      if (argv[1] == std::string("--no-verbose"))
	verbose = tests::none;
      else if (argv[1] == std::string ("--high-verbose"))
	verbose = tests::high;
      else
	verbose = tests::low;
    };
    tests::Tester t(verbose);
    if ($FUN_NAME<TEST_STATIC_ARGS>(t))
      return EXIT_SUCCESS;
    else
      return EXIT_FAILURE;
  }

EOF

    # CHECK_PROG=`echo $FUN_SNAME-$SUFFIX $CHECK_PROG`
    # TEST_CC=`echo $FUN_SNAME\_test_SOURCES = $FUN_SNAME-$SUFFIX.cc % $TEST_CC`
    printf $FUN_SNAME-$SUFFIX' '
  done
  printf '\n'
}

CHECK_PROG=`generate_CCs "$ALL_TEST" test`
FAILCOMP_PROG=`generate_CCs "$ALL_FAILCOMP" failcomp`

# Define the include directories.
for TEST_DIR in $TEST_DIRS; do
# FIXME: Of  course, this  does not work  in general case.
# FIXME: We must find a way to define  the path from DEST_DIR to TEST_DIR
# FIXME: or to force  people to define an absolute  TEST_DIR.
# FIXME: for the distributed tests suites, it works
    INCLUDES="-I\$(srcdir)/../$TEST_DIR $INCLUDES"
done

#
# Generates the script to check failed compilations.
#
FAILCOMP_SCRIPT=$DEST_DIR/failcomp.sh
cat > $FAILCOMP_SCRIPT << \EOF
#! /bin/sh

fail()
{
  echo "FAIL: Program $1 succeed to compile."
  exit 1
}

EOF

for PROG in $FAILCOMP_PROG; do
  cat >> $FAILCOMP_SCRIPT << EOF
CMD="\$CXX \$CXXFLAGS -c \$srcdir/$PROG.cc"
echo "*** THIS COMPILATION IS EXPECTED TO FAIL, THIS IS NOT A BUG ***"
echo \$CMD
\$CMD && fail $PROG
echo "*** END OF FAILED COMPILATION, THIS IS NOT A BUG ***"

EOF
done

echo "exit 0" >> $FAILCOMP_SCRIPT
chmod 755 $FAILCOMP_SCRIPT

#
# Generate a Makefile.am
#
cat > $DEST_DIR/Makefile.am << EOF
include \$(top_srcdir)/src/tests/check/Makefile.check
AM_CPPFLAGS += $INCLUDES
AM_CPPFLAGS += -DEXCEPTION_TRAPS
AM_CPPFLAGS += -DVCSN_SRC_DIR=\"'\$(top_srcdir)'\"

TESTS_ENVIRONMENT = /usr/bin/env CXX="\$(CXX)" CXXFLAGS="\$(AM_CPPFLAGS)"
TESTS += failcomp.sh
check_PROGRAMS = $CHECK_PROG

EXTRA_DIST = failcomp.sh

EOF

for PROG in $CHECK_PROG; do
  PROG_CANON=`echo $PROG | sed s/-/_/g`
  echo "${PROG_CANON}_SOURCES = $PROG.cc" >> $DEST_DIR/Makefile.am
done
