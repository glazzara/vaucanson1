// thompson_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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

# include <vaucanson/algorithms/thompson.hh>
# include <vaucanson/algorithms/realtime.hh>
# include <vaucanson/algorithms/normalized.hh>
# include <vaucanson/algorithms/eval.hh>

# include <vaucanson/algebra/implementation/series/krat.hh>

# include <vaucanson/tools/usual_macros.hh>

# define TEST_ON(ExpStr, Exp, St, TrA, TrB, Tr1)			\
  {									\
    TEST_MSG("Basic test on " ExpStr ".");				\
									\
    krat_t	e = Exp;						\
    automaton_t	au (aa);						\
									\
    thompson_of(au, e.value());						\
									\
    TEST(t, "a has a consistent number of states.",			\
	 au.states().size() == St);					\
    int tr_a = 0;							\
    int tr_b = 0;							\
    int tr_1 = 0;							\
    int tr_X = 0;							\
    for_each_edge(e, au)						\
      {									\
	if (au.series_of(*e) == series_elt_t (ss, ma))			\
	  ++tr_a;							\
	else if (au.series_of(*e) == series_elt_t (ss, mb))		\
	  ++tr_b;							\
	else if (au.series_of(*e) ==					\
		 identity_as<series_value_t>::of(ss))			\
	  ++tr_1;							\
	else								\
	  ++tr_X;							\
      }									\
    TEST(t, "a has consistent transitions.",				\
	 tr_a == TrA and tr_b == TrB and tr_1 == Tr1 and tr_X == 0);	\
									\
    TEST(t, "a is normalized.",						\
	 e == zero_as<exp_t>::of(ss) or is_normalized(au))		\
									\
    realtime_here(au);							\
									\
    if (e != zero_as<exp_t>::of(ss))					\
      {									\
	unsigned i;							\
	for (i = 0; i < nb_word_test; ++i)				\
	  {								\
	    monoid_elt_t w = e.choose_from_supp();			\
	    if (t.verbose() == tests::high)				\
	      std::cout << "TEST: glushkov " << i << " on " << e	\
			<< " : test " << w << std::endl;		\
	    if (eval(au, w) ==						\
		zero_as<semiring_elt_value_t>::of(ss.semiring()))	\
	      {								\
		if (t.verbose() == tests::high)				\
		  std::cout << "TEST: glushkov " << i			\
			    << " failed." << std::endl;			\
		break;							\
	      }								\
	  }								\
	TEST(t, "Basic test.", nb_word_test == i);			\
      }									\
    else								\
      TEST(t, "Basic test.", true);					\
  }

template <class Auto>
bool thompson_test(tests::Tester& tg)
{
  AUTOMATON_TYPES(Auto);
  typedef vcsn::rat::exp<monoid_elt_value_t, semiring_elt_value_t>	exp_t;
  typedef vcsn::Element<series_set_t, exp_t>				krat_t;

  tests::Tester t (tg.verbose());

  alphabet_t		at;
  letter_t		la = at.random_letter();
  at.insert(la);
  letter_t		lb = at.random_letter();
  while (at.contains(lb))
    lb = at.random_letter();
  at.insert(lb);
  monoid_t		md (at);
  semiring_t		sg;
  series_set_t		ss (sg, md);
  automata_set_t	aa (ss);

  unsigned nb_word_test = 100;
  unsigned nb_test = 40;

  letter_t	lalb[] = { la, lb, letter_t () };

  monoid_elt_t	ma (md, la);
  monoid_elt_t	mb (md, lb);
  monoid_elt_t	mamb (md, lalb);

  krat_t	a (ss, ma);
  krat_t	b (ss, mb);
  krat_t	ab (ss, mamb);

  using vcsn::algebra::zero_as;
  using vcsn::algebra::identity_as;

  TEST_ON("0", zero_as<exp_t>::of(ss), 0, 0, 0, 0);
  TEST_ON("1", identity_as<exp_t>::of(ss), 2, 0, 0, 1);
  TEST_ON("a", a, 2, 1, 0, 0);
  TEST_ON("b", b, 2, 0, 1, 0);
  TEST_ON("ab", ab, 3, 1, 1, 0);
  TEST_ON("a.b", a * b, 3, 1, 1, 0);
  TEST_ON("a+b", a + b, 6, 1, 1, 4);
  TEST_ON("a*", krat_t (a).star(), 4, 1, 0, 4);
  TEST_ON("(a+b)*a(a+b)*", (a + b).star() * a * (a + b).star(), 16, 3, 2, 16);

  {
    TEST_MSG("Tests on random expressions.");
    unsigned success = 0;
    unsigned nb_test_done = 0;
    
    for (unsigned nb = 0; nb < nb_test; ++nb)
      {
	krat_t		exp = ss.choose(SELECT(exp_t));
	automaton_t	au (aa);

	try
	  {
	    thompson_of(au, exp.value());
	    bool normalized = is_normalized(au) or
	      exp == zero_as<exp_t>::of(ss);
	    realtime_here(au);

	    if (t.verbose() == tests::high)
	      {
		TEST_MSG("Automaton saved in /tmp.");
		SAVE_AUTOMATON_DOT("/tmp", "thompson", au, nb);
	      }
	    unsigned i = 0;
	    if (exp != ss.zero(SELECT(exp_t)))
	      for (; i < nb_word_test; ++i)
		{
		  monoid_elt_t w = exp.choose_from_supp();
		  if (t.verbose() == tests::high)
		    std::cout << "TEST: thompson (" << nb << ")"
			      << i << " : test " << w << std::endl;
		  if (eval(au, w) ==
		      zero_as<semiring_elt_value_t>::of(ss.semiring()))
		    {
		      if (t.verbose() == tests::high)
			std::cout << "TEST: thompson " << i
				  << " failed." << std::endl;
		      break;
		    }
		}
	    if (normalized and
		((nb_word_test == i) || (exp == ss.zero(SELECT(exp_t)))))
	      ++success;
	    ++nb_test_done;
	  }
	catch (std::logic_error&)
	  {
	    ++nb_test;
	  }
      }
    std::string rate;
    SUCCESS_RATE(rate, success, nb_test_done);
    TEST(t, "Random test " + rate, success == nb_test_done);
  }
  return t.all_passed();
}

#endif // VCSN_TESTS_AUTOMATA_ALGOS_THOMPSON_TEST_HH
