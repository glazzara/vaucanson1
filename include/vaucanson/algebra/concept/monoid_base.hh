// monoid_base.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_MONOID_BASE_HH
# define VCSN_ALGEBRA_CONCEPT_MONOID_BASE_HH

# include <vaucanson/algebra/concept/semigroup_base.hh>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup monoid *//** @{ */

    /*-----------------.
    | MonoidBase<Self> |
    `-----------------*/

    /**
     * @c The base class of all structures that are monoids.
     *
     * Monoid defines identity for semigroups of mul_kind and zero for
     * semigroup of add_kind.
     */
    template<class Self>
    struct MonoidBase : SemigroupBase<Self>
    {
      /// Returns the identity of the monoid (if mul_kind).
      template<typename T>
      Element<Self, T> identity(SELECTOR(T)) const;

      /// Returns the zero of the monoid (if add_kind).
      template<typename T>
      Element<Self, T> zero(SELECTOR(T)) const;

    protected:
      /// Protected since it is an abstract class.
      MonoidBase();

      /// Protected since it is an abstract class.
      MonoidBase(const MonoidBase& other);
    };

    template <class T>
    struct identity_as
    {
      template <class S>
      static
      Element<S, T> of(const S& s);
    };

    template <class T>
    struct zero_as
    {
      template <class S>
      static
      Element<S, T> of(const S& s);
    };

    /** @} */
    /** @} */

  } // algebra

  /** @addtogroup algebra */  /** @{ */
  /** @addtogroup monoid */ /** @{ */

  /*----------------------------------.
  | dynamic_traits<MonoidBase<Self> > |
  `----------------------------------*/

  template<class Self>
  struct dynamic_traits<algebra::MonoidBase<Self> >
    : dynamic_traits<algebra::SemigroupBase<Self> >
  { };

  template<typename S>
  struct virtual_types<algebra::MonoidBase<S> >
    : virtual_types<algebra::SemigroupBase<S> >
  { };

  /*---------------------------------.
  | MetaElement<MonoidBase<Self>, T> |
  `---------------------------------*/

  /// Defines services of element of every monoid.
  template<class Self, typename T>
  struct MetaElement<algebra::MonoidBase<Self>, T>
    : MetaElement<algebra::SemigroupBase<Self>, T>
  {
  protected:
    /// Protected since it is an abstract class.
    MetaElement();

    /// Protected since it is an abstract class.
    MetaElement(const MetaElement& other);
  };

  /** @} */
  /** @} */

  template<typename T, typename Self>
  T op_default(SELECTOR(algebra::MonoidBase<Self>), SELECTOR(T));

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/concept/monoid_base.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_CONCEPT_MONOID_BASE_HH
