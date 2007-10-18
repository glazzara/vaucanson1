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
DEFAULT_GRAPH_IMPLEMENTATION="light"

MK_FILE=generic_contexts.mk
FIND="find"
if [ -z "`find -printf '%f' 2>/dev/null`" ]; then
  FIND="gfind"
fi


write_default_context()
{
  fullname="vaucanson/$1"
  UpperName=`echo $fullname| sed -e 's/[\.\/]/\_/g' | tr "[:lower:]" "[:upper:]"`
  context=`echo $1 | cut -d '.' -f 1 | sed -e 's/_structures//g'`

  cat > $fullname <<-EOF 
#ifndef $UpperName
# define $UpperName

# include <vaucanson/misc/usual_macros.hh>
EOF

  for impl in `$FIND vaucanson/automata/implementation -name '*_graph_impl.hh' -printf '%f\n' 2>/dev/null | sed -e 's/_graph_impl.hh//g'`; do 
    echo "# include <vaucanson/contexts/$impl/$1>" >> $fullname
  done

  cat >> $fullname <<-EOF

# include <vaucanson/config/pconf.hh>
namespace vcsn
{
  namespace $context = vcsn::VCSN_DEFAULT_GRAPH_IMPL::$context;
}

#endif // !$UpperName
EOF

  echo "  $fullname	  \\" >> $MK_FILE
}

write_context()
{
    UpperName=`echo $1| sed -e 's/[\.\/]/\_/g' | tr "[:lower:]" "[:upper:]"`
    cat > $1 <<-EOF 
#ifndef $UpperName
# define $UpperName
# ifndef VCSN_GRAPH_IMPL
#  define VCSN_GRAPH_IMPL $2
# else
#  define DONT_UNDEF
# endif

# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/automata/generic_contexts/$3>

# ifndef DONT_UNDEF
#  undef VCSN_GRAPH_IMPL
# else
#  undef DONT_UNDEF
# endif
#endif // !$UpperName
EOF

  echo "  $1	  \\" >> $MK_FILE

}

write_gpl_header()
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

main()
{
  write_gpl_header

  echo 'GENERIC_CONTEXTS =	  \\' >> $MK_FILE

#Creating directories
  for impl in `$FIND vaucanson/automata/implementation -name '*_graph_impl.hh' -printf '%f\n' 2>/dev/null | sed -e 's/_graph_impl.hh//g'`; do 
      mkdir -p vaucanson/contexts/$impl
  done

  for header in `$FIND vaucanson/automata/generic_contexts/ -name '*.hh' -printf '%f\n' 2>/dev/null`; do
     write_default_context $header
    for impl in `$FIND vaucanson/automata/implementation -name '*_graph_impl.hh' -printf '%f\n' 2>/dev/null | sed -e 's/_graph_impl.hh//g'`; do 
	write_context vaucanson/contexts/$impl/$header $impl $header
    done
  done

  echo 'nobase_include_HEADERS += \$(GENERIC_CONTEXTS)' >> $MK_FILE
  echo 'MAINTAINERCLEANFILES = \$(GENERIC_CONTEXTS)' >> $MK_FILE
}

main
