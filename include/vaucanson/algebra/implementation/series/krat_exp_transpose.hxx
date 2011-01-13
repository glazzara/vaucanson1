// krat_exp_transpose.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_TRANSPOSE_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_TRANSPOSE_HXX

# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_pattern.hh>


namespace vcsn {

  namespace algebra {

    template <class Series, class T, class Dispatch>
    struct KRatExpTranspose : algebra::KRatExpIdentity<
      KRatExpTranspose<Series, T, Dispatch>,
      Series,
      T,
      Dispatch
      >
    {
      typedef KRatExpTranspose<Series, T, Dispatch>	self_t;
      typedef Element<Series, T>			return_type;
      typedef typename Element<Series, T>::semiring_elt_t semiring_elt_t;
      typedef typename semiring_elt_t::value_t		semiring_elt_value_t;
      typedef typename Element<Series, T>::monoid_elt_t	monoid_elt_t;
      typedef typename monoid_elt_t::value_t		monoid_elt_value_t;
      typedef typename monoid_elt_t::set_t		monoid_t;
      typedef typename monoid_t::alphabet_t		alphabet_t;
      typedef typename alphabet_t::letter_t		letter_t;
      INHERIT_CONSTRUCTORS(self_t, T, semiring_elt_t, Dispatch);

      KRatExpTranspose(const Element<Series, T>& exp) :
	KRatExpIdentity<KRatExpTranspose<Series, T, Dispatch>,
      			Series,
      			T,
      			Dispatch
      			>(exp)
      {}

      MATCH__(Product, lhs, rhs)
      {
	return this->match(rhs) * this->match(lhs);
      }
      END

      MATCH_(Constant, m)
      {
	monoid_elt_t melt (this->exp_.structure().monoid(), m);
	melt.mirror();
	return Element<Series, T> (this->exp_.structure(), melt);
      }
      END

    };


  } // algebra

}

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_TRANSPOSE_HXX
