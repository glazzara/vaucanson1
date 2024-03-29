// fibonacci_rt_gen.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2008 The Vaucanson Group.
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
#include "one_rule_rewriting.hh"

#include <vaucanson/boolean_transducer.hh>
#include <vaucanson/algorithms/rw_composition.hh>

#include <vaucanson/xml/contexts/rw.hh>
#include <vaucanson/tools/xml_dump.hh>

#define FIBONACCI_FROM "abb"
#define FIBONACCI_TO "baa"

int main()
{
  using namespace ORR;
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::boolean_transducer;

  /*-------------------------------.
  | Instanciation of the objects.  |
  `-------------------------------*/

  alphabet_t	A;

  A.insert('a');
  A.insert('b');

  /*----------------------.
  | Creation of fibleft.  |
  `----------------------*/

  automaton_t		fibleft = make_automaton(A, A);
  fibleft = replace_left(FIBONACCI_FROM, FIBONACCI_TO, A, A);

  /*-----------------------.
  | Creation of fibright.  |
  `-----------------------*/

  automaton_t fibright = make_automaton(A, A);
  fibright = replace_right(FIBONACCI_FROM, FIBONACCI_TO, A, A);

  /*----------.
  | Compose.  |
  `----------*/

  automaton_t	fiblr = make_automaton(A, A);
  rw_composition(fibleft, fibright, fiblr);

  automaton_t	fibrl = make_automaton(A, A);
  rw_composition(fibright, fibleft, fibrl);

  std::ofstream left_fibo("fibo_left.xml");
  std::ofstream right_fibo("fibo_right.xml");
  std::ofstream left_right_fibo("fibo_left_right.xml");
  std::ofstream right_left_fibo("fibo_right_left.xml");

  tools::xml_dump(left_fibo, fibleft, "left_fibo");
  tools::xml_dump(right_fibo, fibright, "right_fibo");
  tools::xml_dump(left_right_fibo, fiblr, "left_right_fibo");
  tools::xml_dump(right_left_fibo, fibrl, "right_left_fibo");

  std::cout << "Cautious left sequential transducer: fibo_left.xml"
	    << std::endl
	    << "Cautious right sequential transducer: fibo_right.xml"
	    << std::endl
	    << "Left transducer composed by right transducer: "
	    << "fibo_left_right.xml"
	    << std::endl
	    << "Right transducer composed by left transducer: "
	    << "fibo_right_left.xml"
	    << std::endl;

  return 0;
}
