## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2005, 2006 The Vaucanson Group.
##
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License
## as published by the Free Software Foundation; either version 2
## of the License, or (at your option) any later version.
##
## The complete GNU General Public Licence Notice can be found as the
## `COPYING' file in the root directory.
##
## The Vaucanson Group consists of people listed in the `AUTHORS' file.

# Catch unexpected failures.
set -ex

me=$(basename "$0" _tester.test)
prog="./${me}_tester"

# Run the program, compare the result with the expected output.
$prog output > ${me}_result.tmp
## Testing XML dump.
echo "XML: Testing saver for type $me"
diff_result=$(diff ${me}_result.tmp ${srcdir}/${me}_ref.xml)
if ! test -z "$diff_result"; then
    echo >&2 "FAIL: ${me} output has difference with XML reference"
    echo >&2 "$diff_result"
    out=1
fi

## Testing XML parse.
$prog < ${srcdir}/${me}_ref.xml > ${me}_result.dot.tmp
echo "XML: Testing loader for type ${me}"
diff_result=$(diff ${me}_result.dot.tmp ${srcdir}/${me}_ref.dot)
if ! test -z "$diff_result"; then
    echo >&2 "FAIL: ${me} output has difference with DOT reference"
    echo >&2 "$diff_result"
    out=1
fi

exit $out
