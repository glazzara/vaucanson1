#!/bin/sh

(cd src/tests/tests-suite && /bin/sh ./generate-all.sh)
(cd src/tests/sanity && /bin/sh ./generate_files.sh .)
(cd src/demos/vaucanswig && /bin/sh ./expand.sh .)
autoreconf -v -f -i

# disabled temporarily
# cd vauc
# ./bootstrap.sh
echo "Reconfiguration done."
