// determinize.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_DETERMINIZE_HH
# define VCSN_ALGORITHMS_DETERMINIZE_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   determinize.hh
 *
 * Boolean automata determinization.
 *
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 19:13:10 2003
 *
 * @see determinize()
 */
/** @} */

// INTERFACE: Automaton determinize(const Automaton& a) { return vcsn::determinize(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>

# include <map>
# include <set>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// @name Determinization algorithms
  //@{
  /**
   * Returns the determinized of a Boolean automaton.
   *
   * @param a The Boolean automaton to determinize.
   *
   * @return A fresh Boolean automaton that is the determinization of 'a'.
   */
  template<typename A, typename T>
  Element<A, T>
  determinize(const Element<A, T>& a);

  /**
   * Returns the determinized of a Boolean automaton.
   *
   * @param a The Boolean automaton to determinize.
   * @param m A map which will be augmented with the correspondance
   *          from one state of the resulting automaton to the set
   *          of states of the input automaton.
   *
   * @return A fresh Boolean automaton that is the determinization of 'a'.
   */
  template<typename A, typename T>
  Element<A, T>
  determinize(const Element<A, T>& a,
	      std::map<hstate_t, std::set<hstate_t> >&m);
  //@}

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/determinize.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_DETERMINIZE_HH
