#!/bin/sh

# This file is run by the LRDE autobuilder after a successful compilation.
# It is not meant to be distributed with Vaucanson.

set -e
set -x

# Buildbot will tell us the name of the branch being compiled using $1.
rev=$1

case $rev in
  next|hive) rev=snapshot-$rev;;
  master) rev=snapshot;;
  # Don't upload any other branch.
  *) exit;;
esac

case `hostname` in
  vcsn*) DEST=/var/lib/buildbot/tar/$rev;;
  *)     DEST=/lrde/dload/vaucanson/$rev;;
esac

# Retrieve the package version
VERSION=`autoconf --trace='AC_INIT:$2'`

# Always do "cp then mv" when uploading the file, so that someone
# cannot start a download while the destination file is incomplete.

# Upload the tarball
mkdir -p $DEST
cp -f vaucanson-$VERSION.tar.gz $DEST/vaucanson-$rev.tar.gz.tmp
mv -f $DEST/vaucanson-$rev.tar.gz.tmp $DEST/vaucanson-$rev.tar.gz
chmod -R a+r $DEST/vaucanson-$rev.tar.gz

# Upload a copy of the reference manual
rm -rf $DEST/ref.tmp
cp -pR doc/ref $DEST/ref.tmp
cp doc/manual/taf-kit-manual.pdf $DEST/
chmod -R a+rX $DEST/
mv -f $DEST/ref $DEST/ref.old || true
mv -f $DEST/ref.tmp $DEST/ref
rm -rf $DEST/ref.old

# Upload index description
echo "AddDescription \"`git describe`\" ???*" > $DEST/.htaccess
