// fundamental/element.hh
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

#ifndef VCSN_FUNDAMENTAL_ELEMENT_HH
# define VCSN_FUNDAMENTAL_ELEMENT_HH

/** @addtogroup fundamental *//** @{ */
/**
 * @file element.hh
 * @brief Declaration of @c Element
 */
/** @} */

# include <vaucanson/fundamental/predecls.hh>
# include <vaucanson/fundamental/meta_element_root.hh>
# include <vaucanson/fundamental/element_ops.hh>
# include <vaucanson/fundamental/default_ops.hh>
# include <vaucanson/fundamental/slots.hh>

namespace vcsn {

  /** @addtogroup fundamental *//** @{ */

  /*--------.
  | Element |
  `--------*/

  /** Glue class between structural elements and implementation values.
   *
   * @c Element is the center of the design pattern used in Vaucanson
   * to have an orthogonal construction of object from two different
   * viewpoints:
   *
   * <ul>
   * <li> Algebraic/Theorical one, from a hierarchy of sets,
   * <li> Implementation and computations.
   * </ul>
   *
   * @c Element proposes a lot of different constructors so as to
   * allow the largest set of type conversions. Calling foreign
   * constructors assume that there exist compatible "op_convert"
   * functions.
   *
   * @see
   * <ul>
   * <li>@c MetaElement
   * <li>@c Structure
   * <li>@c SetSlot
   * </ul>
   */
  template<typename S, typename T>
  class Element : public MetaElement<S, T>
  {
  public:
    /// Structure type for structural elements.
    typedef S	      set_t;

    /// Implementation type for values.
    typedef T	      value_t;

    /// Attribute indicating whether the structural element has dynamic data.
    static const bool dynamic    = dynamic_traits<S>::ret;
      
    /*--------------------.
    | Default constructor |
    `--------------------*/

    /** Default constructor.
     * Note that using this constructor when the structural element is dynamic,
     * leaves the constructed @c Element instance in an incomplete state, 
     * i.e. not linked to any structural element.
     */
    Element();

    /*--------------------------.
    | Constructors from Element |
    `--------------------------*/

    /// Copy constructor from @c Element instances of exactly the same type.
    Element(const Element& other);

    /// Copy constructor from @c Element instances with different value type.
    template<typename U>
    Element(const Element<S, U>& other);

    /** Copy constructor from foreign @c Element instances.
     * Note that using this constructor when the structural element is dynamic,
     * leaves the constructed @c Element instance in an incomplete state, 
     * i.e. not linked to any structural element.
     */
    template<typename OtherS, typename U>
    Element(const Element<OtherS, U>& other);

    /*-------------------------.
    | Constructors from values |
    `-------------------------*/

    /** @{ */
    /** Copy constructor from anonymous values.
     * Note that using this constructor when the structural element is dynamic,
     * leaves the constructed @c Element instance in an incomplete state, 
     * i.e. not linked to any structural element.
     */
    Element(const T& other);

    template<typename U>
    Element(const U& other);
    /** @} */

    /*-------------------------------------------------.
    | Constructors from structural elements and values |
    `-------------------------------------------------*/

    /** Default constructor with the structural element specified.
     * This constructor invokes the default constructor of the
     * implementation value type.
     */
    explicit Element(const S& set);

    /// Explicit construction from structural element and value.
    Element(const S& set, const T& other); 

    /// Explicit construction from structural element and foreign value.
    template<typename U> Element(const S& set, const U& other);

    /// Explicit construction with foreign @c Element conversion.
    template<typename OtherS, typename U>
    Element(const S& set, const Element<OtherS, U>& other);

    /*-----------.
    | Assignment |
    `-----------*/

    /// Assignment from the same @c Element type.
    Element& operator=(const Element& other);

    /// Assignment from other implementation value types.
    template<typename U>
    Element& operator=(const Element<S, U>& other);

    /// Assignment from foreign @c Element types.
    template<typename OtherS, typename U>
    Element& operator=(const Element<OtherS, U>& other);

    /// Assignment from foreign implementation types.
    template<typename U>
    Element& operator=(const U& other);

    /*--------------------------.
    | Design pattern facilities |
    `--------------------------*/

    /// Accessor to the structural element.
    const S&	set() const;

    /// Post-construction link to a structural element.
    void	attach(const S& set);

    /// Tell whether the @c Element instance is linked or not.
    bool	bound() const;

    /** @{ */
    /// Accessor to the value data.
    T&		value();
    const T&	value() const;
    /** @} */

  private : 
    SetSlot<S>		set_;
    T	value_;
  };

  //! @}

} // vcsn

#include <vaucanson/fundamental/element.hxx>

#endif // VCSN_FUNDAMENTAL_ELEMENT_HH
