// edge_value.hxx: this file is part of the Vaucanson project.
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

#ifndef VAUCANSON_AUTOMATA_IMPLEMENTATION_BOOSTG_EDGE_VALUE_HXX
# define VAUCANSON_AUTOMATA_IMPLEMENTATION_BOOSTG_EDGE_VALUE_HXX

# include <vaucanson/automata/implementation/boostg/edge_value.hh>

namespace vcsn
{
  namespace boostg
  {
    /*-----------------------------.
    | Edge value's Implementation. |
    `-----------------------------*/

    template<typename HState, typename HLabel>
    EdgeValue<HState, HLabel>::EdgeValue (HState h1, HState h2, HLabel l)
      : label_ (l), from_ (h1), to_ (h2)
    { }

  }
}

#endif // !VAUCANSON_AUTOMATA_IMPLEMENTATION_BOOSTG_EDGE_VALUE_HXX


