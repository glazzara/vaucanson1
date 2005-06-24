// fun_spec.h: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_MPP___SRC_PARSE_FUN_SPEC_H
# define VCSN_VAUC_MPP___SRC_PARSE_FUN_SPEC_H

typedef union yystype
{
  int				ival;
  std::string			*str;
  spec::FunSpec			*fun_spec;
  spec::FunSig			*fun_sig;
  std::list<spec::FunSig>	*fun_sigs;
  FunSpec::param_set_t		*param_set;
} YYSTYPE;
# define	NAME	257
# define	PARAMETERS	258
# define	ARROW	259
# define	COMMA	260
# define	DESCRIPTION	261
# define	COLON	262
# define	ID	263
# define	DESC	264


#endif // ! VCSN_VAUC_MPP___SRC_PARSE_FUN_SPEC_H
