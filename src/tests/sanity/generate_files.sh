#! /bin/sh

[ "x$1" = "x" ] && exit 1

cd "$1"

# Compute files to test.
(cd ../../../include && find vaucanson -name \*.hh) | \
  grep -v '/old/\|/obsolete/' > files.tmp

# Set check_PROGRAMS.
cat > Makefile.am << EOF
EXTRA_DIST = generate_files.sh
test_base.cc: generate_files.sh \$(topsrc_dir)/include/Makefile.am
	\$(SHELL) "\$(srcdir)"/generate_files.sh "\$(srcdir)"

AM_CPPFLAGS = -DINTERNAL_CHECKS -DSTRICT -I\$(top_srcdir)/include -I\$(top_builddir)/include
AM_CXXFLAGS = \$(CXXFLAGS_STRICT)
check_PROGRAMS = \\
EOF
awk '{ gsub(/[.\/]/, "_"); print "\t"$0" \\" }' files.tmp | \
  sed '$s/\(.*\) \\/\1/' >> Makefile.am

echo >> Makefile.am

# Set test sources and CPPFLAGS.
awk '
  {
    target = $1
    gsub(/[.\/]/, "_", target)
    print target"_SOURCES = test_base.cc"
    print target"_CPPFLAGS = \$(AM_CPPFLAGS) -DINCLUDE="$1"\n"
  }
' files.tmp >> Makefile.am

# Remove temporary file.
rm files.tmp

# Build base test.
cat > test_base.cc << EOF
#define INC_(I) < I >
#define INC(I) INC_(I)
#include INC(INCLUDE)

int main(int, char)
{
}
EOF
