#!/bin/sh

# This file is run by the LRDE autobuilder after a successful compilation.
# It is not meant to be distributed with Vaucanson.

set -e
set -x

cd doc/manual
make vaucanson-developer-manual.pdf vaucanson-user-manual.pdf
cd ../..

rm -rf /lrde/dload/vaucanson/snapshot/ref.tmp
cp -pR doc/ref /lrde/dload/vaucanson/snapshot/ref.tmp
chmod -R a+rX /lrde/dload/vaucanson/snapshot/ref.tmp

cp doc/manual/vaucanson-developer-manual.pdf doc/manual/vaucanson-user-manual.pdf /lrde/dload/vaucanson/snapshot/

cp -f vaucanson-*.tar.gz /lrde/dload/vaucanson/snapshot/vaucanson-snapshot.tar.gz
chmod a+rX /lrde/dload/vaucanson/snapshot/vaucanson-snapshot.tar.gz

mv -f /lrde/dload/vaucanson/snapshot/ref \
      /lrde/dload/vaucanson/snapshot/ref.old || true
mv -f /lrde/dload/vaucanson/snapshot/ref.tmp /lrde/dload/vaucanson/snapshot/ref
rm -rf /lrde/dload/vaucanson/snapshot/ref.old
