// characteristic.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_CHARACTERISTIC_HH
# define VCSN_ALGORITHMS_CHARACTERISTIC_HH

/**
 * @file characteristic.hh
 *
 * Characteristic algorithm.
 */

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>

namespace vcsn
{

  /**
   * @brief Build a characteristic automaton.
   */
  template<typename lhs_t, typename rhs_t>
  void characteristic(lhs_t& dst, const rhs_t& from);

} // ! vcsn


#include <vaucanson/algorithms/characteristic.hxx>


#endif // ! VCSN_ALGORITHMS_CHARACTERISTIC_HH
