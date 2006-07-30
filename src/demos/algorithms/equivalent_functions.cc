// equivalent_functions.cc: this file is part of the Vaucanson project.
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
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#include <vaucanson/tools/io.hh>
#include <vaucanson/xml/XML.hh>
#include <ostream>
#include <sstream>

#include "equivalent_functions.hh"

rat_exp_t
get_exp(std::string s)
{
  alphabet_t	a;
  a.insert('a');
  a.insert('b');

  return make_rat_exp(a, s);
}

automaton_t
get_aut(std::string s)
{
  std::istream* is (new std::ifstream (s.c_str()));
  if (not is->fail())
  {
    using namespace vcsn::io;
    using namespace vcsn::xml;

    automaton_t a = make_automaton(alphabet_t ());
    *is >> automaton_loader(a, string_out (), XML ());

    if (s != "-")
      delete is;
    return a;
  }
  else
  {
    std::cerr << "FATAL: Could not load automaton." << std::endl;
    exit(1);
  }
}


bool
are_equivalent(const automaton_t &a, const automaton_t &b)
{
  automaton_t c (a);
  automaton_t d (b);

  if (not is_deterministic(c))
    c = determinize(a);
  else if (not is_complete(c))
    complete_here(c);

  if(not is_deterministic(d))
    d = determinize(b);
  else if(not is_complete(d))
    complete_here(d);

  complement_here(c);
  complement_here(d);
  c = trim(product(c, b));
  d = trim(product(a, d));
  return c.states().size() == 0 and d.states().size() == 0;
}

