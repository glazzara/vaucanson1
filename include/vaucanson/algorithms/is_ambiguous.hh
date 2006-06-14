// is_ambiguous.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */
  /**
   * Test the ambiguity of automaton.
   * @note A trimmed automaton @c A is ambiguous if for a word @c f of @c L(A) there
   * is not an unique path labeled by @c f in @c A.
   *
   * @param aut The automaton to test.
   *
   * @return true if the automaton is ambiguous.
   */
  template<typename S, typename A>
  bool
  is_ambiguous(const Element<S, A>& aut);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/is_ambiguous.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_IS_AMBIGUOUS_HH
