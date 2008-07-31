// fibonacci_demo.cc: this file is part of the Vaucanson project.
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

  automaton_t fibleft = make_automaton(A, A);
  fibleft = replace_left(FIBONACCI_FROM, FIBONACCI_TO, A, A);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  eval_an_expression(fibleft, "fibleft");

  /*-----------------------.
  | Creation of fibright.  |
  `-----------------------*/

  automaton_t fibright = make_automaton(A, A);
  fibright = replace_right(FIBONACCI_FROM, FIBONACCI_TO, A, A);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  eval_an_expression(fibright, "fibright");

  /*----------.
  | Compose.  |
  `----------*/

  automaton_t	fiblr = make_automaton(A, A);
  rw_composition(fibleft, fibright, fiblr);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  eval_an_expression(fiblr, "fiblr");

  return 0;
}
