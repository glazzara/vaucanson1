#!/bin/sh

autoreconf -v -f -i
cd vauc
./bootstrap.sh
echo "Reconfiguration done."
