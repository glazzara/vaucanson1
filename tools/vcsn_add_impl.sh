#!/bin/sh
# vcsn_add_impl.sh: this file is part of the Vaucanson project.
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

OUTPUT_DIR="."
INCLUDE_DIR="/usr/local/include"

usage()
{
  cat << EOF
    Usage: vcsn_add_impl.sh --vcsn-include-dir=<path> [--output-dir=<path>] [path/*_graph_impl.hh]
EOF
}

write_context()
{
    UpperName=`echo "$1/$2/$3" | sed -e 's/[\.\/]/\_/g' | tr "[:lower:]" "[:upper:]"`
    cat > "$1/$2/$3" <<-EOF 
#ifndef $UpperName
# define $UpperName
# ifndef VCSN_GRAPH_IMPL
#  define VCSN_GRAPH_IMPL $2
#  define VCSN_GRAPH_IMPL_INCLUDE_PATH $4
#  define VCSN_CONTEXT_INCLUDE_PATH $1
# else
#  define DONT_UNDEF
# endif

# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/automata/generic_contexts/$3>

# ifndef DONT_UNDEF
#  undef VCSN_GRAPH_IMPL
#  undef VCSN_GRAPH_IMPL_INCLUDE_PATH
#  undef VCSN_CONTEXT_INCLUDE_PATH
# else
#  undef DONT_UNDEF
# endif
#endif // !$UpperName
EOF
}

parse_option()
{
  if ! [ -z "`echo $1 | sed -ne '/--vcsn-include-path='/p`" ]; then
    INCLUDE_DIR="`echo $1 | sed -ne s/--vcsn-include-path=//p`"
  elif ! [ -z "`echo $1 | sed -ne '/--output-dir='/p`" ]; then
    OUTPUT_DIR="`echo $1 | sed -ne s/--output-dir=//p`"
  else
    return 1
  fi
  return 0
}

files=()

main()
{
  for arg in $@; do
    if ! parse_option $arg; then
      impl=`echo "$arg" | sed -ne "/.*_graph_impl\.hh/p" | cut -d '_' -f 1`
      if [ -z "$impl" ]; then
	echo "Error : invalid header name (a *_graph_impl.hh form is expected) or invalid option."
	echo "Use the --help option to get more information."
	exit 1
      fi
      files=( "${files[@]}" "$arg" )
    fi
  done

  for file in ${files[@]}; do
      impl=`basename $file`
      impl=`echo "$impl" | sed -ne "/.*_graph_impl\.hh/p" | cut -d '_' -f 1`
      mkdir -p "$OUTPUT_DIR/$impl"
      for header in `find $INCLUDE_DIR/vaucanson/automata/generic_contexts/ -name '*.hh'`; do
	write_context "$OUTPUT_DIR" $impl `basename $header` `dirname $file` 
      done
  done

}

main $@

