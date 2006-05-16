#! /bin/sh

# Don't barf on file not found.
exec 2> /dev/null

use_xml_flags='VCSN_USE_XML\|XML_CHECK'
exit_status=0

for f in $(find . -type f \
    -and \( -name \*.am -or -name \*.cc -or -name \*.hh -or -name \*.hxx \
    -or -name \*.thh -or -name \*.thxx -or -name \*.hcc \) \
    -and -exec grep -q -i xml '{}' \; \
    -and -not -exec grep -q $use_xml_flags '{}' \; \
    -print); do

    # See if the corresponding header check for XML.
    header_check=false
    base=$(expr "$f" : '\(.*h\)\(.\)\2$') && \
	grep -q $use_xml_flags "${base}h" && header_check=true

    # Or if the Makefile.am does.
    makefile_check=false
    grep -q $use_xml_flags "$(dirname "$f")/Makefile.am" && makefile_check=true

    ! $header_check && ! $makefile_check && \
	echo "Warning: $f uses XML I/O but does not test $use_xml_flags." && \
	((exit_status == 127 ? 0 : ++exit_status))
done
exit $exit_status
