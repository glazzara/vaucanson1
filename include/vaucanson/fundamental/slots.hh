// fundamental/slots.hh
//
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

#ifndef FUNDAMENTAL_SLOTS_HH
# define FUNDAMENTAL_SLOTS_HH

# include <vaucanson/misc/selectors.hh>
# include <vaucanson/fundamental/predefs.hh>

/** @file slots.hh
 * Declaration of set and value attribute slots for @c Element
 */

namespace vcsn {

/*! @addtogroup fundamental *//*!@{*/

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
    //! @{
    //! Trivial constructor. 
    SetSlotAttribute();
    SetSlotAttribute(const SetSlotAttribute& other);
    SetSlotAttribute(const S& other);
    //! @}

    /** Access to the instance of the structural element. 
     *
     * Because this version of the class pertains to static S.E.'s,
     * this accessor returns a NULL reference, most likely
     * inappropriate for any other form of dereference other than
     * accessing methods of the S.E. (which do not use the reference
     * anyway).
     */
    const S&	get() const;

    //! This method is being deprecated and should disappear soon.
    S&		get();

    //! @{
    /**
     * Because this version of the class pertains to static S.E.'s,
     * this method actually does nothing and calls to it should be
     * optimized away.
     */

    //! Link a set slot to another.
    void	assign(const SetSlotAttribute& other);

    //! Link a set slot to a structural element.
    void	attach(const S& other);
    //! @}

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
    //! Default constructor. Initialize with a NULL reference.
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

    //! Retrieve the structural element reference from the attribute.
    const S&	get() const;

    //! This method is being deprecated and should disappear soon.
    S&		get();

    //! @{
    /** Update the reference in the slot.
     *
     * This method updates the S.E. reference in the attribute with
     * the reference given as argument.
     */
    void	assign(const SetSlotAttribute& other);
    void	attach(const S& s);
    //! @}

    //! Tell whether the reference to the structural element is valid or not (NULL).
    bool	bound() const;
    
  protected:
    const S*	s_; //!< The actual reference to a structural element.
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
   * MetaSet\<S\>::dynamic_set, which chooses which version of @c
   * SetSlotAttribute to inherit from.
   *
   * @see
   *  - @c SetSlotAttribute
   *  - @c MetaSet
   *  - @c Element
   */
  template<typename S>
  struct SetSlot : SetSlotAttribute<S, MetaSet<S>::dynamic_set>
  {
    //! @{
    //! Trivial constructor. Calls the inherited constructor from 
    //! @c SetSlotAttribute.
    SetSlot();
    SetSlot(const SetSlot& other);
    SetSlot(const S& other);
    //! @}
  };


  /*-------------------------------------.
  | Base class for ValueSlot class below |
  `-------------------------------------*/

  /** @brief Base class for @c ValueSlot
   *
   * This class is responsible for holding value data in each @c
   * Element instance, by means of its @c value_ attribute.
   *
   * This version (parameter @c dynamic is @c false) is used when the
   * value is static, i.e. does not require a value instance in each
   * @c Element instance object : all the value properties are carried
   * by its type.
   * 
   * Because this version has actually no attribute, it should take no
   * memory space in each @c ValueSlot (then @c Element) instance to
   * which it is linked.
   * 
   * @see 
   *   - @ref dyn_val_slot_attribute "ValueSlotAttribute\<S,true\>"
   *   - @c ValueSlot
   *   - @c Element
   */
  template<typename T, bool dynamic>
  struct ValueSlotAttribute
  {
    //! @{
    //! Trivial constructor.
    ValueSlotAttribute();
    ValueSlotAttribute(const T& data);
    ValueSlotAttribute(const ValueSlotAttribute& other);
    //! @}

    //! @{
    //! Accessor to value data.
    //! Because this version of the class designates static values,
    //! there is no data to reference and therefore this accessor returns
    //! a NULL reference.
    const T&	get() const;
    T&		get();
    //! @}

    //! Assignment for another value slot
    void	assign(const ValueSlotAttribute& other);
  };

  /** @brief Base class for @c ValueSlot, specializing @c ValueSlotAttribute
   *
   * @anchor dyn_val_slot_attribute This class is a specialization of
   * @c ValueSlotAttribute used when when the value is dynamic,
   * i.e. requires distinct value data in all @c Element instance
   * objects.
   *
   * @pre 
   *   - The data type @c T must be default constructible if the
   *   default constructor of this class is used.
   *   - The data type @c T must be copy constructible if the copy
   *   constructor of this class is used.
   *   - The data type @c T must be assignable if the @c assign()
   *   method is used.
   *
   * @see @c ValueSlotAttribute.
   */
  template<typename T>
  struct ValueSlotAttribute<T, true>
  {
    //! @{
    //! Trivial constructor. 
    //! It copies data with the data type's default constructor.
    ValueSlotAttribute();
    ValueSlotAttribute(const T& data);
    ValueSlotAttribute(const ValueSlotAttribute& other);
    //! @}

    //! @{
    //! Accessor to value data.
    T&		get();
    const T&	get() const;
    //! @}

    //! Assignment from another value slot.
    void	assign(const ValueSlotAttribute& other);

  protected:
    T data_; //!< The actual value data.
  };

  /*--------------------------------------.
  | Value attribute for the Element class |
  `--------------------------------------*/

  /** Type of the @c value_ attribute of the @c Element class
   *
   * This class derives from @c ValueSlotAttribute, the class holding
   * the value data of any @c Element object.
   *
   * The actual implementation of @c ValueSlot\<S,T\>, for a given
   * structural element @c S and a value type @c T, depends on the
   * value of @c MetaElement\<S,T\>::dynamic_values, which chooses
   * which version of @c ValueSlotAttribute to inherit from.
   *
   * @see
   *  - @c ValueSlotAttribute
   *  - @c MetaElement
   *  - @c Element
   */
  template<typename S, typename T>
  struct ValueSlot : 
    ValueSlotAttribute<T, MetaElement<S, T>::dynamic_values>
  {
    //! @{
    //! Trivial constructor. Calls the inherited constructor from @c ValueSlotAttribute.
    ValueSlot();
    ValueSlot(const ValueSlot& other);
    ValueSlot(const T& other);
    //! @}

    //! This operator is being deprecated and will disappear soon.
    operator const T& () const;
  };

  //! @}

}

/*----------------------------.
| comparison between SetSlots |
`----------------------------*/
/*! @addtogroup fundamental *//*! @{ */
//! @{
//! Compare two instances of @c SetSlotAttribute. 
//! Used to compare instances of @c SetSlot.
template<typename S>
static inline
bool operator==(const vcsn::SetSlotAttribute<S, true>& a,
		const vcsn::SetSlotAttribute<S, true>& b);

template<typename S>
static inline
bool operator==(const vcsn::SetSlotAttribute<S, false>& a,
		const vcsn::SetSlotAttribute<S, false>& b);

template<typename S>
static inline
bool operator!=(const vcsn::SetSlotAttribute<S, true>& a,
		const vcsn::SetSlotAttribute<S, true>& b);

template<typename S>
static inline
bool operator!=(const vcsn::SetSlotAttribute<S, false>& a,
		const vcsn::SetSlotAttribute<S, false>& b);
//! @}
//! @}

/*---------------------------------------.
| internal comparison between ValueSlots |
`---------------------------------------*/
namespace vcsn
{
  namespace internal
  {

    enum comp_kind { eq, neq, lt, gt, le, ge };
    
    template<typename S1, typename S2,
	     typename T1, typename T2, 
	     comp_kind e, bool dynamic /* default false */,
	     bool default_ret>
    struct op
    {
      static bool do_comp(const T1& v1, const T2& v2)
      { 
	return default_ret; 
      }
    };

#define TRIV_OP(Name, Rel)				\
    template<typename S, typename T, bool b>		\
    struct op<S, S, T, T, Name, true, b>		\
    {							\
      static bool do_comp(const T& v1, const T& v2)	\
      { return Rel; }					\
    };

    TRIV_OP(eq, v1 == v2);
    TRIV_OP(neq, !(v1 == v2));
    TRIV_OP(lt, v1 < v2);
    TRIV_OP(gt, v2 < v1);
    TRIV_OP(le, !(v2 < v1));
    TRIV_OP(ge, !(v1 < v2));

#undef TRIV_OP
#define INTER_OP(Name, Op, Rel1, Rel2)				\
    template<typename S, typename T, typename U, bool b>	\
    struct op<S, S, T, U, Name, true, b>			\
    {								\
      static bool do_comp(const T& v1, const U& v2)		\
      { return Op(SELECT(S), Rel1, Rel2); }			\
    };
    
    INTER_OP(eq, op_eq, v1, v2)
    INTER_OP(neq, !op_eq, v1, v2)
    INTER_OP(lt, op_lt, v1, v2)
    INTER_OP(gt, op_lt, v2, v1)
    INTER_OP(ge, !op_lt, v1, v2)
    INTER_OP(le, !op_lt, v2, v1)
#undef INTER_OP

    struct toto {};

#define FOREIGN_OP(Name, Op, X1, X2, Rel1, Rel2)			\
    template<typename S1, typename S2, typename T, typename U, bool b>	\
    struct op<S1, S2, T, U, Name, true, b>				\
    {									\
      static bool do_comp(const T& v1, const U& v2)			\
      { return Op(SELECT(X1), SELECT(X2), Rel1, Rel2); }		\
    }

    FOREIGN_OP(eq, op_eq, S1, S2, v1, v2);
    FOREIGN_OP(neq, !op_eq, S1, S2, v1, v2);
    FOREIGN_OP(lt, op_lt, S1, S2, v1, v2);
    FOREIGN_OP(gt, op_lt, S2, S1, v2, v1);
    FOREIGN_OP(ge, !op_lt, S1, S2, v1, v2);
    FOREIGN_OP(le, !op_lt, S2, S1, v2, v1);

#undef FOREIGN_OP

  } // internal

} // vcsn

namespace vcsn {

#define CALL_OP(Op, Name, Deflt)				\
template<typename S1, typename T1, typename S2, typename T2>	\
static inline							\
bool operator Op(const vcsn::ValueSlot<S1, T1>& v1,	\
		 const vcsn::ValueSlot<S2, T2>& v2)	\
{ return v1.get() == v2.get(); }                         \

CALL_OP(==, vcsn::internal::eq, true);
CALL_OP(!=, vcsn::internal::neq, false);
CALL_OP(<, vcsn::internal::lt, false);
CALL_OP(>, vcsn::internal::gt, false);
CALL_OP(<=, vcsn::internal::le, true);
CALL_OP(>=, vcsn::internal::ge, true);

#undef CALL_OP

} // vcsn

# include <vaucanson/fundamental/slots.hxx>

#endif // FUNDAMENTAL_SLOTS_HH
