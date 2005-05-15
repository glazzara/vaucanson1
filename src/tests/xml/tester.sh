#!/bin/sh

out=0
for i in b z r z_min_plus z_max_plus fmp trans; do

    prog="./${i}_tester"
    $prog output > ${i}_result.tmp
    ## Testing XML dump.
    echo "XML: Testing saver for type $i"
    diff_result=`diff ${i}_result.tmp ${i}_ref.xml`
    if [ -s "$diff_result" ]; then
	echo "FAIL: $i output has difference with reference"
	out=255
    fi
    ## Testing XML parse.
    parse=`$prog < ${i}_ref.xml`
    echo "XML: Testing loader for type $i"
    echo "$parse" > ${i}_ref.dot
    if [ -s "$parse" ]; then
	echo "FAIL: $i output has difference with reference"
	out=255
    fi
done
exit $out
