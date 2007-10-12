// fibonacci_demo.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/boolean_transducer.hh>

#include <vaucanson/algorithms/krat_exp_expand.hh>
#include <vaucanson/algorithms/realtime_composition.hh>

#include <vaucanson/tools/dot_display.hh>

void
eval_an_expression(const vcsn::boolean_transducer::automaton_t& t)
{
  using namespace vcsn::boolean_transducer;

  const alphabet_t&	alphabet = t.structure().series().monoid().alphabet();
  std::string		user_string;

  do
  {
    std::cout << "Enter your expression over " << alphabet
	      <<" (\"next\", otherwise): ";
    std::getline(std::cin, user_string);
    if (user_string != "next")
    {
      using namespace vcsn::boolean_automaton;
      using namespace vcsn::rat; // For setpm and MODE_STAR.

      rat_exp_t exp = make_rat_exp(alphabet, user_string);
      std::cout << setpm (MODE_STAR) << expand(evaluation(t, exp))
		<< std::endl;
    }

  }
  while (user_string != "next");
}

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

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  tools::dot_display(fibleft, "fibleft", true);
  eval_an_expression(fibleft);


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


  /*----------------.
  | Dump and eval.  |
  `----------------*/

  tools::dot_display(fibright, "fibright", true);
  eval_an_expression(fibright);


  /*----------.
  | Compose.  |
  `----------*/

  automaton_t	fiblr = make_automaton(A, A);
  realtime_composition(fibleft, fibright, fiblr);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  tools::dot_display(fiblr, "fiblr", true);
  eval_an_expression(fiblr);

}

