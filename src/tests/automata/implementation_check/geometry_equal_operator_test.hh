// geometry_equal_operator_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>


/*
  Description:

  This test checks if the '=' operator is correctly implemented in the geometry
  class.
  It used to crash when we made a copy of the transducer and we deleted both.
  It was due to the pointer attributes of the tranduscer which were copied
  directly without allocating new space memory. As pointers were freed in the
  destructor, attributes were destructed twice, causing a segfault.
*/


template <class Auto>
unsigned geometry_equal_operator_test(tests::Tester& tg)
{
  tests::Tester	t(tg.verbose());

  AUTOMATON_TYPES(Auto);

  using namespace vcsn;
  using namespace vcsn::algebra;

  bool		ok = true;

  /*--------------------------.
  | Creation of an automaton. |
  `--------------------------*/
  typedef GenRandomAutomata<Auto> gen_auto_t;
  gen_auto_t gen(time(0x0));
  automaton_t rttdc(gen.generate_dfa(10).structure());

  /*-------------------------.
  | Copy of this automaton.  |
  `-------------------------*/
  automaton_t	aut(rttdc.structure());

  aut.geometry().initials();
  rttdc.geometry().initials();
  aut = rttdc;

  /*----------------------------------------------------------------------.
  | If '=' operator is correctly implemented, pointers stored in geometry |
  | have to be different.						  |
  `----------------------------------------------------------------------*/

  if (&(aut.geometry().initials()) == &(rttdc.geometry().initials()))
    ok = false;

  TEST(t, "Check geometry operator '=' implementation.", ok);
  return t.all_passed();
}
