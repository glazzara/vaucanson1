# vcsn.m4                                     -*- Autoconf -*-
#
# Vaucanson, a generic library for finite state machines.
# Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 The Vaucanson Group.
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


AC_PREREQ([2.60])
m4_pattern_forbid([^_?VCSN_])


# AC_CHECK_SWIG13
# ---------------
# Check for SWIG
AC_DEFUN([AC_CHECK_SWIG13],
[dnl
  AC_ARG_VAR([SWIG], [the SWIG interface generator])
  AC_CHECK_PROGS([SWIG], [swig], [$am_aux_dir/missing swig])

  AC_CACHE_CHECK([for SWIG >= 1.3],
		 [ac_cv_recent_swig],
		 [ac_cv_recent_swig=no
		  swig_ver=`$SWIG -version 2>&1 | sed -n -e '/SWIG Version/{s/^.*Version \(.*\)/\1/g;p;q;}'`
		  swig_minor=`echo "$swig_ver" | sed -e 's/^@<:@0-9@:>@*\.\(@<:@^.@:>@*\).*/\1/g'`
		  swig_major=`echo "$swig_ver" | sed -e 's/^\(@<:@0-9@:>@*\)\..*/\1/g'`
		  if test `expr $swig_major \* 100 + $swig_minor 2>/dev/null` -ge 103 >/dev/null 2>&1; then
		      ac_cv_recent_swig=yes
		  fi])
])
