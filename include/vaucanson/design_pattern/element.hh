// element.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_DESIGN_PATTERN_ELEMENT_HH
# define VCSN_DESIGN_PATTERN_ELEMENT_HH

/** @addtogroup design_pattern *//** @{ */
/**
 * @file element.hh
 * @brief Declaration of @c Element
 */
/** @} */

# include <vaucanson/design_pattern/predecls.hh>
# include <vaucanson/design_pattern/meta_element_root.hh>
# include <vaucanson/design_pattern/element_ops.hh>
# include <vaucanson/design_pattern/default_ops.hh>
# include <vaucanson/design_pattern/slots.hh>

namespace vcsn {

  /** @addtogroup design_pattern *//** @{ */

  /*--------.
  | Element |
  `--------*/

  /** Glue class between structural elements and implementation values.
   *
   * @c Element is the center of the design pattern used in Vaucanson
   * to have an orthogonal construction of object from two different
   * viewpoints:
   *
   * - Algebraic/Theoretical one, from a hierarchy of structures,
   * - Implementation and computations.
   *
   * @c  Element proposes  a lot  of different  constructors so  as to
   * allow  the  largest structure  of  type  conversions.  Calling  foreign
   * constructors assumes  that there exist  compatible @c op_convert()
   * functions.
   *
   * @see
   *     - @c MetaElement
   *     - @c Structure
   *     - @c SetSlot
   */
  template<typename S, typename T>
  class Element : public MetaElement<S, T>, private SetSlot<S>
  {
  public:
    /// Structure type for structural elements.
    typedef S	      set_t;

    /// Implementation type for values.
    typedef T	      value_t;

    /// Attribute indicating whether Element instances have run-time data.
    static const bool dynamic    = dynamic_traits<S>::ret
                                   || MetaElement<S, T>::dynamic_value;

    /*--------------------.
    | Default constructor |
    `--------------------*/

    /**
     * Default constructor.
     *
     * It is not possible  to use this  contructor when the
     * structural element has dynamic  data. If you absolutely need to
     * do  so,  notice  that  it may  be  dangerous,  and  see
     * misc::Deferrer.
     *
     * @see misc::Deferrer
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

    /**
     * Copy constructor from foreign @c Element instances.
     *
     * Impossible  to use when the structural  element
     * has  dynamic   data  since  it  leaves  it uninitialized.
     */
    template<typename OtherS, typename U>
    Element(const Element<OtherS, U>& other);

    /*-------------------------.
    | Constructors from values |
    `-------------------------*/

    //@{
    /**
     * Copy constructor from anonymous values.
     *
     * Impossible to use when the structural element has dynamic data
     * since it leaves it uninitialized.
     */
    Element(const T& other);

    template<typename U>
    Element(const U& other);
    //@}

    /*-------------------------------------------------.
    | Constructors from structural elements and values |
    `-------------------------------------------------*/

    /**
     * Default constructor with the structural element specified.
     *
     * Invokes the default constructor of the
     * implementation value type.
     */
    explicit Element(const S& structure);

    /// Explicit construction from structural element and value.
    Element(const S& structure, const T& other);

    /// Explicit construction from structural element and foreign value.
    template<typename U> Element(const S& structure, const U& other);

    /// Explicit construction with foreign @c Element conversion.
    template<typename OtherS, typename U>
    Element(const S& structure, const Element<OtherS, U>& other);

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
    const S&	structure() const;

    /// Post-construction link to a structural element.
    void	attach(const S& structure);

    //@{
    /// Accessor to the value data.
    T&		value();
    const T&	value() const;
    //@}

  private :
    T			value_;
  };

  /** @} */

} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/design_pattern/element.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_DESIGN_PATTERN_ELEMENT_HH
