// cut_up.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
# include <vaucanson/automata/implementation/generalized.hh>
# include <vaucanson/algebra/implementation/series/rat/nodes.hh>
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
  template <class S, class T>
  bool is_cut_up(const Element<S, T>& a);


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
  template <class S, class T>
  Element<S, T>
  cut_up(const Element<S, T>& a);


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
  template <class S, class T>
  void
  cut_up(const Element<S, T>& a, Element<S, T>& res);


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
  template <class S, class T>
  void
  cut_up_here(Element<S, T>& a);


} // ! vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/cut_up.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_CUT_UP_HH
