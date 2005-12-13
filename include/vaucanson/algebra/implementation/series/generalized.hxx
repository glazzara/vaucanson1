// generalized.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_GENERALIZED_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_GENERALIZED_HXX

# include <vaucanson/misc/selectors.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/implementation/series/polynoms.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>

namespace vcsn {

    /*----------------------.
    | Generalized converter |
    `----------------------*/
    template<typename W, typename M, typename Tm, typename Tw>
    rat::exp<Tm, Tw> op_convert(const algebra::Series<W, M>& s1,
				SELECTOR2(rat::exp<Tm, Tw>),
				const algebra::Series<W, M>& s2,
				const algebra::polynom<Tm, Tw>& p_value)
    {
      precondition(& s1 == & s2);

      typedef rat::exp<Tm, Tw> kexp_t;
      kexp_t	exp;

      if (p_value == identity_value(SELECT2(algebra::Series<W, M>),
				    SELECT2(algebra::polynom<Tm, Tw>)))
	return kexp_t::one();

      if (p_value == zero_value(SELECT2(algebra::Series<W, M>),
				SELECT2(algebra::polynom<Tm, Tw>)))
	return kexp_t::zero();

      for (typename algebra::polynom<Tm, Tw>::const_iterator p = p_value.begin();
	   p != p_value.end();
	   ++p)
	if (exp == kexp_t::zero())
	  exp = (*p).second *  kexp_t::constant((*p).first);
	else
	  exp += (*p).second *  kexp_t::constant((*p).first);
      return exp;
    }

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_GENERALIZED_HXX
