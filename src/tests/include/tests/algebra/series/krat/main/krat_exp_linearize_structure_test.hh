// krat_exp_linearize_structure_test.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_LINEARIZE_STRUCTURE_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_LINEARIZE_STRUCTURE_TEST_HH

# include <vaucanson/algorithms/krat_exp_linearize.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/tools/gen_random.hh>

/**
 * @file  krat_exp_linearize_structure_test.hh
 *
 * Checks the structure of a linearized expression.
 */

template <class Expr>
bool
krat_exp_linearize_structure_test(tests::Tester& tg)
{
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
  typedef
    typename vcsn::linearize_element<series_set_t, kexp_t> linearize_element_t;
  typedef
    typename linearize_element_t::element_t		out_krat_exp_t;

  tests::Tester t(tg);

  alphabet_t	alphabet;
  letter_t	a = 'a';
  letter_t	b = 'b';
  alphabet.insert(a);
  alphabet.insert(b);
  monoid_t	monoid (alphabet);
  semiring_t	semiring;
  series_set_t	s (semiring, monoid);

  unsigned	nb_succs = 0;

  for (unsigned n = 0; n < t.test_num(); ++n)
  {
    krat_exp_t	exp = s.choose(SELECT(kexp_t));
    out_krat_exp_t	lin = linearize(exp);
    std::stringstream	exp_str;
    std::stringstream	lin_str;

    exp_str << exp;

    lin_str << lin;
    std::string ls = lin_str.str();
    // Replace (x,y) by x.
    // I.e. remove the numeration from the linearized expressions.
    // We should get the original expression.
    std::string lin_filt;
    int len = ls.size();
    for (int i = 0; i < len; ++i)
      {
	if ((ls[i] == '(') && (i + 2 < len) && (ls[i + 2] == ','))
	  {
	    lin_filt += ls[i + 1];
	    // Skip until the closing ')'.
	    i += 4;
	    while (ls[i] != ')') ++i;
	  }
	else
	  {
	    lin_filt += ls[i];
	  }
      }

    if (exp_str.str() != lin_filt)
    {
      TEST_FAIL_SAVE("exp_linearize_structure",
		     n,
		     exp_str.str() << "!=" << lin_filt << std::endl);
    }
    else
      ++nb_succs;
  }

  std::string rate;
  SUCCESS_RATE(rate, nb_succs, t.test_num());
  TEST(t, "Structure of linearize(exp) is the same as exp. " + rate,
       t.test_num() == nb_succs);

  return t.all_passed();
}

#endif // ! VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_LINEARIZE_STRUCTURE_TEST_HH
