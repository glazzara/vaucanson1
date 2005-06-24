// class_spec.h: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.

// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_VAUC_MPP___SRC_PARSE_CLASS_SPEC_H
# define VCSN_VAUC_MPP___SRC_PARSE_CLASS_SPEC_H

typedef union yystype
{
  int				ival;
  std::string			*str;
  ClassSpec::param_set_t	*param;
  ClassSpec::cpp_param_t	*cpp_param;
  ClassSpec			*class_spec;
} YYSTYPE;
# define	NAME	257
# define	DESCRIPTION	258
# define	PARAMETERS	259
# define	TYPE	260
# define	ID	261
# define	DESC	262
# define	COMMA	263


#endif // ! VCSN_VAUC_MPP___SRC_PARSE_CLASS_SPEC_H
