// meta_element_root.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_FUNDAMENTAL_META_ELEMENT_ROOT_HH
# define VCSN_FUNDAMENTAL_META_ELEMENT_ROOT_HH

/** @addtogroup design_pattern *//** @{ */
/**
 * @file meta_element_root.hh
 * @brief Definition of the specialization of @c MetaElement for the root @c Structure
 */
/** @} */

# include <vaucanson/design_pattern/structure.hh>
# include <vaucanson/design_pattern/syntactic_decorator.hh>

namespace vcsn {

  /** @addtogroup design_pattern *//** @{ */

  /*--------------------------------.
  | MetaElement<Structure<Self>, T> |
  `--------------------------------*/

  /** 
   * @brief The base class that glues structural elements to implementation values.
   *
   * MetaElement<Structure<Self>, T> is the specialization that is at
   * the top of all the hierarchy of Vaucanson. It inherits, and thus
   * is decorated with, SyntacticDecorator<Self, T>.
   *
   * @see
   *   * @c SyntacticDecorator
   *   * @c Element
   *   * @c Structure
   */

  template<class S, typename T>
  struct MetaElement<Structure<S>, T>
    : SyntacticDecorator<S, T>
  {
  protected:
    /** @{ */
    /// Protected constructor for class abstraction
    MetaElement(); 
    MetaElement(const MetaElement& other); 
    /** @} */
  };

  /** @} */

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/design_pattern/meta_element_root.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_FUNDAMENTAL_META_ELEMENT_ROOT_HH
