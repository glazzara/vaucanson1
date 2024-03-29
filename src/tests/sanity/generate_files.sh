#! /bin/sh

set -e

if test "x$1" = "x"; then
  echo >&2 "usage: $0 SRCDIR"
  exit 1
fi
cd "$1"

top_srcdir=../../..
build_aux_dir=$top_srcdir/build-aux
move_if_change=$build_aux_dir/move-if-change

if test ! -f $move_if_change; then
  echo >&2 "$0: no such file: $move_if_change"
  exit 1
fi

# The file to generate.
out=check-programs.mk

# The corresponding tmp file.
tmp=$out.tmp

# Compute files to test.
(cd ../../../include &&
    find vaucanson -type f -name \*.hh) |
grep -vE 'generic_contexts/|old/|obsolete/|\.svn/|contextual_(automaton|transducer)_' > files.tmp

# Set check_PROGRAMS.
cat > $tmp << EOF
#
# DO NOT EDIT BY HAND - Generated by $0.
#

check_PROGRAMS= \\
EOF

sed 's/[.\/]/_/g;
s/.*/	&-test/;
$!s/.*/& \\/'  files.tmp >> $tmp

echo >> $tmp
# Set test sources.
sed 's/[.\/]/_/g;s/.*/&_test_SOURCES = &.cc/' files.tmp >> $tmp

# Update.
$move_if_change $tmp $out

# Build test sources.
while read f
do
    out=$(echo $f | sed 's/[.\/]/_/g').cc
    cat > $out.tmp <<EOF
//
// DO NOT EDIT BY HAND - Generated by $0.
//

// Include the file twice, so we detect missing inclusion guards.
#include <$f>
#include <$f>
int main()
{
}
EOF
    $move_if_change $out.tmp $out
done < files.tmp

# Remove temporary file.
rm files.tmp
