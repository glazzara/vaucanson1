// concat_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_CONCAT_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_CONCAT_TEST_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/concatenate.hh>
# include <vaucanson/algorithms/aut_to_exp.hh>
# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/automata/implementation/generalized.hh>

template <class Auto>
bool concat_test(tests::Tester& tg)
{
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::tools;

  AUTOMATON_TYPES(Auto);
  typedef typename generalized_traits<Auto>::automaton_t generalized_t;
  AUTOMATON_TYPES_(generalized_t, g_);

  unsigned int nb_test = 20;
  unsigned int nb_test_done = 0;
  unsigned int size    = 0;
  tests::Tester t(tg.verbose());

  GenRandomAutomata<Auto> gen(time(0x0));
  for (unsigned i = 0; i < nb_test; ++i)
    {
      automaton_t auto_lhs = gen.generate_with_epsilon(5, 10, 3, 7);
      automaton_t auto_rhs = gen.generate_with_epsilon(auto_lhs.structure(),
						       5, 10, 3, 7);
      generalized_t g_auto_lhs = generalized(auto_lhs);
      generalized_t g_auto_rhs = generalized(auto_rhs);
      g_series_set_elt_t exp_lhs(g_auto_lhs.structure().series());
      g_series_set_elt_t exp_rhs(g_auto_rhs.structure().series());
      exp_lhs = aut_to_exp(g_auto_lhs);
      exp_rhs = aut_to_exp(g_auto_rhs);
      monoid_elt_t word_1 = exp_lhs.choose_from_supp();
      monoid_elt_t word_2 = exp_rhs.choose_from_supp();
      monoid_elt_t word = word_1 * word_2;
     
      try
	{
	  automaton_t ret = concatenate(auto_lhs, auto_rhs);
	  semiring_elt_t val =
	    eval(determinize(realtime(auto_lhs)), word_1) *
	    eval(determinize(realtime(auto_rhs)), word_2);
	  if (ret.states().size() ==
	      auto_lhs.states().size() + auto_rhs.states().size() &&
	      eval(determinize(realtime(ret)), word) == val)
	    ++size;
	  else
	    {
	      std::cerr << "TEST: concatenation of automata corresponding"
			<< "to following expressions failed."
			<< std::endl;
	      std::cerr << "TEST: " << exp_lhs << " and " << exp_rhs
			<< std::endl;
	    }
	  ++nb_test_done;
	}
      catch (std::logic_error&)
	{
	  ++nb_test;
	}
    }

  std::string size_rate;
  SUCCESS_RATE(size_rate, size, nb_test_done);
  TEST(t, "Concatenation of two automata." + size_rate,
       size == nb_test_done);
  // FIXME: add tests based on samples from the languages.
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_CONCAT_TEST_HH
