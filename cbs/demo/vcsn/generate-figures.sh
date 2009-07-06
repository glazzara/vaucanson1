#!/bin/sh

for file in `find . -name "*.plot"`
do
    echo "Generating figure for $file"
    gnuplot $file
done
echo "done"
