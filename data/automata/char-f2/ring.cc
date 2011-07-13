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

#include <vaucanson/f2_automaton.hh>

using namespace vcsn::f2_automaton;

#include <vaucanson/tools/dumper.hh>

int
main(int argc, char** argv)
{
  if (argc < 3)
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

  // Automaton.
  automaton_t ring = make_automaton (alpha);
  ring.add_state ();
  ring.set_initial (0);

  for (int i = 1; i < n; ++i)
  {
    ring.add_state ();
    ring.add_letter_transition (i - 1, i, 'a');
  }
  ring.add_letter_transition (n - 1, 0, 'a');

  int i;
  for (i = 2; argv[i] && std::isdigit(argv[i][0]); ++i)
  {
    int s = vcsn::tools::string_to_int (argv[i]);
    if (s >= n)
    {
      std::cerr << argv[0] << ": too big a state number: " << s << std::endl;
      exit (2);
    }
    ring.set_final (s);
  }

  std::string name = "ring " + nstates;
  vcsn::tools::dumper (argc, argv, i)(std::cout, ring, name);
}
