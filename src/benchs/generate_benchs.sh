#!/bin/sh

if [ $# -eq 0 ]; then
    echo 'usage:'
    echo 'create_benchs.sh bench_dirs'
    exit 1
fi

BENCH_DIRS=$@

ALL_BENCH=''

# Go through all benchs
for BENCH_DIR in $BENCH_DIRS; do

    # Initialize Makefile.am.
    cat > $BENCH_DIR/Makefile.am <<EOF
include \$(top_srcdir)/src/benchs/common/Makefile.flags
noinst_PROGRAMS =
EOF

    for BENCH in $(ls $BENCH_DIR/*_bench.hh 2> /dev/null); do
	BENCH_HEADER="$(basename $BENCH)"
	BENCH_NAME="$(echo $BENCH_HEADER | sed 's/_bench\.hh$//')"

        # Claim that we are under LGPL.
	cat > $BENCH_DIR/$BENCH_NAME-bench.cc <<EOF
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
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
noinst_PROGRAMS += $BENCH_NAME-bench
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
done