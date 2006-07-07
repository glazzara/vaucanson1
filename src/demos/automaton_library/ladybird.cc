// ladybird.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
#include <vaucanson/boolean_automaton.hh>
#include <ostream>
#include <sstream>

using namespace vcsn::boolean_automaton;
#include "dumper.hcc"

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cerr << "Usage: " << argv[0] << " <n> [<fmt>]" << std::endl;
    return 1;
  }

  std::string nstates (argv[1]);
  unsigned n = string_to_int (nstates);

  // Alphabet.
  alphabet_t alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  // Automaton.
  automaton_t an = make_automaton (alpha);

  vcsn::hstate_t p = an.add_state ();
  vcsn::hstate_t x = p;
  for(unsigned i = 1; i < n; ++i)
  {
    vcsn::hstate_t y = an.add_state();
    an.add_letter_transition(x, y, 'a');an.add_letter_transition(y, y, 'b');
    an.add_letter_transition(y, y, 'c');an.add_letter_transition(y, p, 'c');
    x = y;
  }
  an.add_letter_transition(x, p, 'a');
  an.set_initial(p); an.set_final(p);

  // Dump.
  std::string name = "ladybird " + nstates;
  dumper (argc, argv, 2)(std::cout, an, name);
}
