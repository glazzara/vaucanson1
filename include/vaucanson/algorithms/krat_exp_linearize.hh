// krat_exp_linearize.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_KRAT_EXP_LINEARIZE_HH
# define VCSN_ALGORITHMS_KRAT_EXP_LINEARIZE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file krat_exp_linearize.hh
 *
 * Declarations for the linearize() algorithm.
 *
 * @see linearize()
 */
/** @} */

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/implementation/series/series.hh>
# include <vaucanson/algebra/implementation/alphabets/alphabets.hh>
# include <vaucanson/algebra/implementation/monoid/free_monoid.hh>
# include <vaucanson/algebra/implementation/letter/couple_letter.hh>
# include <vaucanson/misc/char_traits.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>

# include <utility>

namespace vcsn {

/** @addtogroup algorithms *//** @{ */

// The following line is a potential INTERFACE lines which has been disabled because of the LinExp pseudo-type.
// Interface: LinExp linearize(const Exp& e) { return vcsn::linearize(e); }

  /// The types of a linearized expression
  template <typename S, typename T>
  struct linearize_element
  {
    // Get types which are useful to build the new type
    typedef typename T::semiring_elt_value_t	orig_semiring_elt_value_t;
    typedef typename S::semiring_t		orig_semiring_t;
    typedef typename S::monoid_t		orig_monoid_t;
    typedef typename orig_monoid_t::letter_t	orig_letter_t;

    // Build it!
    typedef int					index_t;
    typedef std::pair<orig_letter_t, index_t>	letter_t;
    // FIXME: Here, we want X<letter_t> where X is the type of the alphabet
    // FIXME: concept. See next FIXME.
    typedef algebra::AlphabetSet<letter_t>		alphabets_t;
    typedef std::set<letter_t>				alphabet_impl_t;
    typedef Element<alphabets_t, alphabet_impl_t>	alphabet_t;
    // FIXME: in fact, here we want X<alphabet_t> where X is the type of
    // FIXME: the monoid concept. For the moment, we just have FreeMonoid, so
    // FIXME: it is not important but in the future, we will have to introduce
    // FIXME: a convenient way of substituting types parameters ...
    typedef algebra::FreeMonoid<alphabet_t>		monoid_t;
    // FIXME: same remark here.
    typedef algebra::Series<orig_semiring_t, monoid_t>	series_set_t;
    typedef std::basic_string<letter_t, misc::char_traits<letter_t> >
							monoid_elt_value_t;
    typedef rat::exp<monoid_elt_value_t, orig_semiring_elt_value_t>
							series_set_elt_value_t;
    // And the resulting type:
    typedef Element<series_set_t, series_set_elt_value_t>
							element_t;
  };

  /// The linearization of the krat expression.
  template <class Series, class T>
  typename linearize_element<Series, T>::element_t
  linearize(const Element<Series, T>& exp);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/krat_exp_linearize.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_KRAT_EXP_LINEARIZE_HH
