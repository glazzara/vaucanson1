#!/bin/sh

me=$(basename $0)

stderr ()
{
    echo >&2 "$0: $@"
}


# run DIRECTORY COMMAND-LINE
# --------------------------
# "set -e" doesn't work for subshells!
run ()
{
    (
	stderr "bootstrapping: $@"
	cd "$1"
	shift
	if ! /bin/sh "$@"; then
	    stderr "unexpected failure: $@"
	    exit 1
	fi
    )
}

set -e

if [ "$#" -eq "1" ]; then
  AUTORECONF=$1
  echo "Using \`$1' instead of \`autoreconf' command"
else
  AUTORECONF=autoreconf
fi

run src/tests/test-suites ./generate-all.sh
run src/tests/sanity      ./generate_files.sh .
run src/vaucanswig        ./expand.sh .
run src/benchs            ./generate_benchs.sh --all
run .                     build-aux/find_tests.sh
run .                     build-aux/check_xml.sh
run .                     $AUTORECONF -v -f -i

echo "Reconfiguration done."
