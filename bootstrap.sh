#!/bin/sh

autoreconf -v -f -i
cd vauc
./boostrap.sh
echo "Reconfiguration done."
