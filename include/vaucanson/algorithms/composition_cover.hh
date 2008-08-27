// composition_cover.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_COMPOSITION_COVER_HH
# define VCSN_ALGORITHMS_COMPOSITION_COVER_HH

# include <vaucanson/automata/concept/automata_base.hh>

/** @addtogroup algorithms *//** @{ */
/**
 * @file composition_cover.hh
 * @author Guillaume Leroi
 *
 * @brief Composition for normalized and sub-normalized transducers
 * seen as automata over a free monoid product.
 *
 * @see composition_cover()
 * @see composition_co_cover()
 */
/** @} */

// INTERFACE: Automaton composition_cover(const Automaton& a1) { return vcsn::composition_cover(*a1); }
// INTERFACE: GenAutomaton composition_cover(const GenAutomaton& a1) { return vcsn::composition_cover(*a1); }
// INTERFACE: Automaton composition_co_cover(const Automaton& a1) { return vcsn::composition_co_cover(*a1); }
// INTERFACE: GenAutomaton composition_co_cover(const GenAutomaton& a1) { return vcsn::composition_co_cover(*a1); }

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  template <typename S, typename T>
  Element<S, T>
  composition_cover (const Element<S, T>& fmp);

  template <typename S, typename T>
  void
  composition_cover (const Element<S, T>& fmp,
		     Element<S, T>& ret);


  template <typename S, typename T>
  Element<S, T>
  composition_co_cover (const Element<S, T>& fmp);

  template <typename S, typename T>
  void
  composition_co_cover (const Element<S, T>& fmp,
			Element<S, T>& ret);

  /** @} */
}

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
# include <vaucanson/algorithms/composition_cover.hxx>
#endif // ! VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_COMPOSITION_COVER_HH
