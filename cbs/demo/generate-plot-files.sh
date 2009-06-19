#!/bin/bash

MACHINE="2.33GHz Intel Core 2 Quad Q8200, 4GB RAM"
MEXT="q8200"

for file in `find . -name "*.plot.in"`
do
    LEN=`expr length $file`
    let LEN="LEN-3"
    out=`expr substr $file 1 $LEN`
    sed "s/@MACHINE@/${MACHINE}/" $file > $out
    sed -i "s/@MEXT@/${MEXT}/" $out
done
