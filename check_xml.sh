#! /bin/sh

for f in $(find . -type f \
  -and \( -name \*.am -or -name \*.cc -or -name \*.hh -or -name \*.hxx \) \
  -and -exec grep -q -i xml '{}' \; \
  -and -not -exec grep -q VCSN_USE_XML '{}' \; \
  -and -not -path \*include/vaucanson/xml\* \
  -print); do
  echo "Booh! $f uses XML I/O but does not test VCSN_USE_XML."
done
