// glushkov_test.hh
//
// $Id$
// VCSN_HEADER
#ifndef GLUSHKOV_TEST_HH
# define GLUSHKOV_TEST_HH

# include <check/tests_stuff.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/dot_dump.hh>
# include <vaucanson/tools/gen_random.hh>
# include <vaucanson/tools/usual.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/automata/concrete/generalized.hh>
# include <vaucanson/algorithms/glushkov.hh>

using namespace vcsn;

template <class Auto>
bool glushkov_test(tests::Tester& t)
{
  AUTOMATON_TYPES(Auto);
  typedef rat::exp<monoid_elt_value_t, weight_value_t>	exp_t;
  typedef Element<series_t, exp_t>		krat_t;

  series_t s;
  krat_t exp(s);
  letter_t a = exp.set().monoid().alphabet().random_letter();
  letter_t b = exp.set().monoid().alphabet().random_letter();

  krat_t a_e = monoid_elt_t(b);
  exp = monoid_elt_t(a);
  exp = (a_e + exp).star();
  exp = exp * a_e * exp;
  vcsn::tools::GenRandomAutomata<Auto> gen(time(0));
  Auto	au = gen.empty();
  glushkov(au, exp.value());

  return true;
}

#endif // GLUSHKOV_TEST_HH
