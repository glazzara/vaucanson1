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
	stderr "$@"
	cd "$1"
	shift
	if ! "$@"; then
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

# On some environments (Darwin Ports), libtoolize is glibtoolize.
# I suppose their autoreconf is adjusted accordingly, but I use
# my custom Autoconf...
for lt in "$LIBTOOLIZE" libtoolize glibtoolize
do
  if ($lt --version) >/dev/null 2>&1; then
    export LIBTOOLIZE="$lt"
    break
  fi
done

run src/tests/test-suites ./generate-all.sh
run src/tests/sanity      ./generate_files.sh .
run vaucanswig            ./expand.sh .
run src/benchs            ./generate_benchs.sh --all
run .                     build-aux/find_tests.sh

# Will also boostrap argp/.
run .                     $AUTORECONF -v -f -i

echo "Reconfiguration done."
