#!/bin/sh
cat *.xml |\
sed -n '
s/    <parameter name="[^"]*" value="\([0-9]*\)" \/>/\1/p
s/    <result name="[^"]*" value="\([0-9]*\)" \/>/\1/p
s/<\/bench>/NL/p
' |\
tr '\012' ' ' |\
sed '
{
s/ NL /\
/g
}' |\
sort -g > plot.plot
