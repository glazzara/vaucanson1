// boost_support.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_SUPPORT_HH
# define VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_SUPPORT_HH

# include <vaucanson/misc/support.hh>
# include <vaucanson/automata/implementation/boostg/initial_container.hh>

namespace vcsn
{
  namespace misc
  {

    template <>
    class SupportIterator<std::vector<handler<state_h, unsigned int*> > >
    {
      public:
	typedef handler<state_h, unsigned int*>		    data_type;
	typedef std::vector<data_type>			    container_t;
	typedef container_t::const_iterator		    vector_iterator;
	typedef SupportIterator<container_t>		    self_t;

	typedef vector_iterator::iterator_category	    iterator_category;
	typedef vector_iterator::difference_type	    difference_type;
	typedef data_type				    value_type;
	typedef data_type*				    pointer;
	typedef data_type&				    reference;

	SupportIterator () {}
	SupportIterator (const container_t* c, int i);

	data_type operator* () const;
	self_t&	 operator++ ();
	self_t&	 operator-- ();
	self_t	 operator++ (int);
	bool	 operator!= (const SupportIterator&) const;
	bool	 operator== (const SupportIterator&) const;

      private:
	int		    current_;
	size_t		    container_size_;
	const container_t*  container_;
    };

    /// Support<vector<T> > is a const adapter of std::vector to container.
    template <>
    class Support<std::vector<handler<state_h, unsigned*> > >
    {
      public:
	typedef handler<state_h, unsigned*>		 handler_t;
	typedef SupportIterator<std::vector<handler_t> > iterator;
	typedef iterator				 const_iterator;
	/// The type of the values.
	typedef std::vector<handler_t>::value_type	 value_type;

	Support (const std::vector<handler_t>&);

	const_iterator begin () const;
	const_iterator end () const;
	unsigned size () const;

	// Find the element associated to \a k.
	iterator find (const handler_t& k) const;

	/// Whether it's empty.
	bool empty () const;

	handler_t back () const;
      private:
	const std::vector<handler_t>&	m_;
    };

  }
}

/// Declaring the traits for SupportIterator, according to the STL.
namespace std
{
  template <>
    struct iterator_traits<vcsn::misc::SupportIterator<std::vector<vcsn::handler<vcsn::state_h, unsigned int*> > > >
    {
      typedef input_iterator_tag  iterator_category;
      typedef unsigned int*	  value_type;
      typedef int		  difference_type;
      typedef int*		  pointer;
      typedef int&		  reference;
    };
} // std


namespace vcsn
{
  namespace misc
  {
    template <typename U, typename HState>
    class SupportIterator<vcsn::boostg::InitialContainer<U, HState> >
    {
      public:
	typedef typename vcsn::boostg::InitialContainer<U, HState>::Type	container_t;
	typedef typename container_t::key_type			key_type;
	typedef typename container_t::const_iterator		container_iterator;
	typedef SupportIterator<vcsn::boostg::InitialContainer<U, HState> >	self_t;

	typedef typename container_iterator::iterator_category	iterator_category;
	typedef typename container_iterator::difference_type	difference_type;
	typedef key_type					value_type;
	typedef key_type*					pointer;
	typedef key_type&					reference;

	SupportIterator () {}
	SupportIterator (const container_t* c, container_iterator);

	key_type  operator* () const;
	self_t&	 operator++ ();
	self_t&	 operator-- ();
	self_t	 operator++ (int);
	bool	 operator!= (const SupportIterator&) const;
	bool	 operator== (const SupportIterator&) const;


      private:
	container_iterator  i_;
	container_iterator  next_;
	const container_t*  container_;
    };


    /// Support<InitialContainer<U, T> > is a const adapter of InitialContainer to container.
    template <typename  U, typename HState>
    class Support<vcsn::boostg::InitialContainer<U, HState> >
    {
      public:
	typedef typename vcsn::boostg::InitialContainer<U, HState>::Type container_t;
	typedef SupportIterator<vcsn::boostg::InitialContainer<U, HState> > iterator;
	typedef SupportIterator<vcsn::boostg::InitialContainer<U, HState> > const_iterator;

	Support (const container_t&);
	Support (const Support&);

	iterator begin () const;
	iterator end () const;
	unsigned size () const;

	// Find the element associated to \a k.
	iterator find (const HState& k) const;

	/// Whether it's empty.
	bool empty () const;

	HState back () const;
      private:
	const container_t&	m_;
    };

  }
}

/// Declaring the traits for SupportIterator, according to the STL.
namespace std
{
  template <class U, class HState>
  struct iterator_traits<vcsn::misc::SupportIterator<typename vcsn::boostg::InitialContainer<U, HState>::Type > >
  {
    typedef input_iterator_tag  iterator_category;
    typedef HState		value_type;
    typedef int			difference_type;
    typedef int*		pointer;
    typedef int&		reference;
  };
} // std

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

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/automata/implementation/boostg/boostg_support.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_SUPPORT_HH

