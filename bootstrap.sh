#!/bin/sh

aclocal -I .
autoconf -f
automake -a
echo "Reconfiguration done."
