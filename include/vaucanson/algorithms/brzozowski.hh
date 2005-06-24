// brzozowski.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_BRZOZOWSKI_HH
# define VCSN_ALGORITHMS_BRZOZOWSKI_HH

/** @addtogroups algorithms *//** @{ */
/**
 * @file brzozowski.hh
 *
 * Contains the declaration for the Brzozowski algorithm.
 *
 * @see brzozowski()
 */
/** @} */

// INTERFACE: void brzozowski(Automaton& a, const Exp& e) { return vcsn::brzozowski(*a, e); }
// INTERFACE: void brzozowski(GenAutomaton& a, const Exp& e) { return vcsn::brzozowski(*a, e); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms */  /** @{ */

  /// Build an automaton from an expression using the Brzozowski construction.
  template <typename A, typename T, typename Exp>
  void
  brzozowski(Element<A, T>&, const Exp&);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/brzozowski.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_BRZOZOWSKI_HH
