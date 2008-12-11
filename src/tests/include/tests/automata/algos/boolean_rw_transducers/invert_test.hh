// invert.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_RW_TRANSDUCERS_INVERT_TEST_HH
# define VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_RW_TRANSDUCERS_INVERT_TEST_HH

# include <tests/check/tester.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algorithms/invert.hh>
# include <vaucanson/algorithms/eval.hh>

using namespace vcsn;

// FIXME: - Write more tests.x
template <class Auto>
static bool test_exp(const Auto& trans,
		     const Auto& trans_inverse,
		     const automaton::rat_exp_t& exp1)
{
  automaton::rat_exp_t exp2 = rw_transducer::evaluation(trans, exp1);
  automaton::rat_exp_t exp3 = rw_transducer::evaluation(trans_inverse, exp2);

  return are_equivalent(automaton::standard_of(exp1),
			automaton::standard_of(exp3));
}

template <typename T>
bool
is_valid(T l)
{
  typedef algebra::letter_traits<T> traits_t;

  // . will be used as the series times representation
  return traits_t::letter_to_literal(l) != ".";
}

template <class Auto>
bool invert_test(tests::Tester& tg)
{
  tests::Tester t(tg);

  unsigned nb_succeed = 0;
  unsigned test_num = 0;

  AUTOMATON_TYPES(Auto);
  AUTOMATON_FREEMONOID_TYPES(Auto);

  alphabet_t alpha;
  letter_t a = alpha.random_letter();
  while (!is_valid(a)) a = alpha.random_letter();
  letter_t b = alpha.random_letter();
  while (!is_valid(b) or a == b) b = alpha.random_letter();
  alpha.insert(a);
  alpha.insert(b);

  automaton_t trans = rw_transducer::make_automaton(alpha, alpha);
  automaton_t trans_inverse = rw_transducer::make_automaton(alpha, alpha);

  hstate_t s1 = trans.add_state();
  hstate_t s2 = trans.add_state();
  hstate_t s3 = trans.add_state();

  trans.set_initial(s1);
  trans.set_final(s3);

  trans.add_io_transition(s1, s2, a, b);
  trans.add_io_transition(s2, s1, b, a);
  trans.add_io_transition(s2, s3, b, a);
  trans.add_io_transition(s3, s2, a, b);

  invert(trans, trans_inverse);

  //tools::dot_display(trans, "trans", true);



  /*-----------------.
  | Evaluation tests |
  `-----------------*/

  std::ostringstream rat;
  rat << a << "." << b << "." << a << "." << b;

  automaton::rat_exp_t exp1 = automaton::make_rat_exp(alpha, rat.str(),
						      *(trans.series().monoid().representation()),
						      *(trans.series().semiring().representation()));

  test_num++;
  if (test_exp(trans, trans_inverse, exp1))
    nb_succeed++;
  else
    std::cerr << "Failed at first evaluation test" << std::endl;

  rat << "." << a << "." << b;

  exp1 = automaton::make_rat_exp(alpha, rat.str(),
				 *(trans.series().monoid().representation()),
				 *(trans.series().semiring().representation()));
  test_num++;
  if (test_exp(trans, trans_inverse, exp1))
    nb_succeed++;
  else
    std::cerr << "Failed at second evaluation test" << std::endl;



  /*-------.
  | SUM UP |
  `-------*/
  std::string rate;
  SUCCESS_RATE(rate, nb_succeed, test_num);

  TEST(t, "Invert on RW transducers." + rate, nb_succeed == test_num);
  return t.all_passed();
}

#endif // ! VCSN_TESTS_AUTOMATA_ALGOS_BOOLEAN_RW_TRANSDUCERS_INVERT_TEST_HH
