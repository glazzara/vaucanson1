// traits.hh
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

#ifndef INTERNAL_TRAITS_HH
# define INTERNAL_TRAITS_HH

/** \file traits.hh
 * Forward declaration for internal template helpers.
 */

//! Namespace of the Vaucanson library.
namespace vcsn {

  /*! \addtogroup fundamental *//*! @{ */

  /** \brief Namespace for all type-to-type meta-functions.
   *
   * This namespace holds definitions for out-of-class type
   * declarations and definitions pertaining to (beside others) the
   * static inheritance design pattern.
   * 
   * \relates vcsn
   */
  namespace traits {

    /** \brief Holder of virtual types for a class in a static hierarchy.
     *
     * The general definition is empty, and is specialised for each class
     * in static hierarichies that define new virtual types.
     *
     * For any class B which inherits from A in a static hierarchy, 
     * the specialization @c virtual_types\<B\> must inherit from @c
     * virtual_types\<A\>.
     */
    template<typename T>
    struct virtual_types {};

    /** \brief Special type used to declare yet undefined virtual types. 
     *
     * Use this struct to declare abstract virtual types in static
     * hierarchies.
     */
    struct undefined_type {};

  } // traits

  //! @}

} // vcsn 


#endif // INTERNAL_TRAITS_HH
