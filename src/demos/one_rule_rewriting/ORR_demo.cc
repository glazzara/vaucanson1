// ORR_demo.cc: this file is part of the Vaucanson project.
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

int
main()
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::boolean_transducer;
  using namespace ORR;

  alphabet_t A;

  A.insert('a');
  A.insert('b');

  // there is only one rule: from -> to
  std::string from, to;

  std::cout << "Enter your pattern over " << A << " : ";
  std::cin >> from;

  std::cout << "Enter your replacement pattern over " << A << " : ";
  std::cin >> to;

  /*-----------------.
  | Left automaton.  |
  `-----------------*/

  automaton_t left_auto = replace_left(from, to, A, A);

  // we need the left automaton to be realtime
  realtime_here(left_auto);

  eval_an_expression(left_auto, "L");

  /*------------------.
  | Right automaton.  |
  `------------------*/

  automaton_t right_auto = replace_right(from, to, A, A);

  eval_an_expression(right_auto, "R");

  /*-------------------.
  | Result automaton.  |
  `-------------------*/

  automaton_t res_auto = make_automaton(A, A);

  rw_composition(left_auto, right_auto, res_auto);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  eval_an_expression(res_auto, "LR");

  return 0;
}
