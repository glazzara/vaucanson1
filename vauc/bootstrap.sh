#!/bin/sh

echo "Cleaning up..."
sh ./cleanup.sh

echo "Running aclocal..."
aclocal --verbose >aclocal.log 2>&1
echo "Running libtoolize..."
libtoolize -f -c --ltdl
(
   cd libltdl
   echo "Running aclocal in libltdl/..."
   aclocal --verbose &>aclocal.log
   echo "Running libtoolize in libltdl/..."
   libtoolize -f -c
   if [ -f configure.in ]; then
      echo "Fixing libltdl/configure.in..."
      (echo "AC_PREREQ(2.50)"; cat configure.in) > configure.tmp
      mv configure.tmp configure.in
   fi
   echo "Running autoreconf in libltdl/..."
   autoreconf -i -f -v >autoreconf.log 2>&1
)
echo "Running autoreconf..."
autoreconf -i -f -v >autoreconf.log 2>&1

