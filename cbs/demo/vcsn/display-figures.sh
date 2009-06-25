#!/bin/sh

for file in `find . -name "*.eps"`
do
    echo "Displaying figure $file"
    okular $file &
done
echo "Done"
