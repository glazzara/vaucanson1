// semiring_base.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_ALGEBRA_CONCEPT_SEMIRING_BASE_HH
# define VCSN_ALGEBRA_CONCEPT_SEMIRING_BASE_HH

# include <vaucanson/algebra/concept/monoid_base.hh>
# include <cassert>
# include <string>

namespace vcsn {

  namespace algebra {

    /*! \addtogroup algebra */  /* @{ */
    /*! \addtogroup semiring */ /* @{ */

    /*-------------------.
    | SemiringBase<Self> |
    `-------------------*/
    //! SemiringBase is the base class for all structures that are semirings.
    template <class Self>
    struct SemiringBase : MonoidBase<Self>
    {
    protected:
      //! Default constructor is protected since it is an abstract class.
      SemiringBase();

      //! Copy constructor is protected since it is an abstract class.
      SemiringBase(const SemiringBase& other);
    };

    /*! @} @} */

  } // algebra

  /*! \addtogroup algebra */  /* @{ */
  /*! \addtogroup semiring */ /* @{ */

  /*-----------------------------------.
  | MetaElement<SemiringBase<Self>, T> |
  `-----------------------------------*/
  //! Services of every element of semiring (weight).
  template <typename Self, typename T>
  struct MetaElement<algebra::SemiringBase<Self>, T>
    : MetaElement<algebra::MonoidBase<Self>, T>
  {
    //! in-place star transformation of the weight.
    Element<Self, T>&   star();

    //! returns true if we can to compute the star of the weight.
    bool		stareable() const;

  protected:
    //! Default constructor is protected since it is an abstract class.
    MetaElement();

    //! Copy constructor is protected since it is an abstract class.
    MetaElement(const MetaElement& other);
  };

  //! meta information about the return type of the star operation.
  template <typename S, typename T>
  struct op_star_traits
  {
    typedef Element<S, T> ret_t;
  };
  
  //! returns a fresh weight that is the star of w.
  template <typename S, typename T>
  typename op_star_traits<S, T>::ret_t
  star(const Element<S, T>& w);
  
  //! parse the beginning of the string looking for a weight.
  template <typename S, typename T>
  bool 
  parse_weight(Element<S, T>& w, const std::string&, 
	       typename std::string::const_iterator&);

  //! returns true if we can to compute the star of the weight.
  template <typename S, typename T>
  bool stareable(const Element<S, T>& elt);

  /*! @} @} */

  // default implementations:
  template <typename S, typename T>
  bool 
  op_parse(const SemiringBase<S>&, T& w, 
	const std::string&, 
	typename std::string::const_iterator&);

  template <typename Self, typename T>
  bool op_stareable(const SemiringBase<Self>& s, const T& v);

  template <typename Self, typename T>
  void op_in_star(const SemiringBase<Self>& s, T& v);

  template <typename Self, typename T>
  T op_default(SELECTOR(SemiringBase<Self>), SELECTOR(T));

} // vcsn

# include <vaucanson/algebra/concept/semiring_base.hxx>

#endif // VCSN_ALGEBRA_CONCEPT_SEMIRING_BASE_HH



