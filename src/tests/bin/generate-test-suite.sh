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
    echo '* Arguments are:'
    echo "test directories        : $TEST_DIRS"
    echo "destination directories : $DEST_DIR"
    echo "description files       : $DESCRIPTION_FILE"
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

# Generate corresponding -test.cc
for NAME in $ALL_TEST; do
  BNAME=`basename $NAME`
  FUN_NAME=`echo $BNAME | sed s/'.hh'/''/`
  FUN_SNAME=`echo $FUN_NAME | sed s/_test/''/`
  NAME_TEST_FILE=$NAME
  for TEST_DIR in $TEST_DIRS; do
    NAME_TEST_FILE=`echo $NAME_TEST_FILE | sed s,$TEST_DIR/,,`
  done
    
# Include licence.
  cat > $DEST_DIR/$FUN_SNAME-test.cc <<EOF
/*  Vaucanson, a generic library for finite state machines.
Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.

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
cat >> $DEST_DIR/$FUN_SNAME-test.cc<<EOF
  #include <vaucanson/fundamental/fundamental.hh>
EOF

# Include headers inclusion.
cat $DESCRIPTION_FILE >> $DEST_DIR/$FUN_SNAME-test.cc;

# Include "main".
cat >> $DEST_DIR/$FUN_SNAME-test.cc<<EOF

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

  CHECK_PROG=`echo $FUN_SNAME-test $CHECK_PROG`
  TEST_CC=`echo $FUN_SNAME\_test_SOURCES = $FUN_SNAME-test.cc % $TEST_CC`
done

# Define the include directories.
for TEST_DIR in $TEST_DIRS; do
# FIXME: of course, this does not work in general case.
# FIXME: We must find a way to define the path from 
# FIXME: DEST_DIR to TEST_DIR or to force people to define an absolute TEST_DIR.
# FIXME: for the distributed tests suites, it works
    INCLUDES="-I\$(srcdir)/../$TEST_DIR $INCLUDES"
done

# Generate a Makefile.am
TEST_CC=`echo $TEST_CC | tr '%' '\n'`
cat > $DEST_DIR/Makefile.am << EOF
include \$(top_srcdir)/src/tests/check/Makefile.check
AM_CPPFLAGS += $INCLUDES
check_PROGRAMS=$CHECK_PROG
$TEST_CC
EOF
