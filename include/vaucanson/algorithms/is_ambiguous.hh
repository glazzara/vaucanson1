// is_ambiguous.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008 The Vaucanson Group.
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

#ifndef VCSN_ALGORITHMS_IS_AMBIGUOUS_HH
# define VCSN_ALGORITHMS_IS_AMBIGUOUS_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file   is_ambiguous.hh
 *
 * Test for ambiguity.
 *
 * @author Matthieu Varin <matt@lrde.epita.fr>
 *
 * @see is_ambiguous()
 */
/** @} */

// INTERFACE: bool is_ambiguous(const Automaton& a) { return vcsn::is_ambiguous(*a); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */
  /**
   * Test the ambiguity of automaton.
   * @note A trim automaton @c A is ambiguous if there exists a word
   * @c f which is the label of two distinct accepting paths @c A.
   *
   * @param aut The automaton to test.
   *
   * @return true if the automaton is ambiguous.
   */
  template<typename A, typename AI>
  bool
  is_ambiguous(const Element<A, AI>& aut);

  /** @} */

} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/is_ambiguous.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_IS_AMBIGUOUS_HH
