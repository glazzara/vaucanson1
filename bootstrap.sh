#!/bin/sh

if [ "$#" -eq "1" ]; then
  AUTORECONF=$1
  echo "Using \`$1' instead of \`autoreconf' command"
else
  AUTORECONF=autoreconf
fi

(cd src/tests/tests-suites && /bin/sh ./generate-all.sh)
(cd src/tests/sanity && /bin/sh ./generate_files.sh .)
(cd src/demos/vaucanswig && /bin/sh ./expand.sh .)
./update_config_ac.sh
$AUTORECONF -v -f -i

# disabled temporarily
# cd vauc
# ./bootstrap.sh
echo "Reconfiguration done."
