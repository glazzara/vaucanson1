// sparse_interval.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_SPARSE_INTERVAL_HH
# define VCSN_MISC_SPARSE_INTERVAL_HH

/**
 * @file   misc/sparse_interval.hh
 * @brief  Sparse interval and iterators.
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

    /// SparseIterator is an iterator over range except some points.
    template <class Integer, class ExcludedContainer>
    class SparseIterator
    {
      public:
	typedef Integer		  integer_t;
	typedef ExcludedContainer excluded_container_t;

	SparseIterator (integer_t, const excluded_container_t&);

	SparseIterator& operator++ ();
	SparseIterator	operator++ (int);
	SparseIterator& operator-- ();
	SparseIterator	operator-- (int);
	integer_t	operator* ();
	bool		operator!= (const SparseIterator&);
	bool		operator== (const SparseIterator&);
	SparseIterator& operator= (const SparseIterator&);

      private:
	const excluded_container_t*	excluded_;
	integer_t			integer_;
    };

    /** @} */

  } // misc
} // vcsn

namespace std
{

  template <class Integer, class ExcludedContainer>
  struct iterator_traits<vcsn::misc::SparseIterator
			 <Integer, ExcludedContainer> >
  {
      typedef input_iterator_tag iterator_category;
      typedef Integer		   value_type;
      typedef int		   difference_type;
      typedef int*		   pointer;
      typedef int&		   reference;
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
     */
    template <class Integer, class ExcludedContainer>
    class SparseInterval
    {
      public:
	typedef Integer		integer_t;
	typedef ExcludedContainer	excluded_container_t;
	typedef SparseIterator<integer_t, excluded_container_t> iterator;

	SparseInterval (integer_t, integer_t, const excluded_container_t&);
	SparseInterval (const SparseInterval&);

	iterator begin () const;
	iterator end () const;
	unsigned size () const;
	integer_t max () const;
	std::string to_string () const;

      private:
	const excluded_container_t&	excluded_;
	integer_t			from_;
	integer_t			to_;
    };


    /** @} */

  } // misc
} // vcsn


#  include <vaucanson/misc/sparse_interval.hxx>


#endif // ! VCSN_MISC_SPARSE_INTERVAL_HH
