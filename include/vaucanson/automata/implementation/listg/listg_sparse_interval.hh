// listg_sparse_interval.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_LISTG_LISTG_SPARSE_INTERVAL_HH
# define VCSN_AUTOMATA_IMPLEMENTATION_LISTG_LISTG_SPARSE_INTERVAL_HH

/**
 * @file   automata/implementation/listg/listg_sparse_interval.hh
 * @brief  Sparse interval and iterators specializations.
 *
 */

# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/misc/sparse_interval.hh>

namespace vcsn
{
  namespace misc
  {

    /** @addtogroup misc *//** @{ */

    /// SparseIterator is an iterator over range except some points.
    template <class T, class ExcludedContainer>
    class SparseIterator<vcsn::handler<T, unsigned>, ExcludedContainer>
    {
      public:
	typedef vcsn::handler<T, unsigned>	handler_t;
	typedef handler_t		integer_t;
	typedef ExcludedContainer	excluded_container_t;
	typedef typename excluded_container_t::const_iterator  iterator_t;

	SparseIterator (integer_t, const excluded_container_t&);

	SparseIterator& operator++ ();
	SparseIterator	operator++ (int);
	SparseIterator& operator-- ();
	SparseIterator	operator-- (int);
	integer_t	operator* ();
	bool		operator!= (const SparseIterator&) const;
	bool		operator== (const SparseIterator&) const;
	SparseIterator& operator= (const SparseIterator&);

      private:
	const excluded_container_t* excluded_;
	unsigned		    integer_;
    };

    /** @} */

  } // misc
} // vcsn

namespace std
{

  template <class T, class ExcludedContainer>
  struct iterator_traits<vcsn::misc::SparseIterator
			 <vcsn::handler<T, unsigned>, ExcludedContainer> >
  {
      typedef input_iterator_tag		iterator_category;
      typedef vcsn::handler<T, unsigned>		value_type;
      typedef int				difference_type;
      typedef int*				pointer;
      typedef int&				reference;
  };

} // std

namespace vcsn
{
  namespace misc
  {

    /** @addtogroup misc *//** @{ */

    /**
     *
     * @brief Container over a sparse integer range.
     *
     * SparseInterval is a const adapter of a 3-uple :
     *	(from, begin, excluded).
     *	SparseInterval verifies the container concept.
     *
     * Important note : the excluded container _MUST_ be an ordered
     *			set. The element with the highest id must be at
     *			at the end.
     *
     * WARNING: always iterate over this container using the iterators.
     */
    template <class T, class ExcludedContainer>
    class SparseInterval<vcsn::handler<T, unsigned>, ExcludedContainer>
    {
      public:
	typedef vcsn::handler<T, unsigned>	handler_t;
	typedef handler_t		integer_t;
	typedef ExcludedContainer	excluded_container_t;
	typedef SparseIterator<integer_t, excluded_container_t> iterator;
	typedef SparseIterator<integer_t, excluded_container_t> const_iterator;

	SparseInterval (integer_t, integer_t, const excluded_container_t&);
	SparseInterval (const SparseInterval&);

	iterator begin () const;
	iterator end () const;
	//Return the number of elements which are _NOT_ excluded.
	unsigned size () const;
	std::string to_string () const;
	//Return the handler_t with the highest ID.
	handler_t back() const;

      private:
	const excluded_container_t&	excluded_;
	unsigned			from_;
	unsigned			to_;
    };


    /** @} */

  } // misc
} // vcsn


# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/implementation/listg/listg_sparse_interval.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_LISTG_LISTG_SPARSE_INTERVAL_HH
