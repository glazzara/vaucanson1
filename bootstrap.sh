#!/bin/sh

if [ "$#" -eq "1" ]; then
  AUTORECONF=$1
  echo "Using \`$1' instead of \`autoreconf' command"
else
  AUTORECONF=autoreconf
fi

(cd src/tests/test-suites && /bin/sh ./generate-all.sh)
(cd src/tests/sanity && /bin/sh ./generate_files.sh .)
(cd src/vaucanswig && /bin/sh ./expand.sh .)
(cd src/benchs && /bin/sh ./generate_all_benchs.sh)
sh ./find_tests.sh
sh ./check_xml.sh

$AUTORECONF -v -f -i

echo "Reconfiguration done."
