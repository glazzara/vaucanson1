// decorated_alphabet.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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
#ifndef VCSN_ALGEBRA_CONCRETE_ALPHABET_DECORATED_ALPHABET_HH
# define VCSN_ALGEBRA_CONCRETE_ALPHABET_DECORATED_ALPHABET_HH

# include <vaucanson/algebra/concrete/alphabets/alphabets.hh>

namespace vcsn {

  namespace algebra {

    /*! @ingroup alphabet */ /*! @{ */

    /*---------------------.
    | AlphabetDecorator<T> |
    `---------------------*/
    //! Decorate a given alphabet implementation with meta-symbols.
    //! The meta-symbols are:
    //! - a 'joker' which symbolizes every letter of the alphabet.
    //! - a 'discard' which symbolizes every letter that is not in the 
    //!   alphabet but of the same letter type.
    //! The meta-symbols are encoded using the type of the letter with a 
    //! default value that has to be specified with the traits 'meta_symbol'.
    //! For instance, '?' and '#' for char. Yet, if these characters are 
    //! already present in the alphabet, we look for another character in a
    //! incremental way. If, unfortunately, there is not enough place, the 
    //! program is stopped.
    template <class L, class T>
    class AlphabetDecorator
    {
    public:
      typedef L		letter_t;
      typedef T		alphabet_impl_t;
      typedef typename T::const_iterator const_iterator;
      typedef typename T::iterator iterator;

      AlphabetDecorator();
      AlphabetDecorator(alphabet_impl_t& alphabet);
      ~AlphabetDecorator();

      letter_t joker() const;
      letter_t other() const;
      void insert(L);
      unsigned size() const;
      iterator begin();
      iterator end();
      const_iterator begin() const;
      const_iterator end() const;
      alphabet_impl_t& alphabet();
      const alphabet_impl_t& alphabet() const;

    private:
      alphabet_impl_t* alphabet_;
      letter_t	       joker_;
      letter_t	       other_;
      bool	       alphabet_owner_;
    }; 


    /*---------------------------------------------.
    | alphabet_traits<AlphabetSet<L>,std::set<L>> |
    `---------------------------------------------*/
    //! meta information about the mixing of AlphabetSet with
    //! std::set.
    template<typename L, typename T>
    struct alphabet_traits<AlphabetSet<L>, AlphabetDecorator<L, T> >
    {
      //! The type of letter hold by the alphabet.
      typedef L			letter_t;
    };

    //! @}

  } // algebra
  
  /*! @ingroup alphabet */ /*! @{ */

  /*------------------------------------------.
  | MetaElement<AlphabetSet<L>, std::set<L>> |
  `------------------------------------------*/
  //! Services of every alphabet implemented with AlphabetDecorator<T>.
  //! See MetaElement<AlphabetSetBase<Self>, T>.
  template<typename L, typename T>
  struct MetaElement<algebra::AlphabetSet<L>, algebra::AlphabetDecorator<L, T> >
    : MetaElement<algebra::AlphabetSetBase<algebra::AlphabetSet<L> >, algebra::AlphabetDecorator<L, T> >
  {
    //! The dynamic properties depends on the implementation one.
    static const bool dynamic_values = 
    MetaElement<algebra::AlphabetSet<L>,T >::dynamic_values;

    //! The meta-symbol that symbolizes all the alphabet's symbols.
    L	joker() const;

    //! The meta-symbol that symbolizes the symbol not in the alphabet.
    L	other() const;
  };
  
  //! @}

  template<typename L, typename T>
  bool op_contains(const algebra::AlphabetSet<L>& s, 
		   const algebra::AlphabetDecorator<L, T>& a);
  
  template<typename L, typename T>
  bool op_is_finite(const algebra::AlphabetSet<L>& s, 
		    const algebra::AlphabetDecorator<L, T>& a);
  
  template<typename L, typename T>
  bool op_contains_e(const algebra::AlphabetSet<L>& s, 
		     const algebra::AlphabetDecorator<L, T>& a, 
		     const L& v);
    
  template <typename T, typename L>
  bool op_letter_equality(const algebra::AlphabetSet<L>& s, 
				 const algebra::AlphabetDecorator<L, T>& a, 
				 L lhs,
				 L rhs);


} // vcsn

# include <vaucanson/algebra/concrete/alphabets/decorated_alphabet.hxx>
 
#endif // VCSN_ALGEBRA_CONCRETE_ALPHABET_DECORATED_ALPHABET_HH
