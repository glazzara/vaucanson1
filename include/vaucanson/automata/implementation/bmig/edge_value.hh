// edge_value.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2007, 2008 The Vaucanson Group.
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

#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BMIG_EDGEVALUE_HH_
# define VCSN_AUTOMATA_IMPLEMENTATION_BMIG_EDGEVALUE_HH_

namespace vcsn
{
  namespace bmig
  {

    template<typename HState, typename HLabel>
    struct EdgeValue
    {
      EdgeValue (HState from, HState to, HLabel l);

      HLabel label_;
      HState from_;
      HState to_;
    }; // End of class EdgeValue

  } // bmig
} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/implementation/bmig/edge_value.hxx>
# endif
#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_BMIG_EDGEVALUE_HH_

