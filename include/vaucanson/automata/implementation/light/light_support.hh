// light_support.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_LIGHT_LIGHT_SUPPORT_HH
# define VCSN_AUTOMATA_IMPLEMENTATION_LIGHT_LIGHT_SUPPORT_HH


# include <vaucanson/misc/support.hh>
namespace vcsn
{
  namespace misc
  {

    template <typename U>
    class SupportIterator<std::vector<handler<state_h, U> > >
    {
      public:
	typedef handler<state_h, U>				    data_type;
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

	handler<state_h, int> operator* () const;
	self_t&	 operator++ ();
	self_t&	 operator-- ();
	self_t	 operator++ (int);
	bool	 operator!= (const SupportIterator&) const;
	bool	 operator== (const SupportIterator&) const;

      private:
	vector_iterator	i;
    };

  }
}

/// Declaring the traits for SupportIterator, according to the STL.
namespace std
{
  template <class U>
  struct iterator_traits<vcsn::misc::SupportIterator<std::vector<vcsn::handler<vcsn::state_h, U> > > >
  {
    typedef input_iterator_tag  iterator_category;
    typedef U			value_type;
    typedef int			difference_type;
    typedef int*		pointer;
    typedef int&		reference;
  };
} // std

# include <vaucanson/automata/implementation/light/light_support.hxx>

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_LIGHT_LIGHT_SUPPORT_HH

