#! /bin/sh

[ "x$1" = "x" ] && exit 1

cd "$1"

# Compute files to test.
(cd ../../../include && find vaucanson -type f -name \*.hh) | \
  grep -vE 'old/|obsolete/|\.svn/|contextual_(automaton|transducer)_' > files.tmp

# Set check_PROGRAMS.
cat > Makefile.am << EOF
EXTRA_DIST = generate_files.sh
test_base.cc: generate_files.sh \$(top_srcdir)/include/Makefile.am
	\$(SHELL) "\$(srcdir)"/generate_files.sh "\$(srcdir)"

if XML_CHECK
  AM_CPPFLAGS = -DINTERNAL_CHECKS -DSTRICT -I\$(top_srcdir)/include -I\$(top_builddir)/include -I\$(XERCESC)/include
else
AM_CPPFLAGS = -DINTERNAL_CHECKS -DSTRICT -I\$(top_srcdir)/include -I\$(top_builddir)/include
endif
AM_CXXFLAGS = \$(CXXFLAGS_STRICT)

if XML_CHECK
  AM_LDFLAGS = -L\$(XERCESC)/lib -lxerces-c
endif
check_PROGRAMS= \\
EOF
awk '/xml/ { next }; { gsub(/[.\/]/, "_"); print "\t"$0"-test \\" }' \
  files.tmp | sed '$s/\(.*\) \\/\1/' >> Makefile.am

cat >> Makefile.am <<EOF
if XML_CHECK
check_PROGRAMS+= \\
EOF

awk '/xml/ { gsub(/[.\/]/, "_"); print "\t"$0"-test \\" }' files.tmp | \
  sed '$s/\(.*\) \\/\1/' >> Makefile.am

echo "endif" >> Makefile.am

echo >> Makefile.am
echo "TESTS= \\" >> Makefile.am

awk '/xml/ { next }; { gsub(/[.\/]/, "_"); print "\t"$0"-test \\" }' \
  files.tmp | sed '$s/\(.*\) \\/\1/' >> Makefile.am

cat >> Makefile.am <<EOF
if XML_CHECK
TESTS+= \\
EOF

awk '/xml/ { gsub(/[.\/]/, "_"); print "\t"$0"-test \\" }' files.tmp | \
  sed '$s/\(.*\) \\/\1/' >> Makefile.am

echo "endif" >> Makefile.am

# Set test sources and CPPFLAGS.
awk '
  {
    target = $1
    gsub(/[.\/]/, "_", target)
    print target"_test_SOURCES = test_base.cc"
    print target"_test_CPPFLAGS = $(AM_CPPFLAGS) -DINCLUDE="$1"\n"
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
