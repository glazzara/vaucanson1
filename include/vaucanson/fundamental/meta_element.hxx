// meta_element.hxx
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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


#ifndef FUNDAMENTAL_META_ELEMENT_HXX
# define FUNDAMENTAL_META_ELEMENT_HXX

# include <vaucanson/fundamental/structure.hh>
# include <vaucanson/fundamental/element_base.hh>
# include <vaucanson/fundamental/meta_element.hh>

namespace vcsn {

 template <class Self, class T>
 MetaElement<Structure<Self>, T>::MetaElement()
 {}
  
  template <class Self, class T>
  MetaElement<Structure<Self>, T>::MetaElement(const MetaElement& o) :
    SyntacticDecorator<Self, T>(o)
  {}
  
} // vcsn

#endif //  FUNDAMENTAL_META_ELEMENT_HXX
