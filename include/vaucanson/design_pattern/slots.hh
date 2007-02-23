// slots.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_DESIGN_PATTERN_SLOTS_HH
# define VCSN_DESIGN_PATTERN_SLOTS_HH

/** @addtogroup design_pattern *//** @{ */
/**
 * @file slots.hh
 *
 * Declaration of set attribute slot for @c Element.
 */
/** @} */

# include <vaucanson/design_pattern/predecls.hh>

namespace vcsn {

  /** @addtogroup design_pattern *//**@{*/

  /*------------------------------.
  | Basic class for SetSlot below |
  `------------------------------*/

  /**
   * Base class for @c SetSlot
   *
   * This class is responsible for holding a reference to the
   * structural element in each @c Element instance, by means of its
   * @c set_ attribute.
   *
   * This version (parameter @c dynamic is @c false) is used when the
   * structural element is static, i.e. does not require a
   * S.E. instance reference in all related @c Element instance
   * objects: all its properties are carried by its type.
   *
   * Because this version has actually no attribute, it should take no
   * memory space in each @c SetSlot (then @c Element) instance to
   * which it is linked.
   *
   * @see
   *   - @ref dyn_set_slot_attribute "SetSlotAttribute\<S,true\>"
   *   - @c SetSlot
   *   - @c Element
   */
  template<typename S, bool dynamic /* default: false */>
  struct SetSlotAttribute
  {
    //@{
    /// Trivial constructor.
    SetSlotAttribute();
    SetSlotAttribute(const SetSlotAttribute& other);
    SetSlotAttribute(const S& other);
    //@}

    /**
     * Access to the instance of the structural element.
     *
     * Because this version of the class pertains to static S.E.'s,
     * this accessor returns a NULL reference, most likely
     * inappropriate for any other form of dereferencing other than
     * accessing methods of the S.E. (which do not use the reference
     * anyway).
     */
    const S&	_structure_get() const;

    /**
     * @name Methods to link the Slot
     *
     * Because this  version of the  class pertains to  static S.E.'s,
     * those methods  actually do  nothing and calls  to it  should be
     * optimized away.
     */
    //@{

    /// Link a @c SetSlot to another.
    void	_structure_assign(const SetSlotAttribute& other);

    /// Link a @c SetSlot to a structural element.
    void	_structure_attach(const S& other);
    //@}

    /**
     * Whether the current set slot is linked to a structural element.
     *
     * This version always returns @c true.
     */
    bool	_structure_bound() const;
  };

  /**
   * Base class for @c SetSlot, specializing @c SetSlotAttribute
   *
   * @anchor dyn_set_slot_attribute
   * This class is a specialization of @c SetSlotAttribute used
   * when the structural element is dynamic, i.e. requires a
   * S.E. instance reference in all related @c Element instance objects.
   *
   * @see @c SetSlotAttribute.
   */
  template<typename S>
  struct SetSlotAttribute<S, true>
  {
    /// Default constructor. Initialize with a NULL reference.
    SetSlotAttribute();

    /**
     * Copy constructor.
     *
     * Create a structural element reference
     * by copying from the @c other attribute.
     */
    SetSlotAttribute(const SetSlotAttribute& other);

    /**
     * Foreign copy constructor.
     *
     * Create a structural element reference
     * by copying from a reference to a S.E. instance defined elsewhere.
     *
     * @bug
     *   For a number of reasons (see the mailing list), this constructor
     *   creates a fresh copy on the heap which is never deallocated.
     *
     * @bug
     *   Make a better self-contained description of the bug.
     */
    SetSlotAttribute(const S& other);

    /// Retrieve the structural element reference from the attribute.
    const S&	_structure_get() const;

    //@{
    /**
     * Update the reference in the @c Slot.
     *
     * Update the S.E. reference in the attribute with
     * the reference given as argument.
     */
    void	_structure_assign(const SetSlotAttribute& other);
    void	_structure_attach(const S& s);
    //@}

    /**
     * Whether the reference to the structural element is valid or not (NULL).
     */
    bool	_structure_bound() const;

  protected:
    const S*	s_; ///< The actual reference to a structural element.
  };


  /*------------------------------------.
  | Set attribute for the Element class |
  `------------------------------------*/

  /** Type of the @c set_ attribute of the @c Element class.
   *
   * Derives from @c SetSlotAttribute, a reference to a
   * structural element to which an @c Element is related.
   *
   * The actual implementation of @c SetSlot\<S\>, for a given
   * structural element @c S, depends on the value of @c
   * dynamic_traits\<S\>::ret, which chooses which version of @c
   * SetSlotAttribute to inherit from.
   *
   * Additionnally, the class can be meta-tagged when multiple
   * inheritance for the same structural element @c S is needed.
   * This meta-tag (second template argument) makes the type
   * unique w.r.t. the tag type.
   *
   * @see
   *  - @c SetSlotAttribute
   *  - @c dynamic_traits
   *  - @c Element
   */
  template<typename S, typename Tag>
  struct SetSlot : SetSlotAttribute<S, dynamic_traits<S>::ret>
  {
    typedef Tag tag_type;

    //@{
    /**
     * @brief Trivial constructor. Calls the inherited constructor from
     *        @c SetSlotAttribute.
     */
    SetSlot();
    SetSlot(const SetSlot& other);
    SetSlot(const S& other);
    //@}
  };

  /** @} */

}

#  include <vaucanson/design_pattern/slots.hxx>

#endif // ! VCSN_DESIGN_PATTERN_SLOTS_HH
