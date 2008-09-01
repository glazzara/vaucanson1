// cut_up.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_CUT_UP_HH
# define VCSN_ALGORITHMS_CUT_UP_HH

/**
 * @file cut_up.hh
 *
 * Cut-up algorithm.
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */

# include <vaucanson/automata/concept/copy.hh>
# include <vaucanson/algebra/implementation/series/rat/nodes.hh>
# include <vaucanson/algebra/implementation/series/generalized.hh>
# include <vaucanson/algorithms/standard_of.hh>

namespace vcsn
{

  /**
   * @brief Check if labels are series with one element.
   *
   * @arg a	Input automaton.
   * @return	is cut-up.
   *
   */
  template <typename A, typename AI>
  bool is_cut_up(const Element<A, AI>& a);


  /**
   * @brief Transform an automaton labeled with series to an automaton
   * where all labels are series with one and only one element.
   *
   * @note No cut-up work is done on input and output transitions.
   *
   * Works on all automata and transducers labeled with polynomial series,
   * and on automata labeled with rational series.
   *
   * @arg a	Input automaton.
   * @return	Output automaton.
   *
   */
  template <typename A, typename AI>
  Element<A, AI>
  cut_up(const Element<A, AI>& a);


  /**
   * @brief Transform an automaton labeled with series to an automaton
   * where all labels are series with one and only one element.
   *
   * @note No cut-up work is done on input and output transitions.
   *
   * Works on all automata and transducers labeled with polynomial series,
   * and on automata labeled with rational series.
   *
   * @arg a	Input automaton.
   * @arg res	Output automaton.
   *
   */
  template <typename A, typename AI>
  void
  cut_up(const Element<A, AI>& a, Element<A, AI>& res);


  /**
   * @brief Transform an automaton labeled with series to an automaton
   * where all labels are series with one and only one element.
   *
   * @note No cut-up work is done on input and output transitions.
   *
   * Works on all automata and transducers labeled with polynomial series,
   * and on automata labeled with rational series.
   *
   * @arg a	Input automaton.
   *
   */
  template <typename A, typename AI>
  void
  cut_up_here(Element<A, AI>& a);


} // ! vcsn


# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/cut_up.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_CUT_UP_HH
