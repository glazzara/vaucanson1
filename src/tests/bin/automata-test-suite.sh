#!/bin/sh 

# Check args
if [ $# -le 3 ]; then
  echo 'usage: '
  echo 'autamata-test-suite destination_directory includes_file automaton_type tests_dir'
  exit 1
fi

DEST_DIR=$1
INCLUDES_FILE=$2
AUTOTYPE=$3
TEST_DIR=$4

# Verbose mode

# Get all _test.hh
ALL_TEST=`find $TEST_DIR/automata -name \*_test.hh`

# Generate corresponding -test.cc
for NAME in $ALL_TEST; do
  echo $NAME
  BNAME=`basename $NAME`
  echo $BNAME
  FUN_NAME=`echo $BNAME | sed s/'.hh'/''/`
  echo $FUN_NAME
  FUN_SNAME=`echo $FUN_NAME | sed s/_test/''/`
  echo $FUN_SNAME
  TEST_DIR_ECHAP=`echo $TEST_DIR | sed -e s/'\\/'/'\\\\\\/'/`
  echo $TEST_DIR_ECHAP
  NAME_TEST_FILE=`echo $NAME | sed s/"$TEST_DIR_ECHAP"// | sed s/'\\/'// `
  echo $NAME_TEST_FILE
`cat > $DEST_DIR/$FUN_SNAME-test.cc << EOF
/*  Vaucanson, a generic library for finite state machines.
Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.

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
`
  `
  cat $INCLUDES_FILE >> $DEST_DIR/$FUN_SNAME-test.cc;
  cat >> $DEST_DIR/$FUN_SNAME-test.cc << EOF
  #include <check/tests_stuff.hh>
  #include <$NAME_TEST_FILE>

  int main(int argc, char **argv)
  {
  using namespace vcsn;
  using namespace vcsn::tools;

  tests::verbose_level_e verbose = tests::low;
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
    if ($FUN_NAME<$AUTOTYPE>(t)) 
      return EXIT_SUCCESS;
    else
      return EXIT_FAILURE;
  }
  `
  CHECK_PROG=`echo $FUN_SNAME-test $CHECK_PROG`
  TEST_CC=`echo $FUN_SNAME\_test_SOURCES = $FUN_SNAME-test.cc % $TEST_CC`
done

# Generate a Makefile.am
TEST_CC=`echo $TEST_CC | tr '%' '\n'`

`cat > $DEST_DIR/Makefile.am << EOF
include \\\$(top_srcdir)/src/tests/check/Makefile.check
check_PROGRAMS=$CHECK_PROG
$TEST_CC
`
