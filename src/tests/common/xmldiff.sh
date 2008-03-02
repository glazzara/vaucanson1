#! /bin/sh

# IMPORTANT NOTES:
# This script recognise two automaton that are basically the same but
# with xml nodes ordered differently.
# This should be removed once the problem related to the xml output
# differences is fixed.

rhs=`cat "$2"`
while read line
do
  line=`echo "$line" | sed -e 's/\[/\\\[/g' | sed -e 's/\]/\\\]/g'`
  rhs=`echo "$rhs" | sed -e "s|$line||g"`
done < "$1"

rhs=`echo "$rhs" | sed -e "s| ||g"`
echo "$rhs"
if [ -z "$rhs" ]; then
  exit 0
fi
exit 1
