// closure_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003,2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_CLOSURE_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_CLOSURE_TEST_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/algorithms/backward_closure.hh>
# include <vaucanson/algorithms/forward_closure.hh>

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

  for (int i = 0; i < 50 ; ++i)
    {
      automaton_t auto_epsilon = gen.generate_with_epsilon(30, 50, 10, 20);
      {
	automaton_t cauto = backward_closure(auto_epsilon);

	if (backward_closure(cauto).edges().size() != cauto.edges().size())
	  error_backward_idempotence = true;
	for_each_edge(e, cauto)
	  if (cauto.series_of(*e) ==
	      identity_as<series_value_t>::of(cauto.structure().series()))
	    error_backward_epsilon = true;
	if (error_backward_idempotence or error_backward_epsilon)
	  {
	    std::cerr << "Error, automata saved in /tmp." << std::endl;
	    SAVE_AUTOMATON_DOT("/tmp", "backward_closure_in", auto_epsilon, i);
	    SAVE_AUTOMATON_DOT("/tmp", "backward_closure_out", cauto, i);
	    break;
	  }
      }

      {
	automaton_t cauto = forward_closure(auto_epsilon);

	if (forward_closure(cauto).edges().size() != cauto.edges().size())
	  error_forward_idempotence = true;
	for_each_edge(e, cauto)
	  if (cauto.series_of(*e) ==
	      identity_as<series_value_t>::of(cauto.structure().series()))
	    error_forward_epsilon = true;
	if (error_backward_idempotence or error_backward_epsilon)
	  {
	    std::cerr << "Error, automata saved in /tmp." << std::endl;
	    SAVE_AUTOMATON_DOT("/tmp", "forward_closure_in", auto_epsilon, i);
	    SAVE_AUTOMATON_DOT("/tmp", "forward_closure_out", cauto, i);
	    break;
	  }
      }
    }

  TEST(t, "Backward: Idempotence.", not error_backward_idempotence);
  TEST(t, "Backward: No more epsilon transition.",
       not error_backward_epsilon);
  TEST(t, "Forward: Idempotence.", not error_forward_idempotence);
  TEST(t, "Forward: No more epsilon transition.", not error_forward_epsilon);

  // FIXME:  A good  idea would  be  to generate  words recognized  by
  // auto_epsilon and to  check that they are recognize  by cauto. The
  // same process should be done also on unrecognized words.

  return t.all_passed();
}

#endif // VCSN_TESTS_AUTOMATA_ALGOS_CLOSURE_TEST_HH
