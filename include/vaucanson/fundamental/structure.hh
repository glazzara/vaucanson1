// structure.hh
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

#ifndef VCSN_FUNDAMENTAL_STRUCTURE_HH
# define VCSN_FUNDAMENTAL_STRUCTURE_HH

/** @addtogroup fundamental *//** @{ */
/**
 * @file structure.hh
 * @brief Definition of class @c Structure, the root of all structural element types
 */
/** @} */

# include <vaucanson/misc/selectors.hh>
# include <vaucanson/fundamental/predecls.hh>

namespace vcsn {

  /** @addtogroup fundamental *//** @{ */

  /*-------------.
  | Structure<S> |
  `-------------*/

  /** Base class for the hierarchy of structural element types.
   * It provides:
   * <ul>
   *   <li> static inheritance facilities,
   *   <li> the concept of compatibility between elements and a 
   *     structural element considered as a set (through the 
   *     @c contains method),
   *   <li> a @c choose method to pick randomly @c Element instances.
   * </ul>
   */
  template<typename S>
  struct Structure
  {
    /// Check if a given element is compatible with the structural element
    template<typename T>
    bool  contains(const Element<S, T>& elt) const;

    /** Specialization of @c containts that always return false.
     * Indeed, elements structured by a particular type are always
     * incompatible with structural elements of another type.
     */
    template<typename OtherS, typename T>
    bool  contains(const Element<OtherS, T>& other) const;

    /// Check if an anonymous value is compatible with a structural element. 
    template<typename T>
    bool  contains(const T& elt_value) const;

    /// Choose randomly an element in the structure.
    template <class T>
    Element<S, T>
    choose(SELECTOR(T)) const;


    /// Exact type of the most derivated type in the hierarchy
    typedef S		self_t;

    /** @{ */
    /** 
     * Accessor to the real type.
     *
     * This accessor is intended to be used by implementations in this
     * class and derivated structures to obtain a reference to the
     * structural element with its most derivated type.
     */
    self_t&        self();
    const self_t&  self() const;
    /** @} */

  protected:

    /** @{ */
    /// Protected constructor for class abstraction
    Structure();
    Structure(const Structure& other);
    /** @} */
  };

  /*--------------------.
  | default comparisons |
  `--------------------*/

  /** The deep equality operator between @c Structure instances.
   * The implementation for @c Structure always return true since
   * there is no dynamic type information attached to @c Structure itself.
   */
  template<typename S>
  bool operator==(const vcsn::Structure<S>& a,
		  const vcsn::Structure<S>& b);


  /*------------------------------.
  | dynamic_traits<Structure<S> > |
  `------------------------------*/

  /**
   * Specialization of @c dynamic_traits for @c Structure.
   * By default, all structural elements have no dynamic type information.
   */
  template<typename S>
  struct dynamic_traits<Structure<S> >
  {
    static const bool ret = false;
  };

  /** @} */   

} // vcsn

# include <vaucanson/fundamental/structure.hxx>

#endif // VCSN_FUNDAMENTAL_STRUCTURE_HH
