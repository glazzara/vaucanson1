// sub_normalize.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_SUB_NORMALIZE_HH
# define VCSN_ALGORITHMS_SUB_NORMALIZE_HH


/** @addtogroup algorithms *//** @{ */
/**
 * @file sub_normalize.hh
 *
 * Sub-normalization algorithm for FMP transducers.
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 *
 * @see sub_normalize()
 * @see is_sub_normalize()
 *
 */
/** @} */

# include <vaucanson/algebra/concept/freemonoid_product.hh>
# include <vaucanson/automata/concept/copy.hh>
# include <vaucanson/algorithms/cut_up.hh>
# include <vector>

namespace vcsn
{

  /** @addtogroup algorithms *//** @{ */

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
   * @brief Sub-normalize a FMP transducer, in place version.
   *
   * @param a Input automaton.
   */
  template <class S, class T>
  void
  sub_normalize_here(Element<S, T>& a);


  /**
   * @brief Check if a FMP transducer is sub-normalized.
   *
   * @arg a	Input automaton.
   * @return	boolean.
   *
   */
  template <class S, class T>
  bool is_sub_normalized(const Element<S, T>& a);

  /** @} */

} // ! vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/sub_normalize.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_SUB_NORMALIZE_HH
