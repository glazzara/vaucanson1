// isomorph.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_ISOMORPH_HH
# define VCSN_ALGORITHMS_ISOMORPH_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file isomorph.hh
 * @author Rodrigo de Souza <arsouza@enst.fr>
 *
 * This files contains the declaration for the are_isomorphic() algorithm.
 *
 * @see are_isomorphic()
 */
/** @} */

// INTERFACE: bool are_isomorphic(const Automaton& a1, const Automaton& a2) { return vcsn::are_isomorphic(*a1, *a2); }
// INTERFACE: bool are_isomorphic(const GenAutomaton& a1, const GenAutomaton& a2) { return vcsn::are_isomorphic(*a1, *a2); }

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /// Returns true if the two automata are isomorphic.
  template<typename A, typename T>
  bool
  are_isomorphic(const Element<A, T>& a, const Element<A, T>& b);

  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algorithms/isomorph.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_ISOMORPH_HH
