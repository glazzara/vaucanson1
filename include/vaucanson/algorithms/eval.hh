// eval.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_EVAL_HH
# define VCSN_ALGORITHMS_EVAL_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   eval.hh
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 17:50:38 2003
 *
 * @brief  This file provides the evaluation of a word w.r.t an automaton.
 *
 * @see eval()
 */
/** @} */

// INTERFACE: int eval(const Automaton& a, const std::string& s) { return vcsn::eval(*a, Series::monoid_elt_t((*a).structure().series().monoid(), s)).value(); }
// INTERFACE: int eval(const GenAutomaton& a, const std::string& s) { return vcsn::eval(*a, Series::monoid_elt_t((*a).structure().series().monoid(), s)).value(); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Return the image of a word by an automaton.
   *
   * eval(a, w) returns a series that  is the image of the word 'w' in
   * the automaton.  This version of  computation is the  most general
   * one : it works on every types of automaton, deterministic or not.
   * Yet, the automaton must be realtime.
   */
  template<typename A, typename AI, typename W>
  typename Element<A, AI>::semiring_elt_t
  eval(const Element<A, AI>& a, const W& word);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/eval.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_EVAL_HH
