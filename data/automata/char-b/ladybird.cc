// ladybird.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2007 The Vaucanson Group.
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
#include <vaucanson/tools/dumper.hh>

int main(int argc, char** argv)
{
  if ((argc != 2 && argc != 3))
  {
    const char* program = strrchr(argv[0], '/');
    program = program? program+1 : argv[0];
    std::cerr << "Usage: " << std::endl
              << '\t' << program << " <n> [<fmt>]" << std::endl;
    return 1;
  }

  std::string nstates (argv[1]);
  unsigned n = vcsn::tools::string_to_int (nstates);

  // Alphabet.
  alphabet_t alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  // Automaton.
  automaton_t an = make_automaton (alpha);

  hstate_t p = an.add_state ();
  hstate_t x = p;
  for(unsigned i = 1; i < n; ++i)
  {
    hstate_t y = an.add_state();
    an.add_letter_transition(x, y, 'a');an.add_letter_transition(y, y, 'b');
    an.add_letter_transition(y, y, 'c');an.add_letter_transition(y, p, 'c');
    x = y;
  }
  an.add_letter_transition(x, p, 'a');
  an.set_initial(p); an.set_final(p);

  // Dump.
  std::string name = "ladybird " + nstates;
  vcsn::tools::dumper (argc, argv, 2)(std::cout, an, name);
}
