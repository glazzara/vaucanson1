// complete_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_COMPLETE_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_COMPLETE_TEST_HH

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/complete.hh>
# include <vaucanson/algorithms/trim.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/tools/usual_macros.hh>

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;

template <class Auto>
unsigned complete_test(tests::Tester& tg)
{  
  tests::Tester t(tg.verbose());
  typedef Auto				automaton_t;
  typedef GenRandomAutomata<Auto>	gen_auto_t;
  AUTOMATON_TYPES(automaton_t);
  
  gen_auto_t				gen(time(0x0));

  const unsigned			nb_test = 50;
  unsigned				nb_success = 0;

  typedef std::set<hstate_t>		delta_ret_t;
  delta_ret_t				delta_ret;
  bool					result_test;
  
  for (unsigned i = 0 ; i < nb_test; i++) 
    {
      automaton_t a = gen.generate_dfa(30);
      automaton_t b = a;
      complete_here(a);
      alphabet_t alphabet = a.structure().series().monoid().alphabet();
      result_test = true;

      if ((a.edges().size() == a.states().size() * 
	   a.structure().series().monoid().alphabet().size()) 
	  && is_deterministic(a))
	{
	  for (alphabet_iterator l = alphabet.begin();
	       l != alphabet.end();
	       ++l)
	    {
	      for_each_state(s, a)
		{
		  delta_ret.clear();
		  a.letter_deltac(delta_ret, *s, *l,
				  delta_kind::states());
		  if (delta_ret.size() == 0)
		    result_test = false;
		}
	    }
	  if (result_test)
	    ++nb_success;
	}
      else if (tg.verbose() == tests::high)
	{
	  tools::dot_dump(std::cout, b, "input");
	  tools::dot_dump(std::cout, a, "automaton");
	}
     }
  std::string rate;
  SUCCESS_RATE(rate, nb_success, nb_test);
  TEST(t, "complete on DFA." + rate, nb_success == nb_test);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_COMPLETE_TEST_HH
