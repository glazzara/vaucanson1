// predecls.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_FUNDAMENTAL_PREDECLS_HH
# define VCSN_FUNDAMENTAL_PREDECLS_HH

/** @addtogroup fundamental *//** @{ */
/** 
 * @file predecls.hh
 * @brief Forward declarations of the fundamental template classes of Vaucanson
 */
/** @} */

# include <vaucanson/config/system.hh>

/** @addtogroup fundamental *//** @{ */
/// The main namespace of the Vaucanson library
namespace vcsn {

  template<typename S>
  struct dynamic_traits;
  
  template<typename S, typename T>
  struct SyntacticDecorator;
  
  template<typename S, typename T>
  struct MetaElement;

  template<typename S, typename T>
  struct Element;
  
  template<typename S>
  struct SetSlot;
  
  template<typename Self>
  struct Structure;

  template<typename Self>
  struct virtual_types;

  struct undefined_type {};

} // vcsn
/** @} */

#endif // VCSN_FUNDAMENTAL_PREDECLS_HH
