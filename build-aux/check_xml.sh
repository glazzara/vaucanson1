#! /bin/sh

set -e

use_xml_flags='VCSN_USE_XML\|XML_CHECK\|VCSN_INCLUDE_XML\|demo.mk'
exit_status=0

find . \
    -type f \
    -and \( -name \*.am -or -name \*.cc -or -name \*.hh -or -name \*.hxx \
            -or -name \*.thh -or -name \*.thxx -or -name \*.hcc \
         \) \
    -and -exec grep -q -i xml '{}' \; \
    -and -not -exec grep -q $use_xml_flags '{}' \; \
    -print |
while read f;
do

    # See if the corresponding header checks for XML.
    header_check=false
    if base=$(expr "$f" : '\(.*h\)\(.\)\2$') &&
	grep -q $use_xml_flags "${base}h"; then
	header_check=true
    fi

    # Or if the Makefile.am does.
    makefile_check=false
    makefile=$(dirname "$f")/Makefile.am
    if test -f $makefile &&
	grep -q $use_xml_flags "$makefile"; then
	makefile_check=true
    fi

    if ! $header_check && ! $makefile_check; then
	echo "Warning: $f uses XML I/O but does not test $use_xml_flags."
	exit_status=1
    fi
done
exit $exit_status
