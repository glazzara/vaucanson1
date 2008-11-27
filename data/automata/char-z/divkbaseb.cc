// divkbaseb.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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

#include <vaucanson/z_automaton.hh>
using namespace vcsn::z_automaton;
#include <vaucanson/tools/dumper.hh>

// See divkbaseb in char-b. This file is basically the same, but using a
// Z-automaton to get the remainder.
int
main(int argc, char** argv)
{
  if (argc != 3 && argc != 4)
  {
    std::cerr << "Usage:" << std::endl
	      << "\t" << argv[0] << " <divisor> <base> [<fmt>]" << std::endl;
    return 1;
  }

  int divisor = vcsn::tools::string_to_int(std::string(argv[1]));
  int base = vcsn::tools::string_to_int(std::string(argv[2]));

  alphabet_t alpha;
  std::vector<letter_t> int_to_letter;

  for (int i = 0; i < base; ++i)
  {
    int_to_letter.push_back(i < 10 ? '0' + i : 'A' + i);
    alpha.insert(int_to_letter.back());
  }

  automaton_t a = make_automaton(alpha);

  // Each state is given a unique weight, so that if the word evaluates to u,
  // the remainder in the division of n by k is u.
  for (int i = 0; i < divisor; ++i)
  {
    semiring_elt_value_t v = i;
    series_set_elt_t weight(a.structure().series());
    weight.assoc(identity_value(SELECT(monoid_t),
				SELECT(monoid_elt_value_t)), v);
    a.set_final(a.add_state(), weight);
  }

  a.set_initial(0);

  for (int i = 0; i < divisor; ++i)
  {
    int e = i * base;
    for (int l = 0; l < base; ++l)
    {
      int d = (e + l) % divisor;
      a.add_letter_transition(i, d, int_to_letter[l]);
    }
  }

  std::stringstream name;
  name << "div" << divisor << "base" << base;
  vcsn::tools::dumper(argc, argv, 3)(std::cout, a, name.str());
}
