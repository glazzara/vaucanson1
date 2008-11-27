// quotkbaseb.cc: this file is part of the Vaucanson project.
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

#include <vaucanson/fmp_transducer.hh>
#include <vaucanson/xml/contexts/fmp.hh>
#include <vaucanson/tools/xml_dump.hh>

// See divkbaseb in char-b. With a minor addition, this file build the FMP
// transducer whose output is the quotient in the division of n by k.
int
main(int argc, char** argv)
{
  using namespace vcsn::fmp_transducer;

  // Type helpers.
  typedef vcsn::algebra::letter_traits<first_alphabet_t::letter_t> ftraits;
  typedef vcsn::algebra::letter_traits<second_alphabet_t::letter_t> straits;

  if (argc != 3)
  {
    std::cerr << "Usage:" << std::endl
	      << "\t" << argv[0] << " <divisor> <base>" << std::endl;
    return 1;
  }

  std::stringstream k;
  k << argv[1];
  int divisor;
  k >> divisor;

  std::stringstream b;
  b << argv[2];
  int base;
  b >> base;

  first_alphabet_t A;
  second_alphabet_t B;
  std::vector<first_alphabet_t::letter_t> int_to_letter;

  for (int i = 0; i < base; ++i)
  {
    int_to_letter.push_back(i < 10 ? '0' + i : 'A' + i);
    A.insert(int_to_letter.back());
    B.insert(int_to_letter.back());
  }

  automaton_t a = make_automaton(A, B);

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
      int f = (e + l) / divisor;
      a.add_weighted_transition(i, d, true, make_couple(A, B,
	ftraits::letter_to_literal(int_to_letter[l]),
	straits::letter_to_literal(int_to_letter[f])).value());
    }
  }

  std::stringstream name;
  name << "quot" << divisor << "base" << base;
  vcsn::tools::xml_dump(std::cout, a, name.str());
}
