// monoid_base.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
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
     * @c MonoidBase is the base class of all structures that are monoids.
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
      /// Default constructor is protected since it is an abstract class.
      MonoidBase();

      /// Copy constructor is protected since it is an abstract class.
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
    /// Default constructor is protected since it is an abstract class.
    MetaElement();

    /// Copy constructor is protected since it is an abstract class.
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
