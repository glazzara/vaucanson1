// automata.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2008 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_HXX
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_HXX

#include <vaucanson/automata/concept/automata_base.hh>
#include <vaucanson/misc/unique.hh>

namespace vcsn {

  template <class Series>
  Automata<Series>::Automata(const series_set_t& s):
    SetSlot<Series>(s)
  {}

  template <class Series>
  const Series&
  Automata<Series>::series() const
  {
    return this->_structure_get();
  }

  template <class Series>
  bool
  operator==(const Automata<Series>& lhs,
	     const Automata<Series>& rhs)
  {
    return & lhs.series() == & rhs.series();
  }

# define PROJECTION_TRAITS \
    projection_traits<Automata<S>, T>

  template <typename S, typename T>
  inline typename PROJECTION_TRAITS::first_projection_t
  PROJECTION_TRAITS::
  first_projection(const PROJECTION_TRAITS::automaton_t& aut)
  {
    // We can not project if the type does not support it.
    static_assertion_(not (misc::static_eq<first_projection_t,
			   undefined_type>::value), need_first_projection)

    semiring_t semiring = aut.series().semiring();
    alphabet_t A = aut.series().monoid().alphabet();

    // Project the alphabet.
    typename alphabet_traits_t::first_projection_t B =
	alphabet_traits_t::first_projection(A);

    // Construct the monoid.
    typename word_traits_t::first_monoid_t freemonoid(B);

    // Construct the series.
    typename first_projection_t::series_set_t series(semiring, freemonoid);

    // Construct the automaton structure.
    typename first_projection_t::set_t set_t(series);

    return first_projection_t(set_t);
  }

  template <typename S, typename T>
  inline typename PROJECTION_TRAITS::second_projection_t
  PROJECTION_TRAITS::
  second_projection(const PROJECTION_TRAITS::automaton_t& aut)
  {
    // We can not project if the type does not support it.
    static_assertion_(not (misc::static_eq<second_projection_t,
			   undefined_type>::value), need_second_projection)

    semiring_t semiring = aut.series().semiring();
    alphabet_t A = aut.series().monoid().alphabet();

    // Project the alphabet.
    typename alphabet_traits_t::second_projection_t B =
	alphabet_traits_t::second_projection(A);

    // Construct the monoid.
    typename word_traits_t::second_monoid_t freemonoid(B);

    // Construct the series.
    typename second_projection_t::series_set_t series(semiring, freemonoid);

    // Construct the automaton structure.
    typename second_projection_t::set_t set_t(series);

    return second_projection_t(set_t);
  }

  template <typename S, typename T>
  inline typename PROJECTION_TRAITS::series_first_projection_t
  PROJECTION_TRAITS::
  series_first_projection(const PROJECTION_TRAITS::first_series_t& series,
			  const PROJECTION_TRAITS::series_set_elt_t& ss)
  {
    // We can not project if the type does not support it.
    static_assertion_(not (misc::static_eq<first_projection_t,
			   undefined_type>::value), need_first_projection)

    series_first_projection_t ret(series);

    for_all_const_(series_set_elt_t::support_t, s, ss.supp())
      ret.assoc(word_traits_t::first_projection(*s),
		ss.get(*s));

    return ret;
  }

  template <typename S, typename T>
  inline typename PROJECTION_TRAITS::series_second_projection_t
  PROJECTION_TRAITS::
  series_second_projection(const PROJECTION_TRAITS::second_series_t& series,
			   const PROJECTION_TRAITS::series_set_elt_t& ss)
  {
    // We can not project if the type does not support it.
    static_assertion_(not (misc::static_eq<second_projection_t,
			   undefined_type>::value), need_second_projection)

    series_second_projection_t ret(series);

    for_all_const_(series_set_elt_t::support_t, s, ss.supp())
      ret.assoc(word_traits_t::second_projection(*s),
		ss.get(*s));

    return ret;
  }

# undef PROJECTION_TRAITS

} // ! vcsn

#endif // ! VCSN_AUTOMATA_CONCEPT_AUTOMATA_HXX
