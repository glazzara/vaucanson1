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
# include <vector>
# include <vaucanson/automata/concept/handlers.hh>


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

	/*
	 * This is a default constructor.
	 * WARNING: this constructor instantiates an invalid iterator.
	 *	    To use an iterator instantiated by this constructor,
	 *	    you need to initialize it thanks to the '=' operator.
	 *
	 * This constructor is useful whenever you want to use an iterator as
	 * a temporary variable in a loop. For instance:
	 *
	 * for (SupportIterator tmp, it = aut.final().begin();
	 *	it != aut.final().end();)
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
	SupportIterator () {}
	SupportIterator (map_iterator);

	key_type operator* () const;
	self_t&	 operator++ ();
	self_t	 operator++ (int);
	bool	 operator!= (const SupportIterator&) const;
	bool	 operator== (const SupportIterator&) const;

      private:
	map_iterator	i;
    };

    template <typename T, typename U>
    class SupportIterator<std::vector<handler<T, U> > >
    {
      public:
	typedef handler<T, U>				    data_type;
	typedef typename std::vector<data_type>::const_iterator
							    vector_iterator;
	typedef SupportIterator<std::vector<data_type> >    self_t;

	typedef typename vector_iterator::iterator_category iterator_category;
	typedef typename vector_iterator::difference_type   difference_type;
	typedef data_type				    value_type;
	typedef data_type*				    pointer;
	typedef data_type&				    reference;

	/*
	 * This is a default constructor.
	 * WARNING: this constructor instantiates an invalid iterator.
	 *	    To use an iterator instantiated by this constructor,
	 *	    you need to initialize it thanks to the '=' operator.
	 *
	 * This constructor is useful whenever you want to use an iterator as
	 * a temporary variable in a loop. For instance:
	 *
	 * for (SupportIterator tmp, it = aut.final().begin();
	 *	it != aut.final().end();)
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
	SupportIterator () {}
	SupportIterator (vector_iterator);

	handler<T, U> operator* () const;
	self_t&	 operator++ ();
	self_t&	 operator-- ();
	self_t	 operator++ (int);
	bool	 operator!= (const SupportIterator&) const;
	bool	 operator== (const SupportIterator&) const;

      private:
	vector_iterator	i;
    };
  } // misc
} // vcsn

/// Declaring the traits for SupportIterator, according to the STL.
namespace std
{
  template <class T, class U>
  struct iterator_traits<vcsn::misc::SupportIterator<std::vector<vcsn::handler<T, U> > > >
  {
    typedef input_iterator_tag  iterator_category;
    typedef U			value_type;
    typedef int			difference_type;
    typedef int*		pointer;
    typedef int&		reference;
  };
} // std

namespace vcsn
{
  namespace misc
  {
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

    /// Support<vector<T> > is a const adapter of std::vector to container.
    template <class T, class U>
    class Support<std::vector<handler<T, U> > >
    {
      public:
	typedef SupportIterator<std::vector<handler<T, U> > > iterator;
	typedef SupportIterator<std::vector<handler<T, U> > > const_iterator;
	/// The type of the values.
	typedef typename std::vector<handler<T, U> >::value_type value_type;

	Support (const std::vector<handler<T, U> >&);
	Support (const Support&);

	/** Return the one and only element of the support.
	 @pre There is exactly one element in the support.  */
	handler<state_h, int> operator* () const;

	iterator begin () const;
	iterator end () const;
	unsigned size () const;

	// Find the element associated to \a k.
	iterator find (const handler<T, U>& k) const;

	/// Whether it's empty.
	bool empty () const;

	int max () const;
      private:
	const std::vector<handler<T, U> >&	m_;
    };
    /** @} */

  } // misc
} // vcsn

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/misc/support.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_MISC_SUPPORT_HH
