#!/bin/sh
#
# Do not be afraid ! Sed is pretty more developer-friendly than Perl.
#

if test $# -ne 2; then
  cat 1>&2 <<EOF
Invocation is not valid!

Usage:
	$0 <srcdir> <builddir>
EOF
  exit 1
fi

CMD=/tmp/vaucanson-gentufstrings-"$USER"-"$$"

cat > $CMD <<EOF
/str_/ {
s/^.*str_\([a-zA-Z0-9_]*\)[^a-zA-Z0-9_].*$/\1/
s/\(.*\)/const XMLCh str_\1[] = { |\1/
:begin
/|$/b end
s/|_d/chDash, |/
s/|_p/chPeriod, |/
s/|_s/chForwardSlash, |/
s/|_c/chColon, |/
s/|\([0-9]\)/chDigit_\1, |/
s/|\([a-zA-Z]\)/chLatin_\1, |/
/|[a-zA-Z0-9]/b begin
/|$/b end
/|_[dpsc]/b begin
s/^.*\(str_[a-zA-Z0-9_]*\)[^a-zA-Z0-9_].*$/#error "cannot translate \1"/
p
d
b
:end
s/|$/chNull };/
p
}
d
EOF

sed -f $CMD "$1"/*.hxx "$2"/loadgeometry.inc | sort -u > "$2"/xmlstrings.inc
rm $CMD

