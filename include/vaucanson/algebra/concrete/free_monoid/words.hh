// words.hh
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

#ifndef VCSN_ALGEBRA_CONCRETE_WORDS_HH
# define VCSN_ALGEBRA_CONCRETE_WORDS_HH

# include <string>
# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <vaucanson/misc/unique.hh>

namespace vcsn {

  namespace algebra {

    /*! @addtogroup algebra    */ /*! @{ */
    /*! @addtogroup freemonoid */ /*! @{ */
    
    /*------------.
    | FreeMonoid<A> |
    `------------*/
    //! Implementation of a free monoid which aggregates its alphabet.
    template<typename A>
    struct FreeMonoid 
      : FreeMonoidBase<FreeMonoid<A> >
    {
      typedef A alphabets_elt_t;

      //! Default constructor.
      FreeMonoid();

      //! Constructor based on an alphabet.
      FreeMonoid(const A& a);

      //! Copy constructor.
      FreeMonoid(const FreeMonoid& w);

      //! Alphabet's accessor.
      A&	alphabet();

      //! Alphabet's accessor (const version).
      const A&	alphabet() const;

    protected:
      A alph_;
    };

    template<typename A>
    bool operator==(const FreeMonoid<A>& a,
		    const FreeMonoid<A>& b);


    /*! @} @} */

  };

  /*! @addtogroup algebra    */ /*! @{ */
  /*! @addtogroup freemonoid */ /*! @{ */

  /*----------------------.
  | dynamic_traits<FreeMonoid<A> > |
  `----------------------*/
  //! Meta information about FreeMonoid.
  template<typename A>
  struct dynamic_traits<algebra::FreeMonoid<A> >
    : dynamic_traits<algebra::FreeMonoidBase<algebra::FreeMonoid<A> > >
  {
    //! SetWord is dynamic iff its alphabet is.
    static const bool		ret = A::dynamic;
  };
  
  /*----------------------------.
  | MetaElement<FreeMonoid<A>, T> |
  `----------------------------*/
  //! Services of an element of a free monoid implemented with
  //! FreeMonoid.
  template<typename A, typename T>
  struct MetaElement<algebra::FreeMonoid<A>, T>
    : MetaElement<algebra::FreeMonoidBase<algebra::FreeMonoid<A> >, T>
  {};
  
  /*! @} @} */

  template <class A>
  struct virtual_types<algebra::FreeMonoid<A> >
    : virtual_types<algebra::FreeMonoidBase<algebra::FreeMonoid<A> > >
  {
    //! Commonly a free monoid use the multiplication symbol as operation.
    typedef algebra::mul_kind semigroup_kind;
    
    typedef A		alphabet_t;
  };

  
} // vcsn

# include <vaucanson/algebra/concrete/free_monoid/words.hxx>

#endif // VCSN_ALGEBRA_CONCRETE_WORDS_HH

