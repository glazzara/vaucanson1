// freemonoid_base.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_CONCEPT_FREEMONOID_BASE_HH
# define VCSN_ALGEBRA_CONCEPT_FREEMONOID_BASE_HH

# include <vaucanson/algebra/concept/alphabets_base.hh>
# include <vaucanson/algebra/concept/monoid_base.hh>
# include <string>
# include <list>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup freemonoid *//** @{ */

    /*---------------------.
    | FreeMonoidBase<Self> |
    `---------------------*/

    /**
     * Structural element for free monoid.
     *
     * @c FreeMonoidBase is the mother  class of free monoids.  A free
     * monoid  A* is a  monoid generated  by an  alphabet A  and which
     * provides a way of iterating through letters of words.
     */

    template<class Self>
    struct FreeMonoidBase
      : MonoidBase<Self>
    {
      /// The type of the alphabet A.
      typedef typename virtual_types<Self>::alphabet_t  alphabet_t;

      /// The type of letter hold by the alphabet.
      typedef typename alphabet_t::letter_t			letter_t;

      /// Alphabet's accessor.
      alphabet_t&	alphabet();

      /// Alphabet's const accessor.
      const alphabet_t& alphabet() const;

    protected:
      /// Default constructor accessor.
      FreeMonoidBase();

      /// Copy constructor accessor.
      FreeMonoidBase(const FreeMonoidBase& m);
    };

    /** @} */
    /** @} */

  } // algebra

  /** @addtogroup algebra *//** @{ */
  /** @addtogroup freemonoid *//** @{ */

  /*--------------------------------------.
  | dynamic_traits<FreeMonoidBase<Self> > |
  `--------------------------------------*/

  template<class Self>
  struct dynamic_traits<algebra::FreeMonoidBase<Self> >
    : dynamic_traits<algebra::MonoidBase<Self> >
  { };

  template<typename S>
  struct virtual_types<algebra::FreeMonoidBase<S> >
    : virtual_types<algebra::MonoidBase<S> >
  {
    typedef undefined_type alphabet_t;
  };

  /*-------------------------------------.
  | MetaElement<FreeMonoidBase<Self>, T> |
  `-------------------------------------*/

  /// Element of a free monoid i.e. words.
  template<class Self, typename T>
  struct MetaElement<algebra::FreeMonoidBase<Self>, T>
    : MetaElement<algebra::MonoidBase<Self>, T>
  {
    /// Iterator over the word.
    typedef typename op_begin_traits<Self, T>::ret_t	iterator;

    /// Iterator over the word (const version).
    typedef typename
    op_begin_traits<Self, T>::const_ret_t		const_iterator;

    /// Iterator over the mirror image of the word.
    typedef typename op_rbegin_traits<Self, T>::ret_t	reverse_iterator;

    /// Iterator over the mirror image of the word. (const version)
    typedef typename
    op_rbegin_traits<Self, T>::const_ret_t		const_reverse_iterator;

    /// Returns the lenght of the word.
    size_t		      length() const;

    /// In-place mirror transformation.
    void		      mirror();

    /// Beginning of the word.
    iterator			begin();

    /// Beginning of the word (const version).
    const_iterator		begin() const;

    /// Beginning of the mirror image of the word.
    reverse_iterator		rbegin();

    /// Beginning of the mirror image of the word. (const version)
    const_reverse_iterator	rbegin() const;

    /// End of the word.
    iterator			end();

    /// End of the word (const version).
    const_iterator		end() const;

    /// End of the mirror image of the word.
    reverse_iterator		rend();

    /// End of the mirror image of the word (const version).
    const_reverse_iterator	rend() const;

  protected:
    /// Default constructor is protected since it is an abstract class.
    MetaElement();

    /// Copy constructor is protected since it is an abstract class.
    MetaElement(const MetaElement& other);
  };

  /// Return a fresh word that is the mirror
  template<typename S, typename T>
  Element<S, T>
  mirror(const Element<S, T>& e);

  /// Parse the beginning of the string looking for a word.
  template <typename S, typename T, typename CharContainer>
  bool
  parse_word(Element<S, T>& dest,
	     const std::string& s,
	     typename std::string::const_iterator& i,
	     const CharContainer& escaped = CharContainer ());

  /** @} */
  /** @} */

  template <typename S, typename T, typename CharContainer>
  bool op_parse(const algebra::FreeMonoidBase<S>& s, T& v,
		const std::string&,
		typename std::string::const_iterator&,
		const CharContainer& escaped);

  template<typename Self, typename T>
  void op_in_mirror(const algebra::FreeMonoidBase<Self>& s, T& v);

  template<typename Self, typename T>
  bool op_contains(const algebra::FreeMonoidBase<Self>& s, const T& v);

  template<typename Self, typename St, typename T>
  St& op_rout(const algebra::FreeMonoidBase<Self>& s, St& st, const T& v);

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/concept/freemonoid_base.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGEBRA_CONCEPT_FREEMONOID_BASE_HH
