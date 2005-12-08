// sub_normalize.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_SUB_NORMALIZE_HH
# define VCSN_ALGORITHMS_SUB_NORMALIZE_HH

/**
 * @file sub-normalize.hh
 *
 * Sub-normalization algorithm for FMP transducers.
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */

# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/automata/concept/copy.hh>
# include <vaucanson/algorithms/cut_up.hh>
# include <vector>

namespace vcsn
{
  /**
   * @brief Sub-normalize a FMP transducer.
   *
   * @arg a	Input automaton.
   * @return	Sub-normalized automaton.
   *
   */
  template <class S, class T>
  Element<S, T>
  sub_normalize(const Element<S, T>& a);

  /**
   * @brief Sub-normalize a FMP transducer.
   *
   * @arg a	Input automaton.
   * @arg res	Output automaton.
   *
   */
  template <class S, class T1, class T2>
  void
  sub_normalize(const Element<S, T1>& a, Element<S, T2>& res);

  /**
   * @brief Check if a FMP transducer is sub-normalized.
   *
   * @arg a	Input automaton.
   * @return	boolean.
   *
   */
  template <class S, class T>
  bool is_sub_normalized(const Element<S, T>& a);

} // ! vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/sub_normalize.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_SUB_NORMALIZE_HH
