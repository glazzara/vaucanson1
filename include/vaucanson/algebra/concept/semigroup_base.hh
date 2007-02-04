// semigroup_base.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGEBRA_CONCEPT_SEMIGROUP_BASE_HH
# define VCSN_ALGEBRA_CONCEPT_SEMIGROUP_BASE_HH

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup semigroup *//** @{ */

    /// @brief Empty class used as static information to denote the
    ///        kind of internal operation of a semigroup. Here: operator*.
    struct mul_kind
    {};

    /// @brief Empty class used as static information to denote the
    ///        kind of internal operation of a semigroup. Here: operator+.
    struct add_kind
    {};

    /**
     * @brief Base class of all structures that are semigroups.
     *
     * All derived classes must define type virtual_types<S>::semigroup_kind.
     */
    template<class Self>
    struct SemigroupBase : Structure<Self>
    {
    protected:
      /// Default constructor is protected since it is an abstract class.
      SemigroupBase();

      /// Copy constructor is protected since it is an abstract class.
      SemigroupBase(const SemigroupBase& other);
    };

    /** @} */
    /** @} */

  } // algebra

  /** @addtogroup algebra *//** @{ */
  /** @addtogroup semigroup *//** @{ */

  /*-------------------------------------.
  | dynamic_traits<SemigroupBase<Self> > |
  `-------------------------------------*/

  template<class Self>
  struct dynamic_traits<algebra::SemigroupBase<Self> >
    : dynamic_traits<Structure<Self> >
  { };

  template<typename S>
  struct virtual_types<algebra::SemigroupBase<S> >
    : virtual_types<Structure<S> >
  {
    typedef undefined_type semigroup_kind;
  };


  /*-----------------------------------.
  | MetaElement<SemigroupBase<Self>,T> |
  `-----------------------------------*/

  /// Services of every element of a semigroup.
  template<class Self, typename T>
  struct MetaElement<algebra::SemigroupBase<Self>, T>
    : MetaElement<Structure<Self>, T>
  {
  protected:
    /// Protected since it is an abstract class.
    MetaElement();

    /// Protected since it is an abstract class.
    MetaElement(const MetaElement& other);
  };

  /** @} */
  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/concept/semigroup_base.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_ALGEBRA_CONCEPT_SEMIGROUP_BASE_HH
