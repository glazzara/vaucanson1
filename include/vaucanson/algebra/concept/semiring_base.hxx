// semiring_base.hxx
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


#ifndef ALGEBRA_SEMIRING_BASE_HXX
# define ALGEBRA_SEMIRING_BASE_HXX

# include <vaucanson/algebra/concept/semiring_base.hh>

namespace vcsn {

  namespace algebra {

    /*-------------.
    | SemiringBase |
    `-------------*/

    template <class Self>
    SemiringBase<Self>::SemiringBase()
    {}
    
    template <class Self>
    SemiringBase<Self>::SemiringBase(const SemiringBase& other) :
      MonoidBase<Self>(other)
    {}

  } // algebra


    /*---------------------.
    | MetaElement<Self, T> |
    `---------------------*/

    template <class Self, class T>
    Element<Self, T>& 
    MetaElement<algebra::SemiringBase<Self>, T>::star()
    { 
      op_in_star(this->set(), this->value());
      return self();
    }

    template <class Self, class T>
    bool 
    MetaElement<algebra::SemiringBase<Self>, T>::stareable() const
    { 
      return op_stareable(this->set(), this->value()); 
    }
    
    template <class Self, class T>
    MetaElement<algebra::SemiringBase<Self>, T>::MetaElement() 
    {}

    template <class Self, class T>
    MetaElement<algebra::SemiringBase<Self>, T>::MetaElement(const MetaElement& other) :
      MetaElement<algebra::MonoidBase<Self>, T>(other)
    {}

    /*-----.
    | star |
    `-----*/

    template<typename S, typename T>
    typename op_star_traits<S, T>::ret_t
    star(const Element<S, T>& e)
    { 
      typename op_star_traits<S, T>::ret_t res(e);
      return res.star();
    }
    
    template<typename S, typename T>
    bool stareable(const Element<S, T>& elt)
    { 
      return op_stareable(elt.set(), elt.value()); 
    }

    // default implementations:

    template<typename Self, typename T>
    bool op_stareable(const algebra::SemiringBase<Self>& s, const T& v)
    { 
      return op_eq(SELECT(Self), v, zero_value(SELECT(Self), SELECT(T)));
    }

    template<typename Self, typename T>
    void op_in_star(const algebra::SemiringBase<Self>& s, T& v)
    {
      assert(op_eq(SELECT(Self), v, zero_value(SELECT(Self), SELECT(T))));
      v = identity_value(SELECT(Self), SELECT(T));
    } 

    template<typename Self, typename T>
    T op_default(SELECTOR(algebra::SemiringBase<Self>), SELECTOR(T))
    {
      return zero_value(SELECT(Self), SELECT(T)); 
    }

} // vcsn

#endif // ALGEBRA_SEMIRING_BASE_HXX



