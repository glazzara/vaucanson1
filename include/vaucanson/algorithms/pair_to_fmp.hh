// pair_to_fmp.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_PAIR_TO_FMP_HH
# define VCSN_ALGORITHMS_PAIR_TO_FMP_HH

# include <map>
# include <utility>

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/algebra/implementation/alphabets/alphabet_set.hh>
# include <vaucanson/algebra/implementation/monoid/free_monoid.hh>

// Needed for op_rout(fmp)
# include <vaucanson/algebra/implementation/monoid/pair_str_words.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file   pair_to_fmp.hh
 *
 * This file provides a transformation function that computes
 * the FMP transducer of a pair letter automaton.
 *
 * @author Jerome Galtier <jerome.galtier@lrde.epita.fr>
 *
 * @see pair_to_fmp()
 */
/** @} */

// INTERFACE: void pair_to_fmp(const Automaton& a, PairToFMP& b) { return vcsn::pair_to_fmp(*a, *b); }
// INTERFACE: PairToFMP pair_to_fmp(const Automaton& a) { return vcsn::pair_to_fmp(*a); }

namespace vcsn
{
  /** @addtogroup algorithms *//** @{ */

  /// @name Pair letter automaton to FMP transducer algorithm.
  ///@{
  /// Compute the FMP transducer associated to a pair letter automaton.

  // Helper to mute a pair automaton into its corresponding FMP transducer.
  template <typename S, typename T>
  struct mute_pair_to_fmp
  {
    // The automaton type.
    typedef Element<S, T> automaton_t;

    // The monoid type.
    typedef typename automaton_t::monoid_elt_t monoid_elt_t;

    // The alphabet type.
    typedef typename monoid_elt_t::set_t::alphabet_t alphabet_t;

    // Alphabet traits.
    typedef algebra::alphabet_traits<typename alphabet_t::set_t,
	      typename alphabet_t::value_t> alphabet_traits_t;

    // Word traits.
    typedef algebra::word_traits<typename monoid_elt_t::set_t,
	      typename monoid_elt_t::value_t> word_traits_t;

    // The first computed monoid.
    typedef typename word_traits_t::first_monoid_t first_monoid_t;

    // The second computed monoid.
    typedef typename word_traits_t::second_monoid_t second_monoid_t;

    // The semiring type.
    typedef typename automaton_t::semiring_t semiring_t;

    // The first alphabet type.
    typedef typename first_monoid_t::alphabet_t ret_first_alphabet_t;

    // The second alphabet type.
    typedef typename second_monoid_t::alphabet_t ret_second_alphabet_t;

    // The free monoid product type.

    // 1 - structure
    typedef algebra::FreeMonoidProduct<first_monoid_t,
				       second_monoid_t> ret_monoid_t;

    // 2 - implementation
    typedef std::pair<typename word_traits_t::first_projection_t::value_t,
		      typename word_traits_t::second_projection_t::value_t>
	ret_word_impl_t;

    // 3 - element
    typedef Element<ret_monoid_t, ret_word_impl_t> ret_monoid_elt_t;

    // The muted automaton type.

    // 1 - structure
    typedef typename algebra::
	mute_series_traits<typename automaton_t::series_set_t,
			   typename automaton_t::semiring_t,
			   ret_monoid_t>::ret
	ret_series_set_t;
    typedef Automata<ret_series_set_t> ret_set_t;

    // 2 - implementation
    typedef typename mute_graph_impl_monoid_traits<typename automaton_t::
	value_t, ret_word_impl_t, undefined_type>::ret ret_impl_t;

    // 3 - element
    typedef Element<ret_set_t, ret_impl_t> ret;

    // Automaton "makers".
    static ret
    make_automaton(const ret_first_alphabet_t&, const ret_second_alphabet_t&);

    static ret
    make_automaton(const automaton_t&);

    // Series converter.
    static typename ret::series_set_elt_t
    series_convert(const ret_series_set_t&,
		   const typename automaton_t::series_set_elt_t&);
  };

  template <typename S, typename T>
  void
  pair_to_fmp(const Element<S, T>& aut,
	      typename mute_pair_to_fmp<S, T>::ret& res);

  template <typename S, typename T>
  typename mute_pair_to_fmp<S, T>::ret
  pair_to_fmp(const Element<S, T>& aut);

  ///@}

  /** @} */

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/pair_to_fmp.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_PAIR_TO_FMP_HH
