// words.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_WORDS_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_WORDS_HXX

# include <vaucanson/algebra/implementation/free_monoid/words.hh>

namespace vcsn {

  namespace algebra {

    /*---------.
    | Words<A> |
    `---------*/

    template <class A>
    FreeMonoid<A>::FreeMonoid(const A& a) : alph_(a)
    {}

    template <class A>
    FreeMonoid<A>::FreeMonoid(const FreeMonoid& w) :
      FreeMonoidBase<FreeMonoid<A> >(w),
      alph_(w.alph_)
    {}

    template <class A>
    A& FreeMonoid<A>::alphabet()
    {
      return alph_;
    }

    template <class A>
    const A& FreeMonoid<A>::alphabet() const
    {
      return alph_;
    }

    template<typename A>
    bool operator==(const FreeMonoid<A>& a,
		    const FreeMonoid<A>& b)
    {
      return a.alphabet() == b.alphabet();
    }

  } // algebra

} // vcsn


#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_WORDS_HXX
