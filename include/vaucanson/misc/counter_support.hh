// counter_support.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007 The Vaucanson Group.
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
#ifndef VCSN_MISC_COUNTER_SUPPORT_HH
# define VCSN_MISC_COUNTER_SUPPORT_HH

/**
 * @file   misc/counter_support.hh
 * @brief  Stuff to adapt containers.
 *
 */

# include <iterator>
# include <map>
# include <string>

namespace vcsn
{
  namespace misc
  {

    /** @addtogroup misc *//** @{ */

    template <typename HState>
    class CounterSupport;

    /// Iterator over the Support generic class.
    /// @bug is not STL compliant yet.
    template <typename HState>
    class CounterSupportIterator
    {
      public:
	typedef CounterSupportIterator<HState>			 self_t;
	typedef HState hstate_t;

	/*
	 * This is a default constructor. 
	 * WARNING: this constructor instantiates an invalid iterator.
	 * 	    To use an iterator instantiated by this constructor,
	 * 	    you need to initialize it thanks to the '=' operator.
	 *
	 * This constructor is useful whenever you want to use an iterator as
	 * a temporary variable in a loop. For instance:
	 *
	 * for (CounterSupportIterator tmp, it = aut.final().begin(); 
	 * 	it != aut.final().end();)
	 * {
	 *	tmp = it++;
	 *	if (something)
	 *		del_state(*tmp);
	 * }
	 *
	 * In this example, we delete an object in a set we are already iterating on.
	 * So we need to save a copy of the next element before deleting the current one.
	 * Since declaring a temporary variable inside a loop can slow down performances,
	 * it is declared inside the 'for loop' declaration and, in that case, we are really
	 * interested in such a constructor.
	 *
	 */
	CounterSupportIterator () {}
	CounterSupportIterator (unsigned);

	hstate_t operator* () const;
	self_t&	 operator++ ();
	self_t	 operator++ (int);
	bool	 operator!= (const CounterSupportIterator<hstate_t>&) const;
	bool	 operator== (const CounterSupportIterator<hstate_t>&) const;

      private:
	unsigned	i;
    };

    /// Support<map<U, T> > is a const adapter of std::map to container.
    template <typename HState>
    class CounterSupport
    {
      public:
	typedef CounterSupportIterator<HState> iterator;
	typedef CounterSupportIterator<HState> const_iterator;

	CounterSupport ();
	CounterSupport (unsigned);
	CounterSupport (const CounterSupport<HState>&);

	/** Return the one and only element of the support.
	 @pre There is exactly one element in the support.  */
	unsigned operator* () const;

	iterator begin () const;
	iterator end () const;
	unsigned size () const;

	// Find the element associated to \a k.
	iterator find (unsigned k) const;

	/// Whether it's empty.
	bool empty () const;

	unsigned max () const;

      private:
	unsigned	i_;
    };

    /** @} */

  } // misc
} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/misc/counter_support.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_MISC_COUNTER_SUPPORT_HH
