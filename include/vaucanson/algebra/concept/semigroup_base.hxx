// semigroup_base.hxx
//
// 
// $Id$
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


#ifndef ALGEBRA_SEMIGROUP_BASE_HXX
# define ALGEBRA_SEMIGROUP_BASE_HXX

# include <vaucanson/fundamental/fundamental.hh>

namespace vcsn {

  namespace algebra {
    
    template<class Self> 
    SemigroupBase<Self>::SemigroupBase() 
    {}

    template<class Self> 
    SemigroupBase<Self>::SemigroupBase(const SemigroupBase& other) :
      Structure<Self>(other)
    {}
        
  } // algebra
  
  template<class Self, typename T>
  MetaElement<algebra::SemigroupBase<Self>, T>::MetaElement() 
  {}
  
  template<class Self, typename T>
  MetaElement<algebra::SemigroupBase<Self>, T>::MetaElement(const MetaElement& other) :
    MetaElement<Structure<Self>, T>(other)
  {}
    
} // vcsn

#endif // ALGEBRA_SEMIGROUP_BASE_HXX
