#!/bin/sh

# Check args
if [ $# -le 2 ]; then
  echo 'usage: '
  echo '$0 destination_directory description_file tests_dirs'
  exit 1
fi

dest_dir=$1
description_file=$2
shift 2
test_dirs=$@


# dump_header COMMENT-PREFIX
# --------------------------
# Dump the part signaling a file is generated.
dump_header ()
{
    sed -e "s/^/$1 /" << EOF

DO NOT EDIT BY HAND - Generated by $0

Vaucanson, a generic library for finite state machines.
Copyright (C) 2001, 2002, 2004, 2005, 2006 The Vaucanson Group.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

The complete GNU General Public Licence Notice can be found as the
\`COPYING' file in the root directory.

The Vaucanson Group consists of people listed in the \`AUTHORS' file.

EOF
}




# Verbose mode
if [ -n "$VERBOSE" ]; then
  cat << EOF
* Arguments are:
 test directories        : $test_dirs
 destination directories : $dest_dir
 description files       : $description_file
EOF
fi

# if $dest_dir does not exists
if [ ! -d $dest_dir ]; then
    mkdir $dest_dir
fi

# Get all _test.hh
all_test=''
for test_dir in $test_dirs; do
    all_test="$all_test $(find $test_dir/ -name \*_test.hh)"
done

# Get all _failcomp.hh (Tests which are expected not to compile).
all_failcomp=''
for test_dir in $test_dirs; do
    all_failcomp="$all_failcomp $(find $test_dir/ -name \*_failcomp.hh)"
done


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
  local tests=$1
  local suffix=$2

  # Generate corresponding .cc
  for name in $tests
  do
    bname=$(basename $name)
    fun_name=$(echo $bname | sed s/'.hh'/''/)
    fun_sname=$(echo $fun_name | sed s/"_$suffix"/''/)
    name_test_file=$name
    for test_dir in $test_dirs; do
      name_test_file=$(echo $name_test_file | sed s,$test_dir//\*,,)
    done


    # Include licence.
    dump_header "//" >$dest_dir/$fun_sname-$suffix.cc

    # Include necessary Vaucanson header
    cat >> $dest_dir/$fun_sname-"$suffix".cc<<EOF
#include <cassert>
#include <vaucanson/design_pattern/design_pattern.hh>
#define CREATE_SEMIRING(m)
EOF

    # Include headers inclusion.
    cat $description_file >> $dest_dir/$fun_sname-$suffix.cc;

    # Include "main".
    cat >> $dest_dir/$fun_sname-$suffix.cc<<EOF

#include <check/tester.hh>
#include <$name_test_file>

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

    printf $fun_sname-$suffix' '
  done
  printf '\n'
}

check_programs=$(generate_CCs "$ALL_TEST" test)
failcomp_prog=$(generate_CCs "$ALL_FAILCOMP" failcomp)

# Define the include directories.
for test_dir in $test_dirs
do
# FIXME: Of  course, this  does not work  in general case.
# FIXME: We must find a way to define  the path from dest_dir to test_dir
# FIXME: or to force  people to define an absolute  test_dir.
# FIXME: for the distributed tests suites, it works
    includes="-I\$(srcdir)/../$test_dir $includes"
done

#
# Generates the script to check failed compilations.
#
failcomp_script=$dest_dir/failcomp.sh
cat > $failcomp_script << \EOF
#! /bin/sh
EOF

dump_header "#" >>$failcomp_script
cat >> $failcomp_script << \EOF
fail ()
{
  echo "FAIL: Program $1 succeed to compile."
  exit 1
}

EOF

for prog in $failcomp_prog; do
  cat >> $failcomp_script << EOF
cmd="\$CXX \$CXXFLAGS -c \$srcdir/$prog.cc"
echo "*** THIS COMPILATION IS EXPECTED TO FAIL, THIS IS NOT A BUG ***"
echo \$cmd
\$cmd && fail $prog
echo "*** END OF FAILED COMPILATION, THIS IS NOT A BUG ***"

EOF
done

echo "exit 0" >> $failcomp_script
chmod 755 $failcomp_script

#
# Generate a Makefile.am
#
dump_header '##' >$dest_dir/Makefile.am
cat >> $dest_dir/Makefile.am << EOF
include \$(top_srcdir)/src/tests/check/check.mk
AM_CPPFLAGS += $includes
AM_CPPFLAGS += -DEXCEPTION_TRAPS
AM_CPPFLAGS += -DVCSN_SRC_DIR=\"'\$(top_srcdir)'\"

TESTS_ENVIRONMENT = CXX="\$(CXX)" CXXFLAGS="\$(AM_CPPFLAGS) \$(CPPFLAGS)"
TESTS += failcomp.sh
check_programsRAMS = $check_programs

EXTRA_DIST = failcomp.sh

EOF

for prog in $check_programs
do
  prog_canon=$(echo $prog | sed s/-/_/g)
  echo "${prog_canon}_SOURCES = $prog.cc" >> $dest_dir/Makefile.am
done
