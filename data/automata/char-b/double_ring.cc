// double_ring.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006, 2007 The Vaucanson Group.
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
#include <sstream>

#include <vaucanson/boolean_automaton.hh>

using namespace vcsn::boolean_automaton;

#include <vaucanson/tools/dumper.hh>

int
main(int argc, char** argv)
{
  if (argc  < 3)
  {
    const char* program = strrchr(argv[0], '/');
    program = program? program+1 : argv[0];
    std::cerr << "Usage:" << std::endl
        << "\t" << program << " <number of states>"
        << " [list of final states...] [<fmt>]" << std::endl;
    return 1;
  }

  std::string nstates (argv[1]);
  int n = vcsn::tools::string_to_int (nstates);

  // Alphabet.
  alphabet_t alpha;
  alpha.insert('a');
  alpha.insert('b');

  // Automaton.
  automaton_t a = make_automaton (alpha);
  a.add_state ();
  a.set_initial (0);

  for (int i = 1; i < n; ++i)
  {
    a.add_state ();
    a.add_letter_transition (i - 1, i, 'a');
    a.add_letter_transition (i, i - 1, 'b');
  }
  a.add_letter_transition (n - 1, 0, 'a');
  a.add_letter_transition (0, n - 1, 'b');

  int i;
  for (i = 2; argv[i] && std::isdigit(argv[i][0]); ++i)
  {
    int s = vcsn::tools::string_to_int (argv[i]);
    if (s >= n)
    {
      std::cerr << argv[0] << ": too big a state number: " << s << std::endl;
      exit (2);
    }
    a.set_final (s);
  }

  std::string name = "double_ring " + nstates;
  vcsn::tools::dumper (argc, argv, i)(std::cout, a, name);
}
