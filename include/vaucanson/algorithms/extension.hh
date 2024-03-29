// extension.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EXTENSION_HH
# define VCSN_ALGORITHMS_EXTENSION_HH

/** @addtogroup algorithms *//** @{ */
/**
 * @file extension.hh
 *
 * Declarations for extension().
 *
 * @see extension()
 */
/** @} */

// Interface: Transducer extension(const Automaton& a) { return vcsn::extension(*a); }
// Interface: void extension(const Automaton& a, Transducer& res) { vcsn::extension(*a, *t); }

# include <vaucanson/automata/concept/transducer.hh>

namespace vcsn {

  /** @addtogroup algorithms *//** @{ */

  /**
   * Extend an automaton to a transducer.
   *
   * Extend  an automaton to  a transducer  whose multiplicity  is the
   * series of the automaton.
   */
  template <typename S, typename K, typename T>
  typename identity_transducer_helper<S, K, T>::ret
  extension(const Element<S, T>&);


  /**
   * Extend an automaton to a transducer.
   *
   * Extend  an automaton  to a  transducer whose  set is  the  one of
   * another transducer passed in  the second argument. This extension
   * is required if  we want to make a product of  an automaton with a
   * transducer.  If  this  is  not  the case,  we  need  simply  call
   * extension(automaton_t) above.
   */
  template <typename SA, typename TA,
	    typename ST, typename TT>
  Element<ST, TT>
  extension(const Element<SA, TA>&,
	    const Element<ST, TT>&);

  /** @} */

}

# if !defined VCSN_USE_INTERFACE_ONLY && !defined VCSN_USE_LIB
#  include <vaucanson/algorithms/extension.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGORITHMS_EXTENSION_HH
