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

#ifndef VCSN_ALGEBRA_CONCRETE_WORDS_HH
# define VCSN_ALGEBRA_CONCRETE_WORDS_HH

# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <string>

namespace vcsn {

  namespace algebra {
    
    /*------------.
    | SetWords<A> |
    `------------*/
    //! Implementation of a free monoid which aggregates its alphabet.
    template<typename A>
    struct SetWords 
      : FreeMonoidBase<SetWords<A> >
    {
      typedef A alphabets_elt_t;

      //! Default constructor.
      SetWords();

      //! Constructor based on an alphabet.
      SetWords(const A& a);

      //! Copy constructor.
      SetWords(const SetWords& w);

      //! Alphabet's accessor.
      A&	alphabet();

      //! Alphabet's accessor (const version).
      const A&	alphabet() const;

    protected:
      A alph_;
    };

  };

  /*----------------------.
  | MetaSet<SetWords<A> > |
  `----------------------*/
  //! Meta information about SetWords.
  template<typename A>
  struct MetaSet<SetWords<A> >
  {
    //! SetWord is dynamic iff its alphabet is.
    static const bool		dynamic_set = A::dynamic;
    
    //! Commonly a free monoid use the multiplication symbol as operation.
    typedef algebra::mul_kind semigroup_kind;
    
    //! The type of the alphabet.
    typedef A			alphabet_t;
  };
  
  /*----------------------------.
  | MetaElement<SetWords<A>, T> |
  `----------------------------*/
  //! Services of an element of a free monoid implemented with
  //! SetWords.
  template<typename A, typename T>
  struct MetaElement<SetWords<A>, T>
    : MetaElement<FreeMonoidBase<SetWords<A> >, T>
  {};

  namespace traits {
    
    template <class A>
    struct virtual_types<SetWords<A> >
    {
      typedef A		alphabet_t;
    };

  } // traits
  
} // vcsn

template<typename A>
bool operator==(const vcsn::algebra::SetWords<A>& a,
		const vcsn::algebra::SetWords<A>& b);

# include <vaucanson/algebra/concrete/free_monoid/words.hxx>

#endif // VCSN_ALGEBRA_CONCRETE_WORDS_HH

