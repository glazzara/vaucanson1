#!/bin/sh
#
# Do not be afraid ! Sed is pretty more developer-friendly than Perl.
#

sed -f - *.hxx loadgeometry.inc <<EOF | sort -u >xmlstrings.inc
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
