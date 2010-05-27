// shortest.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008, 2009, 2010 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_SHORTEST_HH
# define VCSN_ALGORITHMS_SHORTEST_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file shortest.hh
 *
 * @brief Algorithms for enumeration of short words in a language.
 *
 * Algorithm shortest gives the smallest words for the military (or
 * shortlex) order.  Algorithm enumerates returns the list of all
 * accepted words shorter than a given length.
 *
 * @see shortest(), enumerate()
 */
/** @} */

// INTERFACE: Automaton::monoid_elt_t shortest(const Automaton& a) { return vcsn::shortest(*a); }
// INTERFACE: bool shortest(const Automaton& a, Automaton::monoid_elt_t& w) { return vcsn::shortest(*a, w); }

// INTERFACE: void enumerate(const Automaton& a, unsigned ml, std::list<Automaton::monoid_elt_t>& wl) { vcsn::enumerate(*a, ml, wl); }

#include <list>

namespace vcsn
{
/** @addtogroup algorithms */  /** @{ */

  /**
   * @brief Return the smallest accepted word.
   *
   * This functions returns the smallest accepted word.  A
   * breath-first lexicographically algorithm is performed, and to
   * each met state is associated the smallest word that leads to this
   * state. As soon as a final state is reached, the function returns
   * the corresponding word.  If the language of the automaton is
   * empty, the return value is meaningless (due to the current
   * implementation, it is the default value i.e. the empty word).
   *
   * @param autom The input automaton.
   * @pre @a autom must be a realtime automaton
   */
  template<typename Automaton>
  typename Automaton::monoid_elt_t
  shortest(const Automaton& autom);

  /**
   * @brief Compute the smallest accepted word.
   *
   * This functions returns the smallest accepted word.  A
   * breath-first lexicographically algorithm is performed, and to
   * each met state is associated the smallest word that leads to this
   * state. As soon as a final state is reached, the function returns
   * the corresponding word.  The function return true except if the
   * language of the automaton is empty.
   *
   * @param autom The input automaton.
   * @param word The word which stores the smallest accepted word.
   * @pre @a autom must be a realtime automaton
   */
  template<typename Automaton, typename MonoidElt>
  bool
  shortest(const Automaton& autom, MonoidElt& word);

  /**
   * @brief Compute the list of short accepted words.
   *
   * This functions computes the list of words shorter than max_length.
   * The list is sorted w.r.t. the military (shortlex) order.
   *
   * At step k, the set of states accessible by words of length k is
   * computed; for each state the list of these words is stored.
   * After step max_length, all the words that make final states are
   * collected, sorted, and potential redundancy is suppressed.
   *
   * @pre @a autom must be a realtime automaton
   * @param autom The input automaton.
   * @param max_length The maximal length for words.
   * @param the list to fill with accepted words shortest than max_length.
   */
  template<typename Automaton, typename MonoidElt, typename Alloc>
  void
  enumerate(const Automaton& autom, unsigned max_length,
	    std::list<MonoidElt, Alloc>& word_list);

  /** @} */

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/shortest.hxx>
# endif // VCSN_USE_INTERFACE_ONLY
#endif // ! VCSN_ALGORITHMS_SHORTEST_HH
