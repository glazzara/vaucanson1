#! /bin/sh

# IMPORTANT NOTES:
# This script recognise two automata that are basically the same but
# with xml nodes ordered differently.
# This should be removed once the problem related to the xml output
# differences is fixed.

test -f "$1" || exit 2
test -f "$2" || exit 2

# <foo bar=x baz=y> should be the same as <foo baz=y baz=x>
# So we simply sort the words on each line, in both files.
while read line
do
  # Ignore writingData, because the reference Automata in src/tests/xml
  # do not have any.
  case $line in *writingData*) continue;; esac
  x=`echo $line | tr -d '"[;]/>' | tr " " "\n" | sort | tr '\n' ' ' | tr -d ' '`
  test -n "$x" && echo "$x"
done < "$1" | sort > "$$.t1"

while read line
do
  case $line in *writingData*) continue;; esac
  x=`echo $line | tr -d '"[;]/>' | tr " " "\n" | sort | tr '\n' ' ' | tr -d ' '`
  test -n "$x" && echo "$x"
done < "$2" | sort > "$$.t2"

cmp $$.t1 $$.t2
exitcode=$?

rm -f $$.t1 $$.t2

exit $exitcode
