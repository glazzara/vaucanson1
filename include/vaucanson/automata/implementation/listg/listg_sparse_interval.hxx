// listg_sparse_interval.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_LISTG_LISTG_SPARSE_INTERVAL_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_LISTG_LISTG_SPARSE_INTERVAL_HXX

namespace vcsn
{
  namespace misc
  {
  /*---------------.
  | SparseIterator |
  `---------------*/

    template <class T, class ExcludedContainer>
    SparseIterator<handler<T, unsigned>, ExcludedContainer>::
    SparseIterator (integer_t from,
		    const excluded_container_t& c)
      : excluded_ (&c),
	integer_ (from)
    {}

    template <class T, class ExcludedContainer>
    SparseIterator<handler<T, unsigned>, ExcludedContainer>&
    SparseIterator<handler<T, unsigned>, ExcludedContainer>::operator++ ()
    {
      if (excluded_->size () == 0)
	++integer_;
      else
	do
	  ++integer_;
	while (excluded_->find (handler_t(integer_)) != excluded_->end ());
      return *this;
    }

    template <class T, class ExcludedContainer>
    SparseIterator<handler<T, unsigned>, ExcludedContainer>&
    SparseIterator<handler<T, unsigned>, ExcludedContainer>::operator-- ()
    {
      if (excluded_->size () == 0)
	--integer_;
      else
	do
	  --integer_;
	while (excluded_->find (handler_t(integer_)) != excluded_->end ());
      return *this;
    }

    template <class T, class ExcludedContainer>
    SparseIterator<handler<T, unsigned>, ExcludedContainer>
    SparseIterator<handler<T, unsigned>, ExcludedContainer>::operator++ (int)
    {
      SparseIterator tmp = *this;
      ++*this;
      return tmp;
    }

    template <class T, class ExcludedContainer>
    SparseIterator<handler<T, unsigned>, ExcludedContainer>
    SparseIterator<handler<T, unsigned>, ExcludedContainer>::operator-- (int)
    {
      SparseIterator tmp = *this;
      --*this;
      return tmp;
    }

    template <class T, class ExcludedContainer>
    typename SparseIterator<handler<T, unsigned>, ExcludedContainer>::
    integer_t
    SparseIterator<handler<T, unsigned>, ExcludedContainer>::operator* ()
    {
      return handler_t(integer_);
    }

    template <class T, class ExcludedContainer>
    bool
    SparseIterator<handler<T, unsigned>, ExcludedContainer>
    ::operator!= (const SparseIterator& i) const
    {
      return i.integer_ != integer_;
    }

    template <class T, class ExcludedContainer>
    bool
    SparseIterator<handler<T, unsigned>, ExcludedContainer>
    ::operator== (const SparseIterator& i) const
    {
      return i.integer_ == integer_;
    }

    template <class T, class ExcludedContainer>
    SparseIterator<handler<T, unsigned>, ExcludedContainer>&
    SparseIterator<handler<T, unsigned>, ExcludedContainer>
    ::operator= (const SparseIterator& i)
    {
      integer_ = i.integer_;
      excluded_ = i.excluded_;
      return *this;
    }




  /*-----------------.
  | SparseInterval.  |
  `-----------------*/


    /// SparseInterval is a const adapter of a 3-uple :
    /// (from, begin, excluded).
    /// SparseInterval verifies the container concept.
    template <class T, class ExcludedContainer>
    SparseInterval<handler<T, unsigned>, ExcludedContainer>
    ::SparseInterval (integer_t f, integer_t t, const excluded_container_t& c)
      : excluded_ (c),
	from_ (f),
	to_ (t)
    {
      precondition (from_ <= to_ + 1);
      precondition (excluded_.find (handler_t(to_ + 1)) == excluded_.end ());
      precondition (to_ - from_ + 1 > excluded_.size());
    }

    template <class T, class ExcludedContainer>
    SparseInterval<handler<T, unsigned>, ExcludedContainer>
    ::SparseInterval (const SparseInterval& a)
      : excluded_ (a.excluded_),
	from_ (a.from_),
	to_ (a.to_)
    {
    }

    template <class T, class ExcludedContainer>
    unsigned
    SparseInterval<handler<T, unsigned>, ExcludedContainer>::size () const
    {
      return to_ - from_ + 1 - excluded_.size ();
    }

    template <class T, class ExcludedContainer>
    std::string
    SparseInterval<handler<T, unsigned>, ExcludedContainer>::to_string () const
    {
      std::stringstream s;
      s << "from :" << from_ << " to : " << to_ << " ex:";
      for (typename ExcludedContainer::iterator i = excluded_.begin ();
	   i != excluded_.end ();
	   ++i)
	s << *i << " ";
      return s.str ();
    }

    template <class T, class ExcludedContainer>
    typename SparseInterval<handler<T, unsigned>, ExcludedContainer>::iterator
    SparseInterval<handler<T, unsigned>, ExcludedContainer>::begin () const
    {
      unsigned from = from_;

      if (excluded_.size () != 0)
	while (excluded_.find (handler_t(from)) != excluded_.end ())
	  ++from;
      return iterator (handler_t(from), excluded_);
    }

    template <class T, class ExcludedContainer>
    typename SparseInterval<handler<T, unsigned>, ExcludedContainer>::iterator
    SparseInterval<handler<T, unsigned>, ExcludedContainer>::end () const
    {
      return iterator (handler_t(to_ + 1), excluded_);
    }

    template <class T, class ExcludedContainer>
    typename SparseInterval<handler<T, unsigned>, ExcludedContainer>::handler_t
    SparseInterval<handler<T, unsigned>, ExcludedContainer>::back () const
    {
      unsigned to = to_;

      if (excluded_.size () != 0)
	while (excluded_.find (handler_t(to)) != excluded_.end ())
	  --to;
      return *(iterator (handler_t(to), excluded_));
    }


  } // misc
} // vcsn

#endif // ! VCSN_MISC_SPARSE_INTERVAL_HXX
