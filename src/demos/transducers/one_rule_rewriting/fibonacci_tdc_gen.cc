// fibonacci_tdc_gen.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/fmp_transducer.hh>
#include <vaucanson/algorithms/realtime_to_fmp.hh>
#include <vaucanson/algorithms/normalized_composition.hh>
#include <vaucanson/algorithms/sub_normalize.hh>
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

  automaton_t		fibleft = new_automaton(A, A);

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

  fmp_transducer::automaton_t fmp_fibleft =
    fmp_transducer::new_automaton(A, A);

  fmp_transducer::automaton_t sub_fibleft =
    fmp_transducer::new_automaton(A, A);

  realtime_to_fmp(fibleft, fmp_fibleft);

  sub_normalize(fmp_fibleft, sub_fibleft);

  /*-----------------------.
  | Creation of fibright.  |
  `-----------------------*/

  automaton_t fibright = new_automaton(A, A);

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


  fmp_transducer::automaton_t fmp_fibright =
    fmp_transducer::new_automaton(A, A);

  fmp_transducer::automaton_t sub_fibright =
    fmp_transducer::new_automaton(A, A);

  realtime_to_fmp(fibright, fmp_fibright);

  sub_normalize(fmp_fibright, sub_fibright);

  /*----------.
  | Compose.  |
  `----------*/

  fmp_transducer::automaton_t	fiblr = fmp_transducer::new_automaton(A, A);
  normalized_composition(sub_fibleft, sub_fibright, fiblr);

  fmp_transducer::automaton_t	fibrl = fmp_transducer::new_automaton(A, A);
  normalized_composition(sub_fibright, sub_fibleft, fibrl);

  std::ofstream left_fibo("fibo_fmp_left.xml");
  std::ofstream right_fibo("fibo_fmp_right.xml");
  std::ofstream left_right_fibo("fibo_fmp_left_right.xml");
  std::ofstream right_left_fibo("fibo_fmp_right_left.xml");

  tools::xml_dump(left_fibo, sub_fibleft, "left_fibo");
  tools::xml_dump(right_fibo, sub_fibright, "right_fibo");
  tools::xml_dump(left_right_fibo, fiblr, "left_right_fibo");
  tools::xml_dump(right_left_fibo, fibrl, "right_left_fibo");


  std::cout << "Cautious left sequential transducer: fibo_fmp_left.xml"
	    << std::endl
	    << "Cautious right sequential transducer: fibo_fmp_right.xml"
	    << std::endl
	    << "Left transducer composed by right transducer: "
	    << "fibo_fmp_left_right.xml"
	    << std::endl
	    << "Right transducer composed by left transducer: "
	    << "fibo_fmp_right_left.xml"
	    << std::endl;
}

