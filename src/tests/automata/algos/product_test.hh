// product_test.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_PRODUCT_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_PRODUCT_TEST_HH

# include <time.h>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <check/tester.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/determinize.hh>
# include <vaucanson/algorithms/transpose.hh>
# include <vaucanson/algorithms/product.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/algorithms/complement.hh>
# include <vaucanson/algorithms/complete.hh>
# include <vaucanson/algorithms/trim.hh>

using namespace vcsn;
using namespace vcsn::algebra;
using namespace vcsn::tools;

template <class Auto>
unsigned product_test(tests::Tester& tg)
{  
  typedef Auto automaton_t;
  GenRandomAutomata<automaton_t> gen(time(0x0));
  tests::Tester t(tg.verbose());

  const unsigned nb_test    = 30;
  unsigned success_identity = 0;
  unsigned success_null     = 0;

  for (unsigned i = 0 ; i < nb_test; i++) 
    {
      automaton_t a = gen.generate(10, 20);
      
      complete_here(a);
      a = determinize(a);  
      automaton_t ac = complement(a);
      automaton_t squared = product(a,a);

      if ((squared.states().size() == a.states().size()) &&
	  (squared.edges().size() == a.edges().size()))
	success_identity++;
      
      if (trim(product(a, ac)).states().size() == 0)
	success_null++;
    }
  
  std::string rate_identity;
  std::string rate_null;
  SUCCESS_RATE(rate_identity, success_identity, nb_test);
  TEST(t,"Square of a complete deterministic automaton." + rate_identity,
       success_identity == nb_test);
  SUCCESS_RATE(rate_null, success_null, nb_test);
  TEST(t, "Product of complete automaton and its complementary." +
       rate_null,
       success_null == nb_test);
  return t.all_passed();
}

#endif // VCSN_TESTS_AUTOMATA_ALGOS_PRODUCT_TEST_HH
