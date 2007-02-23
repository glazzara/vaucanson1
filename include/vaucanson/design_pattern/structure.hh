// structure.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_DESIGN_PATTERN_STRUCTURE_HH
# define VCSN_DESIGN_PATTERN_STRUCTURE_HH

/** @addtogroup design_pattern *//** @{ */
/**
 * @file structure.hh
 * @brief Definition of class @c Structure, the root of all structural element types
 */
/** @} */

# include <vaucanson/misc/selectors.hh>
# include <vaucanson/design_pattern/predecls.hh>
# include <vaucanson/misc/unique.hh>

namespace vcsn {

  /** @addtogroup design_pattern *//** @{ */

  /*-------------.
  | Structure<S> |
  `-------------*/

  /** Base class for the hierarchy of structural element types.
   * It provides:
   *
   *   - static inheritance facilities,
   *   - the concept of compatibility between elements and a
   *     structural element considered as a set (through the
   *     @c contains() method),
   *   - a @c choose() method to pick randomly @c Element instances.
   */
  template<typename S>
  struct Structure : misc::unique::unifiable
  {
    /// Check if a given element is compatible with the structural element
    template<typename T>
    bool  contains(const Element<S, T>& elt) const;

    /**
     * Specialization of @c contains that always returns false.
     *
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


    /// Exact type of the most derived type in the hierarchy.
    typedef S		self_t;

    //@{
    /**
     * Accessor to the real type.
     *
     * To be used by implementations in this
     * class and derived structures to obtain a reference to the
     * structural element with its most derived type.
     */
    self_t&        self();
    const self_t&  self() const;
    //@}

  protected:

    /// @name Protected constructor for class abstraction.
    /** @{ */
    Structure();
    Structure(const Structure& other);
    /** @} */
  };

  /*--------------------.
  | default comparisons |
  `--------------------*/

  /** @addtogroup operators *//** @{ */
  /**
   * @name Inequality operator for Structures.
   *
   * Calls equality operator of sub-class.
   *
   */
  /** @{ */

  template<typename S>
  bool operator != (const vcsn::Structure<S>& a,
		    const vcsn::Structure<S>& b);
  /** @} */
  /** @} */

  /*------------------------------.
  | dynamic_traits<Structure<S> > |
  `------------------------------*/

  /**
   * Specialization of @c dynamic_traits for @c Structure.
   *
   * By default, all structural elements have no dynamic type information.
   */
  template<typename S>
  struct dynamic_traits<Structure<S> >
  {
    static const bool ret = false;
  };

  /*-----------------------------.
  | virtual_types<Structure<S> > |
  `-----------------------------*/

  /// Specialization of @c virtual_types for @c Structure.
  template<typename S>
  struct virtual_types<Structure<S> >
  { };

  /** @} */

} // vcsn

#  include <vaucanson/design_pattern/structure.hxx>

#endif // ! VCSN_DESIGN_PATTERN_STRUCTURE_HH
