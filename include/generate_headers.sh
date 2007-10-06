#!/bin/sh
# generate_headers.sh: this file is part of the Vaucanson project.
#
# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2007 The Vaucanson Group.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# The complete GNU General Public Licence Notice can be found as the
# `COPYING' file in the root directory.
#
# The Vaucanson Group consists of people listed in the `AUTHORS' file.
#

# Set the default graph implementation here
DEFAULT_GRAPH_IMPLEMENTATION="legacy"

MK_FILE=generic_contexts.mk

function write_context()
{
    UpperName=`echo $1| sed -e 's/\./\_/g' | tr "[:lower:]" "[:upper:]"`
    cat > $1 <<-EOF 
#ifndef $UpperName
# define $UpperName
# define VCSN_GRAPH_IMPL $2

# include <vaucanson/automata/generic_contexts/$3>

# undef VCSN_GRAPH_IMPL
#endif // !$UpperName
EOF

  echo "  $1	  \\" >> $MK_FILE

}

function write_gpl_header()
{
  cat > $MK_FILE <<-EOF
## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2007 The Vaucanson Group.
##
## This program is free software; you can redistribute it and/or
## modify it under the terms of the GNU General Public License
## as published by the Free Software Foundation; either version 2
## of the License, or (at your option) any later version.
##
## The complete GNU General Public Licence Notice can be found as the
## \`COPYING' file in the root directory.
##
## The Vaucanson Group consists of people listed in the \`AUTHORS' file.
##
## NOTE: this file was generated automatically with generate_libvcsn.rb

EOF
}

function main()
{
  write_gpl_header

  echo "GENERIC_CONTEXTS +=	  \\" >> $MK_FILE

#Creating directories
  for impl in `find vaucanson/automata/implementation -name '*_graph_impl.hh' -printf '%f\n' | sed -e 's/_graph_impl.hh//g'`; do 
    mkdir -p vaucanson/contexts/$impl
  done

  for header in `find vaucanson/automata/generic_contexts/ -name '*.hh' -printf '%f\n'`; do
    for impl in `find vaucanson/automata/implementation -name '*_graph_impl.hh' -printf '%f\n' | sed -e 's/_graph_impl.hh//g'`; do 

      if [ "$impl" = "$DEFAULT_GRAPH_IMPLEMENTATION" ]; then
	write_context vaucanson/$header $impl $header
      fi
	write_context vaucanson/contexts/$impl/$header $impl $header

    done
  done

  echo "nobase_include_HEADERS += \$(GENERIC_CONTEXTS)" >> $MK_FILE
  echo "MAINTAINERCLEANFILES += \$(GENERIC_CONTEXTS)" >> $MK_FILE
}

main
