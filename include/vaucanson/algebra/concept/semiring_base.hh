// semiring_base.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_CONCEPT_SEMIRING_BASE_HH
# define VCSN_ALGEBRA_CONCEPT_SEMIRING_BASE_HH

# include <vaucanson/algebra/concept/monoid_base.hh>
# include <vaucanson/misc/contract.hh>
# include <string>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup semiring *//** @{ */

    /*-------------------.
    | SemiringBase<Self> |
    `-------------------*/

    /// SemiringBase is the base class for all structures that are semirings.
    template <class Self>
    struct SemiringBase : MonoidBase<Self>
    {
    public:
      /**
       * Indicate wether it is possible or not to call choose_non_starable.
       *
       * There's no need for can_choose_starable, since Zero is always
       * starable and therefor can be choosen.
       */
      template <class T>
      bool can_choose_non_starable(SELECTOR(T)) const;

      /// Return a randomly choosed starable semiring element.
      template <class T>
      Element<Self, T>	choose_starable(SELECTOR(T)) const;

      /// Return a randomly choosed non-starable semiring element.
      template <class T>
      Element<Self, T> choose_non_starable(SELECTOR(T)) const;
    protected:
      /// Default constructor is protected since it is an abstract class.
      SemiringBase();

      /// Copy constructor is protected since it is an abstract class.
      SemiringBase(const SemiringBase& other);
    };

    /** @} */
    /** @} */

  } // algebra

  /** @addtogroup algebra *//** @{ */
  /** @addtogroup semiring *//** @{ */

  /*------------------------------------.
  | dynamic_traits<SemiringBase<Self> > |
  `------------------------------------*/

  template<typename Self>
  struct dynamic_traits<algebra::SemiringBase<Self> >
    : dynamic_traits<algebra::MonoidBase<Self> >
  { };

  template<typename S>
  struct virtual_types<algebra::SemiringBase<S> >
    : virtual_types<algebra::MonoidBase<S> >
  { };

  /*-----------------------------------.
  | MetaElement<SemiringBase<Self>, T> |
  `-----------------------------------*/

  /// Services of every element of semiring (semiring_elt).
  template <typename Self, typename T>
  struct MetaElement<algebra::SemiringBase<Self>, T>
    : MetaElement<algebra::MonoidBase<Self>, T>
  {
    /// In-place star transformation of the weight.
    Element<Self, T>&   star();

    /// Returns true if we can compute the star of the weight.
    bool		starable() const;

  protected:
    /// Default constructor is protected since it is an abstract class.
    MetaElement();

    /// Copy constructor is protected since it is an abstract class.
    MetaElement(const MetaElement& other);
  };

  /// Meta information about the return type of the star operation.
  template <typename S, typename T>
  struct op_star_traits
  {
    typedef Element<S, T> ret_t;
  };

  /// Returns a fresh weight that is the star of w.
  template <typename S, typename T>
  typename op_star_traits<S, T>::ret_t
  star(const Element<S, T>& w);

  /// Parse the beginning of the string looking for a weight.
  template <typename S, typename T>
  bool
  parse_weight(Element<S, T>& w, const std::string&,
	       typename std::string::const_iterator&);

  /// Returns true if we can compute the star of the weight.
  template <typename S, typename T>
  bool starable(const Element<S, T>& elt);

  /** @} */
  /** @} */

  // default implementations:

  /// Returns whether a non-starable @c Element can be choosen from a Semiring.
  template <typename S, typename T>
  bool
  op_can_choose_non_starable(const algebra::SemiringBase<S>& set, SELECTOR(T));

  /// Returns a random starable element in the set.
  template <typename S, typename T>
  Element<S, T>
  op_choose_starable(const algebra::SemiringBase<S>& set, SELECTOR(T));

  /// Returns a random non-starable element in the set.
  template <typename S, typename T>
  Element<S, T>
  op_choose_non_starable(const algebra::SemiringBase<S>& set, SELECTOR(T));


  template <typename S, typename T>
  bool
  op_parse(const algebra::SemiringBase<S>&, T& w,
	const std::string&,
	typename std::string::const_iterator&);

  template <typename Self, typename T>
  bool op_starable(const algebra::SemiringBase<Self>& s, const T& v);

  template <typename Self, typename T>
  void op_in_star(const algebra::SemiringBase<Self>& s, T& v);

  template <typename Self, typename T>
  T op_default(SELECTOR(algebra::SemiringBase<Self>), SELECTOR(T));

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/concept/semiring_base.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_CONCEPT_SEMIRING_BASE_HH
