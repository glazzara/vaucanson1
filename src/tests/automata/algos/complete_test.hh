// complete_test.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef COMPLETE_TEST_HH
# define COMPLETE_TEST_HH

# include <vaucanson/fundamental/fundamental.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/complementary.hh>
# include <vaucanson/algorithms/complete.hh>
# include <vaucanson/algorithms/trim.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/misc/dot_dump.hh>

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;

template <class Auto>
unsigned complete_test(tests::Tester& tg)
{  
  tests::Tester t(tg.verbose());
  typedef Auto			  automaton_t;
  typedef GenRandomAutomata<Auto> gen_auto_t;
  
  gen_auto_t gen(time(0x0));

  const unsigned nb_test = 100;
  unsigned nb_success    = 0;

  for (unsigned i = 0 ; i < nb_test; i++) 
    {
      automaton_t a = gen.generate_dfa(20);
      automaton_t b = a;
      complete_here(a);
      
      if ((a.edges().size() == a.states().size() * 
	   a.set().series().monoid().alphabet().size()) 
	  && is_deterministic(a))
	++nb_success;
      else
	{
	  misc::dot_dump(std::cout, b, "input");
	  misc::dot_dump(std::cout, a, "automaton");
	}
     }
  std::string rate;
  SUCCESS_RATE(rate, nb_success, nb_test);
  TEST(t, "complete on DFA." + rate, nb_success == nb_test);
  return t.all_passed();
}

#endif // COMPLETE_TEST_HH
