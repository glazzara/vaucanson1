// semigroup_base.hh
//
// 
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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


#ifndef ALGEBRA_SEMIGROUP_BASE_HH
# define ALGEBRA_SEMIGROUP_BASE_HH

# include <vaucanson/fundamental/fundamental.hh>

namespace vcsn {

  namespace algebra {

    struct mul_kind 
    {};

    struct add_kind 
    {};

    //! SemigroupBase is the base class of all structures that are semigroups.
    /*! All derived classes must define type MetaSet<S>::semigroup_kind.
     */
    template<class Self>
    struct SemigroupBase : Structure<Self>
    {
      
    protected:
      SemigroupBase();
      SemigroupBase(const SemigroupBase& other);
    };

  } // algebra

  template<class Self, typename T>
  struct MetaElement<algebra::SemigroupBase<Self>, T>
    : MetaElement<Structure<Self>, T>
  {
  protected:
    MetaElement();
    MetaElement(const MetaElement& other);
  };
  
} // vcsn

# include <vaucanson/algebra/concept/semigroup_base.hxx>

#endif // ALGEBRA_SEMIGROUP_BASE_HH
