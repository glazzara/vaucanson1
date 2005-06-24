// module_spec.h: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_MPP___SRC_PARSE_MODULE_SPEC_H
# define VCSN_VAUC_MPP___SRC_PARSE_MODULE_SPEC_H

typedef union yystype
{
  int					ival;
  std::string				*str;
  spec::ModuleSpec			*module_spec;
  spec::ModuleSpec::param_set_t		*param_set;
  spec::Version				*version;
  std::list<spec::Version*>		*list_version;
  spec::FunVersion::sigs_t		*signatures;
  std::list<std::string>		*signature;
  spec::ModuleSpec::param_value_t	*args;

} YYSTYPE;
# define	ALIAS	257
# define	NAME	258
# define	TYPE	259
# define	FUN	260
# define	IS	261
# define	LPAREN	262
# define	RPAREN	263
# define	ARROW	264
# define	COMMA	265
# define	DESCRIPTION	266
# define	COLON	267
# define	EQ	268
# define	WITH	269
# define	ID	270
# define	DESC	271
# define	OBJECT	272


#endif // ! VCSN_VAUC_MPP___SRC_PARSE_MODULE_SPEC_H
