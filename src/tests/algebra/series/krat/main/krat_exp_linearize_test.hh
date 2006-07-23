// krat_exp_linearize_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_LINEARIZE_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_LINEARIZE_TEST_HH

# include <check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/algorithms/krat_exp_linearize.hh>
# include <vaucanson/algorithms/krat_exp_flatten.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <list>

template <class Expr>
bool krat_exp_linearize_test(tests::Tester& tg)
{
  using namespace vcsn::misc;
  // Original types (for the input expression).
  typedef Expr						krat_exp_t;
  typedef typename krat_exp_t::value_t			kexp_t;
  typedef typename krat_exp_t::monoid_elt_t		monoid_elt_t;
  typedef typename monoid_elt_t::set_t			monoid_t;
  typedef typename krat_exp_t::semiring_elt_t		semiring_elt_t;
  typedef typename semiring_elt_t::set_t		semiring_t;
  typedef typename krat_exp_t::set_t			series_set_t;
  typedef typename monoid_t::letter_t			letter_t;
  typedef typename monoid_t::alphabet_t			alphabet_t;

  // Output types (for the linearized expression).
  typedef typename vcsn::linearize_element<series_set_t, kexp_t>
							linearize_element_t;
  typedef typename linearize_element_t::element_t	out_krat_exp_t;

  tests::Tester t(tg.verbose());
  srand(time(0));
  const unsigned int nb_tests_final = 100;

  unsigned int nb_tests = 0;
  unsigned int nb_succs = 0;
  for (unsigned int n = 0; n < nb_tests_final; ++n)
    {
      ++nb_tests;
      bool success = true;

      alphabet_t alphabet;
      letter_t a = alphabet.random_letter();
      letter_t b = alphabet.random_letter();
      alphabet.insert(a);
      alphabet.insert(b);
      monoid_t monoid(alphabet);
      semiring_t semiring;
      series_set_t s(semiring, monoid);


      krat_exp_t		exp = s.choose(SELECT(kexp_t));
      std::list<letter_t>	lexp = flatten(exp);

      out_krat_exp_t		lin = linearize(exp);
      std::list<typename linearize_element_t::letter_t>
				llin = flatten(lin);

      typename std::list<letter_t>::const_iterator j = lexp.begin();
      typename std::list<typename linearize_element_t::letter_t>::
	const_iterator i = llin.begin();
      for ( ; (i != llin.end()) and (j != lexp.end()); ++i, ++j)
	{
	  // Each letter should be in the alphabet.
	  if (lin.structure().monoid().alphabet().value().find(*i) ==
	      lin.structure().monoid().alphabet().value().end())
	    {
	      success = false;
	      TEST_FAIL_SAVE("krat_exp_linearize",
			     nb_tests,
			     "in: " << exp << std::endl
			     << "out: " << lin << std::endl
			     << "Letter not in alphabet: " << *i << "."
			     << std::endl);
	    }
	  // The letter should not exists anywhere else.
	  unsigned int t;
	  if ((t = count(llin.begin(), llin.end(), *i)) != 1)
	    {
	      success = false;
	      TEST_FAIL_SAVE("krat_exp_linearize",
			     nb_tests,
			     "in: " << exp << std::endl
			     << "out: " << lin << std::endl
			     << "Letter <<" << *i << ">> found " << t
			     << " times in the expression instead of 1."
			     << std::endl);
	    }
	  // The letter should be the same in both expressions.
	  if (i->first != *j)
	    {
	      success = false;
	      TEST_FAIL_SAVE("krat_exp_linearize",
			     nb_tests,
			     "in: " << exp << std::endl
			     << "out: " << lin << std::endl
			     << "Letter <<" << *i << ">> in the linearized"
			     "expression does not match letter " << *j <<
			     " in the base expression." << std::endl);
	    }
	}
      if (success)
	++nb_succs;
    }

  std::string rate;
  SUCCESS_RATE(rate, nb_succs, nb_tests);
  TEST(t, "Linearize on lots of random expressions " + rate,
       nb_tests == nb_succs);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_LINEARIZE_TEST_HH
