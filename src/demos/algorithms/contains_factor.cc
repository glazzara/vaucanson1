// contains_factor.cc: this file is part of the Vaucanson project.
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
#include "equivalent_functions.hh"

int
main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cerr << "Usage: " << argv[0] << " <automaton> <factor>" << std::endl;
    return 1;
  }


  rat_exp_t exp = get_exp(argv[2]);
  automaton_t a = standard_of(exp);
  alphabet_t alpha = a.structure().series().monoid().alphabet();

  for_all_initial_states(s, a)
    for_all_letters(l, alpha)
  {
    a.add_letter_transition(*s, *s, *l);
  }

  for_all_final_states(s, a)
    for_all_letters(l, alpha)
  {
    a.add_letter_transition(*s, *s, *l);
  }

  automaton_t b = get_aut(argv[1]);

  a = trim(product(a, b));

  if (a.states().size() != 0)
  {
    std::cout << "The factor \"" << argv[2]
	      << "\" is recognized by the automaton " << argv[1]
	      << "." << std::endl;
    return 0;
  }
  std::cout << "The factor \"" << argv[2]
	    << "\" is NOT recognized by the automaton " << argv[1]
	    << "." << std::endl;
  return 1;
}

