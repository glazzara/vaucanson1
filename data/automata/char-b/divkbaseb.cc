// divkbaseb.cc: this file is part of the Vaucanson project.
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
  if (argc != 3 && argc != 4)
  {
    std::cerr << "Usage:" << std::endl
	      << "\t" << argv[0] << " <divisor> <base> [<fmt>]" << std::endl;
    return 1;
  }

  std::string div (argv[1]);
  std::string b (argv[2]);

  int divisor = vcsn::tools::string_to_int (div);
  int base = vcsn::tools::string_to_int (b);

  // Build the alphabet.
  alphabet_t alpha;
  for (int i = 0; i < base; ++i)
    alpha.insert(i < 10 ? '0' + i : 'A' + i);

  // Build the automaton.
  automaton_t a = make_automaton(alpha);

  for (int i = 0; i < divisor; ++i)
    a.add_state();
  a.set_initial(0);
  a.set_final(0);

  int d = 0;
  for (int i = 0; i < divisor; ++i)
    for_all_letters(l, alpha)
    {
      a.add_letter_transition(i, d, *l);
      d = (d + 1) % divisor;
    }

  std::string name = "div" + div + "base" + b;
  vcsn::tools::dumper (argc, argv, 3) (std::cout, a, name);
}
