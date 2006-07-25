// closure_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_CLOSURE_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_CLOSURE_TEST_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <tests/check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/algorithms/closure.hh>

template <class Auto>
bool closure_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  typedef Auto automaton_t;
  AUTOMATON_TYPES(Auto);

  tests::Tester t(tg.verbose());
  GenRandomAutomata<automaton_t> gen(time(0x0));

  bool error_forward_idempotence = false;
  bool error_forward_epsilon = false;
  bool error_backward_idempotence = false;
  bool error_backward_epsilon = false;

  int nb_test = 50;

  for (int i = 0; i < nb_test; ++i)
  {
    try
    {
      automaton_t auto_epsilon = gen.generate_with_epsilon(30, 50, 10, 20);
      {
	automaton_t cauto = backward_closure(auto_epsilon);

	if (backward_closure(cauto).transitions().size() !=
	    cauto.transitions().size())
	  error_backward_idempotence = true;
	for_all_transitions(e, cauto)
	  if (cauto.series_of(*e) ==
	      identity_as<series_set_elt_value_t>::
	      of(cauto.structure().series()))
	    error_backward_epsilon = true;
	if (error_backward_idempotence or error_backward_epsilon)
	{
	  TEST_MSG("Automata saved in /tmp.");
	  SAVE_AUTOMATON_DOT("/tmp",
			     "backward_closure_in",
			     auto_epsilon,
			     i);
	  SAVE_AUTOMATON_DOT("/tmp", "backward_closure_out", cauto, i);
	  break;
	}
      }

      {
	automaton_t cauto = forward_closure(auto_epsilon);

	if (forward_closure(cauto).transitions().size() !=
	    cauto.transitions().size())
	  error_forward_idempotence = true;
	for_all_transitions(e, cauto)
	  if (cauto.series_of(*e) ==
	      identity_as<series_set_elt_value_t>::
	      of(cauto.structure().series()))
	    error_forward_epsilon = true;
	if (error_backward_idempotence or error_backward_epsilon)
	{
	  TEST_MSG("Automata saved in /tmp.");
	  SAVE_AUTOMATON_DOT("/tmp",
			     "forward_closure_in",
			     auto_epsilon,
			     i);
	  SAVE_AUTOMATON_DOT("/tmp", "forward_closure_out", cauto, i);
	  break;
	}
      }
    }
    catch (std::logic_error&)
    {
      ++nb_test;
    }
  }

  TEST(t, "Backward: Idempotence.", not error_backward_idempotence);
  TEST(t, "Backward: No more epsilon transition.",
       not error_backward_epsilon);
  TEST(t, "Forward: Idempotence.", not error_forward_idempotence);
  TEST(t, "Forward: No more epsilon transition.", not error_forward_epsilon);

  // FIXME:  A good  idea would	 be  to generate  words recognized  by
  // auto_epsilon and to  check that they are recognize	 by cauto. The
  // same process should be done also on unrecognized words.

  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_LABEL_AWARE_GRAPHS_CLOSURE_TEST_HH
