// slots.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_FUNDAMENTAL_SLOTS_HH
# define VCSN_FUNDAMENTAL_SLOTS_HH

/** @addtogroup design_pattern *//** @{ */
/** 
 * @file slots.hh
 * @brief Declaration of set attribute slot for @c Element
 */
/** @} */

# include <vaucanson/design_pattern/predecls.hh>

namespace vcsn {

/** @addtogroup design_pattern *//**@{*/

  /*------------------------------.
  | Basic class for SetSlot below |
  `------------------------------*/

  /** @brief Base class for @c SetSlot
   *
   * This class is responsible for holding a reference to the
   * structural element in each @c Element instance, by means of its
   * @c set_ attribute.
   *
   * This version (parameter @c dynamic is @c false) is used when the
   * structural element is static, i.e. does not require a
   * S.E. instance reference in all related @c Element instance
   * objects : all its properties are carried by its type.
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
    /// @{
    /// Trivial constructor. 
    SetSlotAttribute();
    SetSlotAttribute(const SetSlotAttribute& other);
    SetSlotAttribute(const S& other);
    /// @}

    /** Access to the instance of the structural element. 
     *
     * Because this version of the class pertains to static S.E.'s,
     * this accessor returns a NULL reference, most likely
     * inappropriate for any other form of dereference other than
     * accessing methods of the S.E. (which do not use the reference
     * anyway).
     */
    const S&	get() const;

    /// @{
    /**
     * Because this version of the class pertains to static S.E.'s,
     * this method actually does nothing and calls to it should be
     * optimized away.
     */

    /// Link a set slot to another.
    void	assign(const SetSlotAttribute& other);

    /// Link a set slot to a structural element.
    void	attach(const S& other);
    /// @}

    /** Tell whether the current set slot is linked to a structural element or not.
     *
     * In this version this method always returns @c true.
     */
    bool	bound() const;
  };

  /** @brief Base class for @c SetSlot, specializing @c SetSlotAttribute
   *
   * @anchor dyn_set_slot_attribute
   * This class is a specialization of @c SetSlotAttribute used when
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

    /** Copy constructor.
     *
     * This copy constructor creates an structural element reference
     * by copying from the @c other attribute. 
     */
    SetSlotAttribute(const SetSlotAttribute& other);

    /** Foreign copy constructor.
     *
     * This copy constructor creates an structural element reference
     * by copying from a reference to a S.E. instance defined elsewhere.
     *
     * @bug
     *   For a number of reasons (see the mailing list), this constructor
     *   creates a fresh copy on the heap which is never deallocated.
     */
    SetSlotAttribute(const S& other);

    /// Retrieve the structural element reference from the attribute.
    const S&	get() const;

    /// @{
    /** Update the reference in the slot.
     *
     * This method updates the S.E. reference in the attribute with
     * the reference given as argument.
     */
    void	assign(const SetSlotAttribute& other);
    void	attach(const S& s);
    /// @}

    /// Tell whether the reference to the structural element is valid or not (NULL).
    bool	bound() const;
    
  protected:
    const S*	s_; ///< The actual reference to a structural element.
  };


  /*------------------------------------.
  | Set attribute for the Element class |
  `------------------------------------*/

  /** Type of the @c set_ attribute of the @c Element class
   *
   * This class derives from @c SetSlotAttribute, a reference to a
   * structural element to which an @c Element is related.
   *
   * The actual implementation of @c SetSlot\<S\>, for a given
   * structural element @c S, depends on the value of @c
   * dynamic_traits\<S\>::ret, which chooses which version of @c
   * SetSlotAttribute to inherit from.
   *
   * @see
   *  - @c SetSlotAttribute
   *  - @c dynamic_traits
   *  - @c Element
   */
  template<typename S>
  struct SetSlot : SetSlotAttribute<S, dynamic_traits<S>::ret>
  {
    /// @{
    /// Trivial constructor. Calls the inherited constructor from 
    /// @c SetSlotAttribute.
    SetSlot();
    SetSlot(const SetSlot& other);
    SetSlot(const S& other);
    /// @}
  };

  /// @}

}


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/design_pattern/slots.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_FUNDAMENTAL_SLOTS_HH
