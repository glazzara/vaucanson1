// deferrer.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_MISC_DEFERRER_HH
# define VCSN_MISC_DEFERRER_HH

/** @addtogroup misc */ /** @{ */
/**
 * @file deferrer.hh
 *
 * Declarations for the Deferrer class.
 *
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 * @see vcsn::misc::Deferrer
 */
/** @} */

namespace vcsn
{
  namespace misc
  {

    /** @addtogroup misc *//** @{ */

# ifndef VCSN_NDEBUG
    enum { deferrer_runtime_checks_default = true };
# else // VCSN_NDEBUG
    enum { deferrer_runtime_checks_default = false };
# endif // ! VCSN_NDEBUG

    /// Helper class for Deferrer.
    /** @{ */
    template <class T, bool B>
    struct DeferrerDebugPart
    {
      protected:
	// Defaults to true.
	DeferrerDebugPart (void* ptr, bool is_valid = false);

	void	 set_valid (bool b);
	T&	 cast (void*);
	const T& cast (const void*) const;

	bool is_valid_;
    };

    template <class T>
    struct DeferrerDebugPart<T, false>
    {
      protected:
	// False version.
	DeferrerDebugPart (void* ptr, bool is_valid = false);
	void	 set_valid (bool b);
	T&	 cast (void*);
	const T& cast (const void*) const;
    };
    /** @} */

    /**
     * This class defers the creation of its template parameter.
     *
     * This  class is designed	to hold	 a instance  of type  T, without
     * initializing  it	 when  the  class  is  created.	  In  fact,  the
     * construction of T  is deferred to a later  time, using operator=.
     * This  may be  usefull  when you	want  to equip	a  class with  a
     * constructor without arguments.
     *
     * Using a Deferrer	 may be dangerous, e.g. when you  make a call to
     * the cast	 operator without  having initialized the  referred type
     * with a call to operator=.
     *
     * Because of that danger, you can optionally enable or disable some
     * runtime	checks by  respectively set  or clear  a  second Boolean
     * template parameter.
     *
     * When  you  compile  without  the	 NDEBUG	 macro,	 this  parameter
     * defaults	 to true  (checks enabled).  Else it  defaults	to false
     * (checks disabled).
     *
     * @author Thomas Claveirole
     */
    template <class T, bool rt_checks = deferrer_runtime_checks_default>
    struct Deferrer : DeferrerDebugPart<T, rt_checks>
    {
	typedef T deferred_type;

	/**
	 * Constructor.
	 *
	 * Please notice that this constructor *do not initialize* the
	 * holded type.
	 *
	 * @see operator=
	 */
	Deferrer ();

	/**
	 * Effectively builds the holded type.
	 *
	 * @warning Calling this operator twice does not call any destructor
	 *		nor overloaded operators = on the first instance which
	 *		was created.
	 */
	Deferrer&
	operator= (const deferred_type&);

	/// Get back the holded type.
	operator T () const;
      protected:
	typedef unsigned char data_t[sizeof (deferred_type)];

	/**
	 * A flat area of memory big enough to hold an instance of deferred_type.
	 *
	 * Using this  kind of trick forces us	to do a lot  of ugly casts
	 * (after all, data_t  is just an array of char),  but as a result
	 * there are no dynamic allocations.
	 */
	data_t data;
    };

    /** @} */
  } // End of namespace misc.
} // End of namespace vcsn.

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/misc/deferrer.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_MISC_DEFERRER_HH
