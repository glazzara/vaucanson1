// normalized_composition.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_NORMALIZED_COMPOSITION_HH
# define VCSN_ALGORITHMS_NORMALIZED_COMPOSITION_HH

# include <vaucanson/automata/concept/automata_base.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file normalized_composition.hh
 *
 * @brief Composition for normalized and sub-normalized transducers
 * seen as automata over a free monoid product.
 *
 * @author Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
 *
 * @see compose()
 * @see u_compose()
 */
/** @} */

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */


 /**
   * Composition for weighted normalized and sub-normalized
   * transducers, seen as automata over a free monoid product.
   *
   * @param  lhs The left hand side transducer.
   * @param  rhs The right hand side transducer.
   * @param  ret The result transducer.
   *
   */
  template <typename S, typename T>
  void
  compose(const Element<S, T>& lhs,
	  const Element<S, T>& rhs,
	  Element<S, T>& ret);



  /**
   * Composition for weighted normalized and sub-normalized
   * transducers, seen as automata over a free monoid product.
   *
   * @param  lhs The left hand side transducer.
   * @param  rhs The right hand side transducer.
   *
   */
  template <typename S, typename T>
  Element<S, T>
  compose(const Element<S, T>& lhs,
	  const Element<S, T>& rhs);


  /**
   * Unambiguous composition for weighted normalized and sub-normalized
   * transducers, seen as automata over a free monoid product.
   *
   * @param  lhs The left hand side transducer.
   * @param  rhs The right hand side transducer.
   * @param  ret The result transducer.
   *
   */
  template <typename S, typename T>
  void
  u_compose(const Element<S, T>& lhs,
	    const Element<S, T>& rhs,
	    Element<S, T>& ret);

  /**
   * Unambiguous composition for weighted normalized and sub-normalized
   * transducers, seen as automata over a free monoid product.
   *
   * @param  lhs The left hand side transducer.
   * @param  rhs The right hand side transducer.
   *
   */
  template <typename S, typename T>
  Element<S, T>
  u_compose(const Element<S, T>& lhs,
	    const Element<S, T>& rhs);

  /** @} */

} // End of namespace vcsn.

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/normalized_composition.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_NORMALIZED_COMPOSITION_HH
