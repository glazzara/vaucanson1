// meta_element_root.hxx
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


#ifndef VCSN_FUNDAMENTAL_META_ELEMENT_ROOT_HXX
# define VCSN_FUNDAMENTAL_META_ELEMENT_ROOT_HXX

# include <vaucanson/fundamental/meta_element_root.hh>

namespace vcsn {

  template <class S, class T>
  MetaElement<Structure<S>, T>::MetaElement()
  {}
  
  template <class S, class T>
  MetaElement<Structure<S>, T>::MetaElement(const MetaElement& o) :
    SyntacticDecorator<S, T>(o)
  {}
  
} // vcsn

#endif // VCSN_FUNDAMENTAL_META_ELEMENT_ROOT_HXX
