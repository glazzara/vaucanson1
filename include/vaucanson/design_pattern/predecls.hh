// predecls.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_DESIGN_PATTERN_PREDECLS_HH
# define VCSN_DESIGN_PATTERN_PREDECLS_HH

/** @addtogroup design_pattern *//** @{ */
/**
 * @file predecls.hh
 *
 * Forward declarations of the design pattern template classes of Vaucanson.
 */
/** @} */

# include <vaucanson/config/system.hh>

/// The main namespace of the Vaucanson library
namespace vcsn {

  /** @addtogroup design_pattern *//** @{ */

  template<typename S>
  struct dynamic_traits;

  template<typename S, typename T>
  struct SyntacticDecorator;

  template<typename S, typename T>
  struct MetaElement;

  template<typename S, typename T>
  struct Element;

  struct default_slot_tag {};

  template<typename S, typename Tag = default_slot_tag>
  struct SetSlot;

  template<typename Self>
  struct Structure;

  template<typename Self>
  struct virtual_types;

  struct undefined_type {};


  /** @} */

} // vcsn

#endif // ! VCSN_DESIGN_PATTERN_PREDECLS_HH
