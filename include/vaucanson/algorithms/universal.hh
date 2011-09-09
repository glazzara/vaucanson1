// universal.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_UNIVERSAL_HH
# define VCSN_ALGORITHMS_UNIVERSAL_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   universal.hh
 *
 * Universal automaton for Boolean rational languages.
 *
 * @see universal()
 */
/** @} */

// INTERFACE: Automaton universal(const Automaton& a) { return vcsn::universal(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// @name Universal algorithm
  //@{
  /**
   * Build a universal automaton from a Boolean automaton.
   *
   * This function build the universal automaton of a rational language
   * using the intersection of sets.
   * For a complete definition of the universal automaton, see
   * "The universal automaton", (S.Lombardy and J.Sakarovitch)
   * Logic and Automata, Texts in Logic and Games, 2
   * (Amsterdam University Press, 2008), 457-504.
   *
   * @param a The Boolean automaton recognizing the language.
   *
   * @pre @a a must be a Boolean automaton.
   * @pre @a a must be a realtime automaton.
   *
   * @return A new automaton which is universal @a a.
   */
  template<typename A, typename AI>
  Element<A, AI>
  universal(const Element<A, AI>& a);
  //@}

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/universal.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_UNIVERSAL_HH
