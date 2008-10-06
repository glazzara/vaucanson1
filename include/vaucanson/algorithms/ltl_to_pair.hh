// ltl_to_pair.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_LTL_TO_PAIR_HH
# define VCSN_ALGORITHMS_LTL_TO_PAIR_HH

# include <map>
# include <set>
# include <utility>
# include <string>

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/transducer.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/algebra/implementation/alphabets/alphabet_set.hh>
# include <vaucanson/algebra/implementation/free_monoid/words.hh>

// Needed for the operator<< on pairs
# include <vaucanson/algebra/implementation/letter/couple_letter.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file   ltl_to_pair.hh
 *
 * This file provides a transformation function that computes
 * the pair letter automaton of an FMP automaton.
 *
 * @author Jerome Galtier <jerome.galtier@lrde.epita.fr>
 *
 * @see ltl_to_pair()
 */
/** @} */

// INTERFACE: void ltl_to_pair(const Automaton& a, LtlToPair& b) { return vcsn::ltl_to_pair(*a, *b); }
// INTERFACE: LtlToPair ltl_to_pair(const Automaton& a) { return vcsn::ltl_to_pair(*a); }

namespace vcsn
{
  /** @addtogroup algorithms *//** @{ */

  /// @name Letterized FMP automaton to pair letter automaton algorithm.
  ///@{
  /// Compute the pair letter automaton associated to a letterized FMP
  /// automaton.

  // Helper to mute an FMP into its corresponding pair automaton.
  template <typename S, typename T>
  struct mute_ltl_to_pair
  {
    // The automaton type.
    typedef Element<S, T> automaton_t;

    // The free monoid product type.
    typedef typename automaton_t::monoid_elt_t::set_t monoid_set_elt_t;

    // The semiring type.
    typedef typename automaton_t::semiring_t semiring_t;

    // The first alphabet type.
    typedef typename monoid_set_elt_t::
	first_monoid_t::alphabet_t first_alphabet_t;

    // The second alphabet type.
    typedef typename monoid_set_elt_t::
	second_monoid_t::alphabet_t second_alphabet_t;

    // The first letter type.
    typedef typename first_alphabet_t::set_t::letter_t first_letter_t;

    // The second letter type.
    typedef typename second_alphabet_t::set_t::letter_t second_letter_t;

    // The return letter type.
    typedef std::pair<first_letter_t, second_letter_t> ret_letter_t;

    // The return alphabet type.

    // 1 - structure
    typedef typename algebra::AlphabetSet<ret_letter_t> ret_alphabet_set_t;

    // 2 - implementation
    typedef std::set<ret_letter_t> ret_alphabet_impl_t;

    // 3 - element
    typedef Element<ret_alphabet_set_t, ret_alphabet_impl_t>
	ret_alphabet_t;

    typedef algebra::FreeMonoid<ret_alphabet_t> ret_monoid_t;

    typedef Element<ret_monoid_t, std::basic_string<ret_letter_t> >
	ret_monoid_elt_t;

    // Helper to calculate the Cartesian product of two
    // alphabets: E = {(a,x)| a \in A, x \in B}.
    static ret_alphabet_t
    cartesian_product(const first_alphabet_t& A,
		      const second_alphabet_t& B);

    // The muted automaton type.

    // 1 - structure
    typedef typename algebra::
	mute_series_traits<typename automaton_t::series_set_t,
			   typename automaton_t::semiring_t,
			   algebra::FreeMonoid<ret_alphabet_t> >::ret
	ret_series_set_t;
    typedef Automata<ret_series_set_t> ret_set_t;

    // 2 - implementation
    typedef typename mute_graph_impl_monoid_traits<typename automaton_t::
	value_t, ret_monoid_elt_t>::ret ret_impl_t;

    // 3 - element
    typedef Element<ret_set_t, ret_impl_t> ret;

    // Automaton "makers".
    static ret
    make_automaton(const ret_alphabet_t&);

    static ret
    make_automaton(const automaton_t&);

    // Series converter.
    static typename ret::series_set_elt_t
    series_convert(const ret_series_set_t&,
		   const typename automaton_t::series_set_elt_t&);
  };

  template <typename S, typename T>
  void
  ltl_to_pair(const Element<S, T>& ltl,
	      typename mute_ltl_to_pair<S, T>::ret& res);

  template <typename S, typename T>
  typename mute_ltl_to_pair<S, T>::ret
  ltl_to_pair(const Element<S, T>& ltl);

  ///@}

  /** @} */

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/ltl_to_pair.hxx>
# endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_LTL_TO_PAIR_HH
