// fibonacci_rt_gen.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/boolean_transducer.hh>
#include <vaucanson/algorithms/realtime_composition.hh>
#include <vaucanson/tools/xml_dump.hh>


int main()
{
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

  hstate_t p = fibleft.add_state();
  hstate_t q = fibleft.add_state();
  hstate_t r = fibleft.add_state();

  fibleft.add_io_transition(p, p, "b", "b");
  fibleft.add_io_transition(p, q, "a", "");
  fibleft.add_io_transition(q, q, "a", "a");
  fibleft.add_io_transition(q, r, "b", "");
  fibleft.add_io_transition(r, q, "a", "ab");
  fibleft.add_io_transition(r, q, "b", "ba");

  fibleft.set_o_final(q, "a");

  fibleft.set_o_final(r, "ab");

  fibleft.set_final(p);
  fibleft.set_initial(p);

  /*-----------------------.
  | Creation of fibright.  |
  `-----------------------*/

  automaton_t fibright = make_automaton(A, A);

  hstate_t s = fibright.add_state();
  hstate_t t = fibright.add_state();
  hstate_t u = fibright.add_state();

  fibright.add_io_transition(s, s, "b", "b");
  fibright.add_io_transition(s, t, "b", "");
  fibright.add_io_transition(t, s, "a", "aa");
  fibright.add_io_transition(t, u, "b", "");
  fibright.add_io_transition(u, t, "a", "ab");
  fibright.add_io_transition(u, u, "a", "a");

  fibright.set_o_initial(s, "bb");

  fibright.set_o_initial(t, "b");

  fibright.set_initial(u);
  fibright.set_final(u);


  /*----------.
  | Compose.  |
  `----------*/

  automaton_t	fiblr = make_automaton(A, A);
  realtime_composition(fibleft, fibright, fiblr);

  automaton_t	fibrl = make_automaton(A, A);
  realtime_composition(fibright, fibleft, fibrl);

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
}

