// krat_exp_constant_term_test.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef TEST_DERIVATIONS_COMMON_HH
# define TEST_DERIVATIONS_COMMON_HH

template <class Derivation,
	  class Expr,
	  class Letter>
inline
bool test_derivate(const Expr& specimen,
		   const Letter& l,
		   const Expr& expected)
{
  Derivation d(specimen, l);
  
  if (d.is_defined() && (d.get_result() == expected))
    return true;
  else
    {
      std::cerr << "TEST FAILED: derivation of \"" << specimen <<
	"\" with letter '" << l << "' does not give \"" << expected << "\"." <<
	std::endl;
      return false;
    }
}

# define TEST_DERIVATE(Count, SuccessCount, Exp, Ltr, Expected)	\
{								\
  if (test_derivate<derivation_t>(Exp, Ltr, Expected))		\
    SuccessCount++;						\
  Count++;							\
}

# define TEST_DERIVATION_TYPEDEF_DECS(Expr, Derivation)			\
  typedef Expr					krat_exp_t;		\
  typedef typename krat_exp_t::value_t		kexp_t;			\
  typedef typename kexp_t::weight_value_t	kexp_weight_value_t;	\
  typedef typename kexp_t::monoid_value_t	kexp_monoid_value_t;	\
  typedef typename krat_exp_t::monoid_elt_t	monoid_elt_t;		\
  typedef typename monoid_elt_t::set_t		monoid_t;		\
  typedef typename krat_exp_t::weight_t		weight_t;		\
  typedef typename weight_t::set_t		weights_t;		\
  typedef typename krat_exp_t::set_t		series_t;		\
  typedef typename monoid_t::letter_t		letter_t;		\
  typedef typename monoid_t::alphabet_t		alphabet_t;		\
  typedef Derivation				derivation_t;

# define TEST_DERIVATION_USUAL_DECS(Alphabet, A, B, Monoid, Semiring, Series) \
  alphabet_t Alphabet;				\
  letter_t A = Alphabet.random_letter();	\
  letter_t B;					\
  do						\
    B = Alphabet.random_letter();		\
  while (A == B);				\
  Alphabet.insert(A);				\
  Alphabet.insert(B);				\
  monoid_t Monoid(Alphabet);			\
  weights_t Semiring;				\
  series_t Series(Semiring, Monoid);

#endif // ! TEST_DERIVATIONS_COMMON_HH
