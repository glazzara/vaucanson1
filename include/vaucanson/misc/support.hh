// support.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_SUPPORT_HH
# define VCSN_MISC_SUPPORT_HH

/**
 * @file   misc/support.hh
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

    template <class T>
    class Support;

    /// Iterator over the Support generic class.
    /// @bug is not STL compliant yet.
    template <class C>
    class SupportIterator
    {
      public:
	typedef typename C::key_type		key_type;
	typedef typename C::const_iterator	map_iterator;
	typedef SupportIterator<C>		self_t;

	typedef typename map_iterator::iterator_category iterator_category;
	typedef typename map_iterator::difference_type	 difference_type;
	typedef key_type				 value_type;
	typedef key_type*				 pointer;
	typedef key_type&				 reference;

	SupportIterator (map_iterator);

	key_type operator* () const;
	self_t&	 operator++ ();
	self_t	 operator++ (int);
	bool	 operator!= (const SupportIterator&) const;
	bool	 operator== (const SupportIterator&) const;

      private:
	map_iterator	i;
    };

    /// Support<map<U, T> > is a const adapter of std::map to container.
    template <class U, class T>
    class Support<std::map<U, T> >
    {
      public:
	typedef SupportIterator<std::map<U, T> > iterator;
	typedef SupportIterator<std::map<U, T> > const_iterator;
	/// The type of the values.
	typedef typename std::map<U, T>::value_type value_type;

	Support (const std::map<U, T>&);
	Support (const Support&);

	/** Return the one and only element of the support.
	 @pre There is exactly one element in the support.  */
	value_type operator* () const;

	iterator begin () const;
	iterator end () const;
	unsigned size () const;

	// Find the element associated to \a k.
	iterator find (const U& k) const;

	/// Whether it's empty.
	bool empty () const;

	U max () const;
      private:
	const std::map<U, T>&	m_;
    };

    /** @} */

  } // misc
} // vcsn

# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/misc/support.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_MISC_SUPPORT_HH
