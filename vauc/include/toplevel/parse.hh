// parse.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_VAUC_INCLUDE_TOPLEVEL_PARSE_HH
# define VCSN_VAUC_INCLUDE_TOPLEVEL_PARSE_HH

#include <string>
#include <iostream>

#include <lazy/exp.hh>

struct Token
{
  std::string word;
  int number;
};

void* ToplevelParseAlloc(void *(*)(size_t));
void ToplevelParseFree(void *, void (*)(void *));

#ifndef NDEBUG
void ToplevelParseTrace(std::ostream *, const char *);
#endif

namespace toplevel
{
  class Command;

  struct ToplevelParseArg
  {
    vcsn::vauc::LazyExp comm;
    std::ostream *err;
    unsigned errors;
  };
}

void ToplevelParse(void *, int, Token *, toplevel::ToplevelParseArg *);

#endif // ! VCSN_VAUC_INCLUDE_TOPLEVEL_PARSE_HH
