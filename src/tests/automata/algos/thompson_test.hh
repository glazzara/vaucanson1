// thompson_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_THOMPSON_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_THOMPSON_TEST_HH

# include <check/tester.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/automata/concrete/generalized.hh>
# include <vaucanson/algorithms/thompson.hh>
# include <vaucanson/algorithms/eval.hh>
# include <vaucanson/algorithms/realtime.hh>

using namespace vcsn;

template <class Auto>
bool thompson_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  typedef rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef Element<series_t, exp_t>		krat_t;
  tests::Tester t(tg.verbose());

  alphabet_t alphabet;
  letter_t a = alphabet.random_letter();
  letter_t b = alphabet.random_letter();
  alphabet.insert(a);
  alphabet.insert(b);
  monoid_t monoid(alphabet);
  semiring_t semiring;
  series_t s(semiring, monoid);

  unsigned nb_word_test = 100;
  unsigned nb_test = 100;

  {
    TEST_MSG("Basic test on a well known expression.");
    krat_t exp(s);
    krat_t a_e(s, monoid_elt_t(b));
    exp = monoid_elt_t(a);
    exp = (a_e + exp).star();
    exp = exp * a_e * exp;
    vcsn::tools::GenRandomAutomata<Auto> gen(time(0));
    Auto	au = gen.empty();
    thompson_of(au, exp.value());
    realtime_here(au);
    unsigned i = 0;
    for (; i < nb_word_test; ++i)
      {
	monoid_elt_t w = exp.choose_from_supp();
	if (t.verbose() == tests::high)
	  std::cout << "TEST: thompson " << i << " : test " << w << std::endl;
	if (eval(au, w) == zero_as<semiring_elt_value_t>::of(s.semiring()))
	  {
	    break;
	    if (t.verbose() == tests::high)
	      std::cout << "TEST: thompson " << i << " failed." << std::endl;
	  }
      }
    TEST(t, "Basic test ", nb_word_test == i);
  }
  
  {
    TEST_MSG("Tests on random expressions.");
    unsigned success = 0;

    for (unsigned nb = 0; nb < nb_test; ++nb)
      {
	krat_t exp = s.choose(SELECT(exp_t));
	vcsn::tools::GenRandomAutomata<Auto> gen(time(0));
	Auto	au = gen.empty();
	thompson_of(au, exp.value());
	realtime_here(au);
	if (t.verbose() == tests::high)
	  {
	    TEST_MSG("Automaton saved in /tmp.");
	    SAVE_AUTOMATON_DOT("/tmp", "thompson", au, nb);
	  }
	unsigned i = 0;
	if (exp != s.zero(SELECT(exp_t)))
	  for (; i < nb_word_test; ++i)
	    {
	      monoid_elt_t w = exp.choose_from_supp();
	      if (t.verbose() == tests::high)
		std::cout << "TEST: thompson (" << nb << ")" 
			  << i << " : test " << w << std::endl;
	      if (eval(au, w) == zero_as<semiring_elt_value_t>::of(s.semiring()))
		{
		  if (t.verbose() == tests::high)
		    std::cout << "TEST: thompson " << i << " failed." << std::endl;
		  break;
		}
	    }
	if ((nb_word_test == i) || (exp == s.zero(SELECT(exp_t))))
	  ++success;
      }
    std::string rate;
    SUCCESS_RATE(rate, success, nb_test);
    TEST(t, "Random test " + rate, success == nb_test);
  }
  return t.all_passed();
}

#endif // VCSN_TESTS_AUTOMATA_ALGOS_THOMPSON_TEST_HH
