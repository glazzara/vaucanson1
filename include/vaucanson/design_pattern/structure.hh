// structure.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_FUNDAMENTAL_STRUCTURE_HH
# define VCSN_FUNDAMENTAL_STRUCTURE_HH

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
   * <ul>
   *   <li> static inheritance facilities,
   *   <li> the concept of compatibility between elements and a 
   *     structural element considered as a set (through the 
   *     @c contains method),
   *   <li> a @c choose method to pick randomly @c Element instances.
   * </ul>
   */
  template<typename S>
  struct Structure : utility::unique::unifiable
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

    /** @{ */
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


  template<typename S>
  bool operator!=(const vcsn::Structure<S>& a,
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

  /*-----------------------------.
  | virtual_types<Structure<S> > |
  `-----------------------------*/

  /// Specialization of @c virtual_types for @c Structure.
  template<typename S>
  struct virtual_types<Structure<S> >
  { };

  /** @} */   

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/design_pattern/structure.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_FUNDAMENTAL_STRUCTURE_HH
