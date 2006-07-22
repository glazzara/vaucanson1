// composition_cover.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_COMPOSITION_COVER_HXX
# define VCSN_ALGORITHMS_COMPOSITION_COVER_HXX

/**
 * @file   composition_cover.hxx
 * @author Guillaume Leroi
 * @date   Sat Jul 22 18:03:02 2006
 *
 * @brief  Composition (co-)cover algorithms for normalized and sub-normalized
 * transducers seen as automaton over a free monoid.
 *
 *
 */

# include <vaucanson/algorithms/internal/outsplitting.hh>
# include <vaucanson/algorithms/composition_cover.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/automata/concept/automata.hh>


namespace vcsn {

  template <typename S, typename M1, typename M2, typename Auto_t>
  void
  do_composition_cover (const AutomataBase<S>&,
			const algebra::FreeMonoidProduct<M1, M2>&,
			const Auto_t& fmp,
			Auto_t& ret)
  {
    AUTOMATON_TYPES(Auto_t);

    ret = splitting::outsplitting (fmp);
  }


  template <typename S, typename M1, typename M2, typename Auto_t>
  void
  do_composition_co_cover (const AutomataBase<S>&,
			   const algebra::FreeMonoidProduct<M1, M2>&,
			   const Auto_t& fmp,
			   Auto_t& ret)
  {
    AUTOMATON_TYPES(Auto_t);

    ret = splitting::insplitting (fmp);
  }



  /// Facade for composition cover

  template <typename S, typename T>
  Element<S, T>
  composition_cover (const Element<S, T>& fmp)
  {
    typedef Element<S, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    auto_t ret (fmp.structure());

    do_composition_cover (fmp.structure(),
			  fmp.structure().series().monoid(),
			  fmp,
			  ret);
    return ret;
  }


  template <typename S, typename T>
  void
  composition_cover (const Element<S, T>& fmp,
		     Element<S, T>& ret)
  {
    typedef Element<S, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    for_all_states (s, ret)
      ret.del_states (*s);
    do_composition_cover (fmp.structure(),
			  fmp.structure().series().monoid(),
			  fmp,
			  ret);
  }


  /// Facade for composition co-cover

  template <typename S, typename T>
  Element<S, T>
  composition_co_cover (const Element<S, T>& fmp)
  {
    typedef Element<S, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    automaton_t ret(fmp.structure());

    do_composition_co_cover (fmp.structure(),
			     fmp.structure().series().monoid(),
			     fmp,
			     ret);
    return ret;
  }


  template <typename S, typename T>
  void
  composition_co_cover (const Element<S, T>& fmp,
			Element<S, T>& ret)
  {
    typedef Element<S, T> auto_t;
    AUTOMATON_TYPES(auto_t);

    for_all_states (s, ret)
      ret.del_states (*s);
    do_composition_cover (fmp.structure(),
			  fmp.structure().series().monoid(),
			  fmp,
			  ret);
  }

}

#endif // ! VCSN_ALGORITHMS_COMPOSITION_COVER_HXX
