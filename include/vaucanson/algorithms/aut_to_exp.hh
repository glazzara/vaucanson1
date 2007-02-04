// aut_to_exp.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_AUT_TO_EXP_HH
# define VCSN_ALGORITHMS_AUT_TO_EXP_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   aut_to_exp.hh
 * @author Yann Régis-Gianas <yann@lrde.epita.fr>
 * @date   Tue Jun 24 19:21:17 2003
 *
 * @brief  This file provides converter from automaton to expression.
 *
 * @see aut_to_exp()
 */
/** @} */

// INTERFACE: Exp aut_to_exp(const GenAutomaton& a) { return vcsn::aut_to_exp(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Returns a series which describes the language of the automaton.
   *
   * This algorithm works on every kind of series. However, if, during
   * the computation,  it must take  the star of  it, it can  fail. By
   * passing  a "generalized"  automaton,  that is  an automaton  with
   * rational  expression as  label,  you  will be  sure  to have  the
   * algorithm succeed since we can always take the star of a rational
   * expression.
   *
   * @param a The automaton to convert.
   *
   * @return A rational series that describes the language of the automaton.
   * @see generalized()
   */
  template<typename A, typename T>
  typename Element<A, T>::series_set_elt_t
  aut_to_exp(const Element<A, T>& a);

  /**
   * Returns a series which describes the language of the automaton.
   *
   * This algorithm works on every kind of series. However, if, during
   * the computation,  it must take  the star of  it, it can  fail. By
   * passing  a "generalized"  automaton,  that is  an automaton  with
   * rational  expression as  label,  you  will be  sure  to have  the
   * algorithm succeed since we can always take the star of a rational
   * expression.
   *
   * @param a The automaton to work on.
   * @param c An object-function that returns the next state to remove
   *          from the current state and the automaton.
   *
   * @return A rational series that describes the language of the automaton.
   * @see generalized()
   */
  template<typename A, typename T, typename Chooser_>
  typename Element<A, T>::series_set_elt_t
  aut_to_exp(const Element<A, T>& a, const Chooser_& c);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/aut_to_exp.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_AUT_TO_EXP_HH
