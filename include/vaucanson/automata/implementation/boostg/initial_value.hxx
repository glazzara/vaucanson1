// initial_value.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007 The Vaucanson Group.
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

#ifndef VAUCANSON_AUTOMATA_IMPLEMENTATION_BOOSTG_INITIAL_VALUE_HXX
# define VAUCANSON_AUTOMATA_IMPLEMENTATION_BOOSTG_INITIAL_VALUE_HXX

# include <vaucanson/automata/implementation/boostg/initial_value.hh>

namespace vcsn
{
  namespace boostg
  {

    /*------------------------------------------------.
    | Structure for initial/final states information. |
    `------------------------------------------------*/

    template <typename HState, typename Series>
    InitialValue<HState, Series>::InitialValue(const HState& state, const Series& series)
      : first(state),
	second(series)
    {}

  }
}

#endif // ! VAUCANSON_AUTOMATA_IMPLEMENTATION_BOOSTG_INITIAL_VALUE_HXX

