// monoid_base.hh
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


#ifndef ALGEBRA_MONOID_BASE_HH
# define ALGEBRA_MONOID_BASE_HH

# include <vaucanson/algebra/concept/semigroup_base.hh>

namespace vcsn {

  namespace algebra {

    /*-----------------.
    | MonoidBase<Self> |
    `-----------------*/
    //! MonoidBase is the base class of all structures that are monoids.
    /*! Monoid define identity for semigroups of mul_kind and zero for
      semigroup of add_kind.
    */

    template<class Self>
    struct MonoidBase : SemigroupBase<Self>
    {
      template<typename T>
      Element<Self, T> identity(SELECTOR(T)) const;

      template<typename T>
      Element<Self, T> zero(SELECTOR(T)) const;

    protected:
      MonoidBase();
      MonoidBase(const MonoidBase& other);
    };

  } // algebra

  using namespace algebra;

    /*---------------------------------.
    | MetaElement<MonoidBase<Self>, T> |
    `---------------------------------*/
    template<class Self, typename T>
    struct MetaElement<MonoidBase<Self>, T> 
      : MetaElement<SemigroupBase<Self>, T>
    { 
    protected:
      MetaElement();
      MetaElement(const MetaElement& other);
    };

    template<typename T, typename Self>
    T op_default(SELECTOR(MonoidBase<Self>), SELECTOR(T));

} // vcsn

# include <vaucanson/algebra/concept/monoid_base.hxx>

#endif // ALGEBRA_MONOID_BASE_HH
