// max_plus.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_CONTEXTS_MAX_PLUS_HXX
# define VCSN_XML_CONTEXTS_MAX_PLUS_HXX

# include <vaucanson/xml/builders.hh>

namespace vcsn
{
  namespace xml
  {
    /**
     * Consistency
     */
    namespace builders
    {
      template <>
      const char* get_semiring_operations<>(const vcsn::algebra::TropicalSemiring<vcsn::algebra::TropicalMax>&)
      {
	return "maxPlus";
      }
    } // !builders
  } // !xml
} // !vcsn

#endif // !VCSN_XML_CONTEXTS_MAX_PLUS_HXX
