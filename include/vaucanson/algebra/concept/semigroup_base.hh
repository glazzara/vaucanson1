// semigroup_base.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_CONCEPT_SEMIGROUP_BASE_HH
# define VCSN_ALGEBRA_CONCEPT_SEMIGROUP_BASE_HH

# include <vaucanson/design_pattern/design_pattern.hh>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup semigroup *//** @{ */

    /// @brief Empty class used as static information to denotes the
    ///        kind of internal operation of a semigroup. Here: operator*
    struct mul_kind
    {};

    /// @brief Empty class used as static information to denotes the
    ///        kind of internal operation of a semigroup. Here: operator+
    struct add_kind
    {};

    /**
     * @brief @c SemigroupBase is the base class of all structures that
     *        are semigroups.
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
    /// Default constructor is protected since it is an abstract class.
    MetaElement();

    /// Copy constructor is protected since it is an abstract class.
    MetaElement(const MetaElement& other);
  };

  /** @} */
  /** @} */

} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/algebra/concept/semigroup_base.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGEBRA_CONCEPT_SEMIGROUP_BASE_HH
