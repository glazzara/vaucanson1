// divkbaseb.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006, 2007, 2008 The Vaucanson Group.
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
#include <vector>

#include <vaucanson/boolean_automaton.hh>
using namespace vcsn::boolean_automaton;
#include <vaucanson/tools/dumper.hh>

// Build the boolean automaton which accepts a word n representing a
// number in base b if and only if k|n.
int
main(int argc, char** argv)
{
  if (argc != 3 && argc != 4)
  {
    const char* program = strrchr(argv[0], '/');
    program = program? program+1 : argv[0];
    std::cerr << "Usage:" << std::endl
        << "\t" << program << " <divisor> <base> <format>" << std::endl;
    return 1;
  }

  // The divisor `k'.
  int divisor = vcsn::tools::string_to_int(std::string(argv[1]));
  // The base `b'.
  int base = vcsn::tools::string_to_int(std::string(argv[2]));

  // Build the alphabet (from letter 0 to base - 1).
  alphabet_t alpha;
  std::vector<letter_t> int_to_letter;

  for (int i = 0; i < base; ++i)
  {
    int_to_letter.push_back(i < 10 ? '0' + i : 'A' + i);
    alpha.insert(int_to_letter.back());
  }

  // Build the automaton.
  automaton_t a = make_automaton(alpha);

  // Add one state for each possible remainder. The last state encountered
  // during the evaluation will be n % k. If the last state is the state 0,
  // it means that the residue is 0, ie the word will be accepted, ie the
  // number is a multiple of k.
  for (int i = 0; i < divisor; ++i)
    a.add_state();

  a.set_initial(0);
  a.set_final(0);

  for (int i = 0; i < divisor; ++i)
  {
    int e = i * base;
    for (int l = 0; l < base; ++l)
    {
      int d = (e + l) % divisor;
      a.add_letter_transition(i, d, int_to_letter[l]);
    }
  }

  // Dump the automaton.
  std::stringstream name;
  name << "div" << divisor << "base" << base;
  vcsn::tools::dumper(argc, argv, 3)(std::cout, a, name.str());
}
