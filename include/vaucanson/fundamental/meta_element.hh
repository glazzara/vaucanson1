// meta_element.hh
//
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#ifndef FUNDAMENTAL_META_ELEMENT_HH
# define FUNDAMENTAL_META_ELEMENT_HH

# include <vaucanson/fundamental/structure.hh>
# include <vaucanson/fundamental/element_base.hh>

namespace vcsn {

  /*! \addtogroup fundamental */ /*! @{ */

  /*--------------------------------.
  | MetaElement<Structure<Self>, T> |
  `--------------------------------*/
  //! MetaElement is the way of defining interactions between a set
  //! and an implementation.
  
  /*! MetaElement<Structure<Self>, T> is the specialization that is at
    the top of all the hierarchy of Vaucanson.

    MetaElement<Structure<Self>, T> is decorated with a
    SyntacticDecorator<Self, T>.
  */

  template<class Self, typename T>
  struct MetaElement<Structure<Self>, T>
    : SyntacticDecorator<Self, T>
  {
  public:
    /*! Default value of dynamic_values is true. */
    static const bool dynamic_values = true;

  protected:
    /*! Every constructor is protected since MetaElement is an
      abstract class in the static hierarchy. */
    MetaElement(); 

    /*! Every constructor is protected since MetaElement is an
      abstract class in the static hierarchy. */
    MetaElement(const MetaElement& other); 
  };

  /*! @} */

} // vcsn

# include <vaucanson/fundamental/meta_element.hxx>

#endif //  FUNDAMENTAL_META_ELEMENT_HH
