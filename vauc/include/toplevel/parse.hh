/***********************
 * <toplevel/parse.hh> *
 ***********************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef TOPLEVEL_PARSE_HH
#define TOPLEVEL_PARSE_HH

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

#endif
