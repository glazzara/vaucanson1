#!/bin/sh

$SHELL src/tests/sanity/generate_files.sh src/tests/sanity
(cd src/demos/vaucanswig && /bin/sh ./expand.sh .)
autoreconf -v -f -i

# disabled temporarily
# cd vauc
# ./bootstrap.sh
echo "Reconfiguration done."
