// words.hh
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

#ifndef ALGEBRA_WORDS_HH
# define ALGEBRA_WORDS_HH

# include <string>
# include <vaucanson/algebra/concept/freemonoid_base.hh>

namespace vcsn {

  namespace algebra {

    /*------------.
    | SetWords<A> |
    `------------*/

    template<typename A>
    struct SetWords 
      : FreeMonoidBase<SetWords<A> >
    {
      typedef A alphabets_elt_t;

      // in case of default constructor, do not forget to attach an
      // alphabet, otherwise the alphabet is empty.
      SetWords();
      SetWords(const A& a);
      SetWords(const SetWords& w);

      A&	alphabet();
      const A&	alphabet() const;

    protected:
      A alph_;
    };

  }

    /*----------------------.
    | MetaSet<SetWords<A> > |
    `----------------------*/
    template<typename A>
    struct MetaSet<SetWords<A> >
    {
      static const bool		dynamic_set = A::dynamic;
      typedef algebra::mul_kind semigroup_kind;
      typedef A			alphabet_t;
    };

    /*-------------------------.
    | MetaElement<SetWords<A>, T> |
    `-------------------------*/
    template<typename A, typename T>
    struct MetaElement<SetWords<A>, T>
      : MetaElement<FreeMonoidBase<SetWords<A> >, T>
    {};

  namespace traits {
    
    template<typename A>
    struct virtual_types<algebra::SetWords<A> >
    {
      typedef A alphabet_t;
    };

  } // traits

} // vcsn

template<typename A>
bool operator==(const vcsn::algebra::SetWords<A>& a,
		const vcsn::algebra::SetWords<A>& b);

# include <vaucanson/algebra/concrete/free_monoid/words.hxx>

#endif // ALGEBRA_WORDS_HH

