#!/bin/sh

aclocal -I .
autoconf -f
automake
echo "Reconfiguration done."
