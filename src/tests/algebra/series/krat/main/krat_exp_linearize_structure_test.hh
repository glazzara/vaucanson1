// krat_exp_linearize_structure_test.hh: this file is part of the Vaucanson
// project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_LINEARIZE_STRUCTURE_TEST_HH
# define VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_LINEARIZE_STRUCTURE_TEST_HH

# include <vaucanson/algorithms/krat_exp_linearize.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/tools/gen_random.hh>

/**
 * @file  krat_exp_linearize_structure_test.hh
 *
 * Checks the structure of a linearized expression.
 *
 * This test  redefines the <<  operator in the utility  namespace, in
 * order to print linearized expressions without their numeration.  So
 * linearized and original expressions should be printed the same way.
 */

namespace utility
{

  template <typename U>
  std::ostream&
  operator << (std::ostream& o, const std::pair<U, int>& p)
  {
    return o << p.first;
  }

  template <typename U, class Traits, class Allocator>
  std::ostream& operator<<(std::ostream& o,
			   const std::basic_string<std::pair<U, int>,
			                           Traits,
			                           Allocator>& s)
  {
    typename
    std::basic_string<std::pair<U, int>, Traits, Allocator>::const_iterator i;
    for (i = s.begin(); i != s.end(); ++i)
      o << i->first;
    return o;
  }

}

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

  tests::Tester t(tg.verbose());
  srand(time(0));

  alphabet_t	alphabet;
  letter_t	a = alphabet.random_letter();
  letter_t	b = alphabet.random_letter();
  alphabet.insert(a);
  alphabet.insert(b);
  monoid_t	monoid (alphabet);
  semiring_t	semiring;
  series_set_t	s (semiring, monoid);

  const int	nb_tests = 200;
  int		nb_succs = 0;

  for (int n = 0; n < nb_tests; ++n)
    {
      krat_exp_t	exp = s.choose(SELECT(kexp_t));
      out_krat_exp_t	lin = linearize(exp);
      std::stringstream	exp_str;
      std::stringstream	lin_str;

      exp_str << exp;
      lin_str << lin;

      if (exp_str.str() != lin_str.str())
	std::cerr << "TEST:" << exp << "!=" << lin << std::endl;
      else
	++nb_succs;
    }

  std::string rate;
  SUCCESS_RATE(rate, nb_succs, nb_tests);
  TEST(t, "Structure of linearize(exp) is the same as exp. " + rate,
       nb_tests == nb_succs);

  return t.all_passed();
}

#endif // VCSN_TESTS_ALGEBRA_SERIES_KRAT_MAIN_KRAT_EXP_LINEARIZE_STRUCTURE_TEST_HH
