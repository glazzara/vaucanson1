#!/bin/sh
# generate_headers.sh: this file is part of the Vaucanson project.
#
# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2007, 2008, 2009 The Vaucanson Group.
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

MK_FILE=generic_contexts.mk
IMPL_SET=`find vaucanson/automata/implementation -name '*_graph_impl.hh' -exec basename {} \; 2>/dev/null | sed -e 's/_graph_impl.hh//g' | sort`

write_namespace_alias()
{
  conditional_alias=""
  if $3; then
    conditional_alias=" && defined(VCSN_ALIAS_NAMESPACE)"
  fi

  cat >> $1 <<-EOF
# if !defined(ALIAS_$2)$conditional_alias
#  define ALIAS_$2
namespace vcsn
{
  namespace $2 = vcsn::VCSN_DEFAULT_GRAPH_IMPL::$2;
}
# endif
EOF
}

write_common_traits()
{
  cat >> $1 <<-EOF
# if !defined(COMMON_TRAITS)
#  define COMMON_TRAITS
namespace vcsn
{
  VCSN_MAKE_STANDARD_OF_TRAITS(vcsn::VCSN_DEFAULT_GRAPH_IMPL::Graph);
}
# endif
EOF
}

insert_specific_alias()
{
  if [ "$2" = "boolean_transducer" ]; then
    write_namespace_alias $1 "boolean_automaton" $3
  elif [ "$2" = "fmp_transducer" ]; then
    write_namespace_alias $1 "boolean_automaton" $3
  elif [ "$2" = "z_fmp_transducer" ]; then
    write_namespace_alias $1 "z_automaton" $3
  elif [ "$2" = "z_transducer" ]; then
    write_namespace_alias $1 "z_automaton" $3
  fi
}

write_default_context()
{
  fullname="vaucanson/$1"
  UpperName=`echo $fullname| sed -e 's/[\.\/]/\_/g' | tr "[:lower:]" "[:upper:]"`
  context=`echo $1 | cut -d '.' -f 1 | sed -e 's/_structures//g'`

  cat > $fullname <<-EOF
#ifndef $UpperName
# define $UpperName

# include <vaucanson/config/pconf.hh>
# include <vaucanson/misc/usual_macros.hh>
EOF

  for impl in $IMPL_SET; do
    printf "# include <vaucanson/contexts/$impl/$1>\n" >> $fullname
  done

  write_namespace_alias $fullname $context false
  insert_specific_alias $fullname $context false
  write_common_traits $fullname

  cat >> $fullname <<-EOF
#endif // !$UpperName
EOF

  printf "  $fullname" >> $MK_FILE
}

write_context()
{
    UpperName=`echo $1| sed -e 's/[\.\/]/\_/g' | tr "[:lower:]" "[:upper:]"`
    cat > $1 <<-EOF
#ifndef $UpperName
# define $UpperName
# ifndef VCSN_GRAPH_IMPL
#  define VCSN_GRAPH_IMPL $2
#  define VCSN_GRAPH_IMPL_INCLUDE_PATH vaucanson/automata/implementation
#  define VCSN_CONTEXT_INCLUDE_PATH vaucanson/contexts
# else
#  define DONT_UNDEF
# endif

# ifndef VCSN_DEFAULT_GRAPH_IMPL
#  define VCSN_DEFAULT_GRAPH_IMPL $2
#  define VCSN_ALIAS_NAMESPACE
# endif

# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/automata/generic_contexts/$3>
EOF

write_namespace_alias $1 $context true
insert_specific_alias $1 $context true

cat >> $1 <<-EOF

# ifndef DONT_UNDEF
#  undef VCSN_GRAPH_IMPL
#  undef VCSN_GRAPH_IMPL_INCLUDE_PATH
#  undef VCSN_CONTEXT_INCLUDE_PATH
# else
#  undef DONT_UNDEF
# endif
#endif // !$UpperName
EOF

  printf "  $1" >> $MK_FILE

}

write_gpl_header()
{
  cat > $MK_FILE <<-EOF
## Vaucanson, a generic library for finite state machines.
## Copyright (C) 2007, 2008 The Vaucanson Group.
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
## NOTE: this file was generated automatically with generate_headers.sh

EOF
}

main()
{
  write_gpl_header

  printf 'GENERIC_CONTEXTS = ' >> $MK_FILE

#Creating directories
  for impl in $IMPL_SET; do
      mkdir -p vaucanson/contexts/$impl
  done

  for header in `find vaucanson/automata/generic_contexts/ -name '*.hh' -exec basename {} \; 2>/dev/null | sort`; do
    printf "\\\\\n" >> $MK_FILE
    write_default_context $header
    for impl in $IMPL_SET; do
	printf "\\\\\n" >> $MK_FILE
	write_context vaucanson/contexts/$impl/$header $impl $header
    done
  done
  printf "\\n" >> $MK_FILE
  printf "nobase_include_HEADERS += \$(GENERIC_CONTEXTS)\n" >> $MK_FILE
  printf "MAINTAINERCLEANFILES = \$(GENERIC_CONTEXTS)\n" >> $MK_FILE

  # Sometimes we creates some context on a Git branch, and when
  # switching to another branch without this context we are left with
  # some generated files that should not be there.  These cause some
  # problems because other parts of Vaucanson
  # (e.g. src/tests/sanity/generate_files.sh) will glob for files to
  # generate code.  Let's remove these files.  (This fix is only a
  # hack; the real fix is to stop globbing.  Globbing is evil.)
  for header in `find vaucanson/contexts -type f -name '*.hh'` vaucanson/*.hh; do
    if grep -F -q "$header" Makefile.am generic_contexts.mk; then :; else
	echo deleting $header
	rm -f $header
    fi
  done
}

main
