#!/bin/sh

out=0
for i in b z r z_min_plus z_max_plus fmp trans session geometry label_node; do

    prog="./${i}_tester"
    $prog output > ${i}_result.tmp
    ## Testing XML dump.
    echo "XML: Testing saver for type $i"
    diff_result=`diff ${i}_result.tmp ${i}_ref.xml`
    if ! [ -z "$diff_result" ]; then
	echo "FAIL: $i output has difference with XML reference"
	echo "$diff_result"
	out=255
    fi
    ## Testing XML parse.
    $prog < ${i}_ref.xml > ${i}_result.dot.tmp
    echo "XML: Testing loader for type $i"
    diff_result=`diff ${i}_result.dot.tmp ${i}_ref.dot`
    if ! [ -z "$diff_result" ]; then
	echo "FAIL: $i output has difference with DOT reference"
	echo "$diff_result"
	out=255
    fi
done
exit $out
