#!/bin/sh

# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# The complete GNU General Public Licence Notice can be found as the
# `COPYING' file in the root directory.
#
# The Vaucanson Group consists of people listed in the `AUTHORS' file.

# generate_bench DIR
generate_bench ()
{
    BENCH_DIR=$1

    # Initialize Makefile.am.
    cat > $BENCH_DIR/Makefile.am <<EOF
#
# DO NOT EDIT BY HAND - Generated by $0
#
include \$(top_srcdir)/src/benchs/common/bench.mk
EXTRA_PROGRAMS =
EOF

    for BENCH in $(ls $BENCH_DIR/*_bench.hh 2> /dev/null); do
	BENCH_HEADER="$(basename $BENCH)"
	BENCH_NAME="$(echo $BENCH_HEADER | sed 's/_bench\.hh$//')"

        # Claim that we are under GPL.
	cat > $BENCH_DIR/$BENCH_NAME-bench.cc <<EOF
//
// DO NOT EDIT BY HAND - Generated by $0
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// \`COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the \`AUTHORS' file.
EOF

        # Include necessary tools
	cat >> $BENCH_DIR/$BENCH_NAME-bench.cc <<EOF

#include <iostream>

#include <vaucanson/tools/bencher.hh>
EOF

        # Precise this-bench related things
	cat >> $BENCH_DIR/$BENCH_NAME-bench.cc <<EOF
#define BENCHNAME		$BENCH_NAME
#include "$BENCH"
EOF

	cat >> $BENCH_DIR/$BENCH_NAME-bench.cc <<EOF
#define BENCHFUN		BENCHFUN_layer1(BENCHNAME)
#define BENCHFUN_layer1(NAME)	BENCHFUN_layer2(NAME)
#define BENCHFUN_layer2(NAME)	NAME ## _bench

#define BENCHTEXT		BENCHTEXT_layer1(BENCHNAME)
#define BENCHTEXT_layer1(NAME)	BENCHTEXT_layer2(NAME)
#define BENCHTEXT_layer2(NAME)  # NAME

int main(int argc, char* argv[])
{
  std::cerr << BENCHTEXT << ":" << std::endl;
  if (argc == 2)
    BENCHFUN(atoi(argv[1]));
}
EOF

	# Add the bench to the Makefile.am.
	cat >> $BENCH_DIR/Makefile.am <<EOF
EXTRA_PROGRAMS += $BENCH_NAME-bench
$(echo "$BENCH_NAME" | sed 's/-/_/g')_bench_SOURCES = $BENCH_NAME-bench.cc \
						      $BENCH_HEADER
EOF
    done
    if [ -r $BENCH_DIR/Makefile.bench ]; then
	cat >> $BENCH_DIR/Makefile.am <<EOF
EXTRA_DIST = Makefile.bench
include \$(top_srcdir)/src/benchs/$BENCH_DIR/Makefile.bench
EOF
    fi
}

case $1:$# in
    --all:1)
	BENCH_DIRS="determinization 				\
	 minimization_debruijn derived_terms minimization_2n	\
         quotient composition"
	;;
    --all:* | *:0)
	echo >&2 "invalid arguments: $@"
	exit 1
	;;
    *)
	BENCH_DIRS=$@
	;;
esac

# Go through all benchs
for BENCH_DIR in $BENCH_DIRS; do
    generate_bench $BENCH_DIR
done
