// words.hxx
//
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
#ifndef VCSN_ALGEBRA_CONCRETE_WORDS_HXX
# define VCSN_ALGEBRA_CONCRETE_WORDS_HXX

# include <vaucanson/algebra/concrete/free_monoid/words.hh>

namespace vcsn {

  namespace algebra {

    /*---------.
    | Words<A> |
    `---------*/

    template <class A>
    inline FreeMonoid<A>::FreeMonoid() 
    {}
    
    template <class A>
    inline FreeMonoid<A>::FreeMonoid(const A& a) : alph_(a) 
    {}
    
    template <class A>
    inline FreeMonoid<A>::FreeMonoid(const FreeMonoid& w) : 
      FreeMonoidBase<FreeMonoid<A> >(w),
      alph_(w.alph_) 
    {}
    
    template <class A>
    inline A& FreeMonoid<A>::alphabet()
    { 
      return alph_; 
    }
    
    template <class A>
    inline const A& FreeMonoid<A>::alphabet() const
    { 
      return alph_; 
    }

  } // algebra
    
} // vcsn

template<typename A>
bool operator==(const vcsn::algebra::FreeMonoid<A>& a,
		const vcsn::algebra::FreeMonoid<A>& b)
{ 
  return a.alphabet() == b.alphabet(); 
}

#endif // VCSN_ALGEBRA_CONCRETE_WORDS_HXX

