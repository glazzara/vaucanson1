// freemonoid_base.hh
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

#ifndef ALGEBRA_FREEMONOID_BASE_HH
# define ALGEBRA_FREEMONOID_BASE_HH

# include <vaucanson/algebra/concept/alphabets_base.hh>
# include <vaucanson/algebra/concept/monoid_base.hh>

namespace vcsn {

  namespace algebra {

    //! \addtogroup algebra 
    //! \@{

    /*---------------------.
    | FreeMonoidBase<Self> |
    `---------------------*/
    //! Structural element for free monoid.
    /*! FreeMonoidBase is the mother class of free monoids. A free
      monoid A* is a monoid generated by an alphabet A and which provides
      a way of iterating through letters of words. */

    template<class Self>
    struct FreeMonoidBase 
      : MonoidBase<Self>
    {
      /*! The type of the alphabet A. */ 
      typedef typename traits::virtual_types<Self>::alphabet_t  alphabet_t;

      /*! The type of letter hold by the alphabet. */
      typedef typename alphabet_t::letter_t			letter_t;

      /*! Alphabet's accessor. */
      alphabet_t&	alphabet();

      /*! Alphabet's const accessor. */
      const alphabet_t& alphabet() const;

    protected:
      /*! Default constructor accessor. */
      FreeMonoidBase();

      /*! Copy constructor accessor. */
      FreeMonoidBase(const FreeMonoidBase& m);
    };

    //! @}

  } // algebra


  //! \addtogroup algebra 
  //! \@{

  /*-------------------------------------.
  | MetaElement<FreeMonoidBase<Self>, T> |
  `-------------------------------------*/
  //! Element of a free monoid ie words.
  template<class Self, typename T>
  struct MetaElement<FreeMonoidBase<Self>, T>
    : MetaElement<MonoidBase<Self>, T>
  {
    //! iterator over the word.
    typedef typename op_begin_traits<Self, T>::ret_t	iterator;

    //! iterator over the word. (const version)
    typedef typename 
    op_begin_traits<Self, T>::const_ret_t		const_iterator;

    //! iterator over the mirror image of the word.
    typedef typename op_rbegin_traits<Self, T>::ret_t	reverse_iterator;

    //! iterator over the mirror image of the word. (const version)
    typedef typename 
    op_rbegin_traits<Self, T>::const_ret_t		const_reverse_iterator;

    //! returns the lenght of the word. 
    size_t		      length() const;

    //! in-place mirror transformation.
    void		      mirror();
    
    //! beginning of the word.
    iterator			begin();

    //! beginning of the word. (const version)
    const_iterator		begin() const;

    //! beginning of the mirror image of the word.
    reverse_iterator		rbegin();

    //! beginning of the mirror image of the word. (const version)
    const_reverse_iterator	rbegin() const;

    //! end of the word.
    iterator			end();

    //! end of the word (const version).
    const_iterator		end() const;

    //! end of the mirror image of the word.
    reverse_iterator		rend();

    //! end of the mirror image of the word. (const version)
    const_reverse_iterator	rend() const;

  protected:
    //! Default constructor is protected since it is an abstract class.
    MetaElement();

    //! Copy constructor is protected since it is an abstract class.
    MetaElement(const MetaElement& other);
  };

  //! Returns a fresh word that is the mirror 
  template<typename Self, typename T>
  Element<FreeMonoidBase<Self>, T>
  mirror(const Element<FreeMonoidBase<Self>, T>& e);

  //! @}

  template<typename Self, typename T>
  void op_in_mirror(const FreeMonoidBase<Self>& s, T& v);

  template<typename Self, typename T>
  bool op_contains(const FreeMonoidBase<Self>& s, const T& v);

  template<typename Self, typename St, typename T>
  St& op_rout(const FreeMonoidBase<Self>& s, St& st, const T& v);

} // vcsn

# include <vaucanson/algebra/concept/freemonoid_base.hxx>

#endif // ALGEBRA_FREEMONOID_BASE_HH
