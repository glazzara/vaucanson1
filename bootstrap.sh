#!/bin/sh

(cd src/demos/vaucanswig && /bin/sh ./expand.sh .)
autoreconf -v -f -i

# disabled temporarily
# cd vauc
# ./bootstrap.sh
echo "Reconfiguration done."
