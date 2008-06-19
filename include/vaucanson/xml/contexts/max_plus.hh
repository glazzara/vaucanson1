// max_plus.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_XML_CONTEXTS_MAX_PLUS_HH
# define VCSN_XML_CONTEXTS_MAX_PLUS_HH

/**
 * @file max_plus.hh
 *
 * Tools to help loading automata.
 *
 * @see vcsn::xml::*Handler
 *
 * @author Florian Lesaint <florian.lesaint@lrde.epita.fr>
 */

# include <string>

# include <xercesc/sax2/Attributes.hpp>
# include <xercesc/util/XMLString.hpp>

# include <vaucanson/xml/handlers_base.hh>
# include <vaucanson/xml/builders.hh>
# include <vaucanson/xml/regexp.hh>

# include <vaucanson/algebra/implementation/semiring/tropical_semiring.hh>

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
      const char* get_semiring_operations<
	vcsn::algebra::TropicalSemiring<vcsn::algebra::TropicalMax>
      >(const vcsn::algebra::TropicalSemiring<vcsn::algebra::TropicalMax>&);
    } // !builders
  } // !xml
} // !vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/xml/contexts/max_plus.hxx>
# endif // VCSN_USE_INTERFACE_ONLY || !VCSN_USE_LIB

#endif // !VCSN_XML_CONTEXTS_MAX_PLUS_HH
