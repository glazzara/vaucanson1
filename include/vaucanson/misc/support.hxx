// support.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_MISC_SUPPORT_HXX
# define VCSN_MISC_SUPPORT_HXX

# include <vaucanson/misc/support.hh>
# include <vaucanson/misc/contract.hh>
# include <sstream>

namespace utility {


  /*-------------------*
   | SupportIterator.  |
   *-------------------*/

  template <class C>
  SupportIterator<C>::SupportIterator(map_iterator mp):
    i(mp)
  {}

  template <class C>
  typename SupportIterator<C>::key_type
  SupportIterator<C>::operator*() const
  {
    return i->first;
  }

  template <class C>
  SupportIterator<C>&	SupportIterator<C>::operator++()
  {
    ++i;
    return *this;
  }

  template <class C>
  SupportIterator<C>	SupportIterator<C>::operator++(int)
  {
    SupportIterator<C> tmp = *this;
    ++i;
    return tmp;
  }

  template <class C>
  bool
  SupportIterator<C>::operator!=(const SupportIterator& o) const
  {
    return o.i != i;
  }

  template <class C>
  bool
  SupportIterator<C>::operator == (const SupportIterator& o) const
  {
    return !(*this != o);
  }



  /*-----------*
   | Support.  |
   *-----------*/


  /// support<map<U, T> > is a const adapter of std::map to container.
  template <class U, class T>
  Support<std::map<U, T> >::Support(const Support& s):
    m_(s.m_)
  {
  }

  template <class U, class T>
  Support<std::map<U, T> >::Support(const std::map<U, T>& m):
    m_(m)
  {
  }

  template <class U, class T>
  unsigned
  Support<std::map<U, T> >::size() const
  {
    return m_.size();
  }

  template <class U, class T>
  typename Support<std::map<U, T> >::iterator
  Support<std::map<U, T> >::find(const U& k) const
  {
    return m_.find(k);
  }

  template <class U, class T>
  bool
  Support<std::map<U, T> >::empty() const
  {
    return m_.empty ();
  }

  template <class U, class T>
  typename Support<std::map<U, T> >::iterator
  Support<std::map<U, T> >::begin() const
  {
    return iterator(m_.begin());
  }

  template <class U, class T>
  typename Support<std::map<U, T> >::iterator
  Support<std::map<U, T> >::end() const
  {
    return iterator(m_.end());
  }

  template <class U, class T>
  U
  Support< std::map<U, T> >::max() const
  {
    return *max_element(begin(), end());
  }



  /*----------------*
   | SparseIterator |
   *----------------*/

  template <class Integer, class ExcludedContainer>
  SparseIterator<Integer, ExcludedContainer>::
  SparseIterator(integer_t from,
		 const excluded_container_t& c):
    excluded_(&c),
    integer_(from)
  {}

  template <class Integer, class ExcludedContainer>
  SparseIterator<Integer, ExcludedContainer>&
  SparseIterator<Integer, ExcludedContainer>::operator++()
  {
    if (excluded_->size() == 0)
      integer_ = integer_ + 1;
    else
      do
	integer_ = integer_ + 1;
      while (excluded_->find(integer_) != excluded_->end());
    return *this;
  }

  template <class Integer, class ExcludedContainer>
  SparseIterator<Integer, ExcludedContainer>&
  SparseIterator<Integer, ExcludedContainer>::operator--()
  {
    if (excluded_->size() == 0)
      integer_ = integer_ - 1;
    else
      do
	integer_ = integer_ - 1;
      while (excluded_->find(integer_) != excluded_->end());
    return *this;
  }

  template <class Integer, class ExcludedContainer>
  SparseIterator<Integer, ExcludedContainer>
  SparseIterator<Integer, ExcludedContainer>::operator++(int)
  {
    SparseIterator tmp = *this;
    ++*this;
    return tmp;
  }

  template <class Integer, class ExcludedContainer>
  SparseIterator<Integer, ExcludedContainer>
  SparseIterator<Integer, ExcludedContainer>::operator--(int)
  {
    SparseIterator tmp = *this;
    --*this;
    return tmp;
  }

  template <class Integer, class ExcludedContainer>
  typename SparseIterator<Integer, ExcludedContainer>::
  integer_t
  SparseIterator<Integer, ExcludedContainer>::operator*()
  {
    return integer_;
  }

  template <class Integer, class ExcludedContainer>
  bool
  SparseIterator<Integer, ExcludedContainer>
  ::operator!=(const SparseIterator& i)
  {
    return i.integer_ != integer_;
  }

  template <class Integer, class ExcludedContainer>
  bool
  SparseIterator<Integer, ExcludedContainer>
  ::operator==(const SparseIterator& i)
  {
    return i.integer_ == integer_;
  }

  template <class Integer, class ExcludedContainer>
  SparseIterator<Integer, ExcludedContainer>&
  SparseIterator<Integer, ExcludedContainer>
  ::operator=(const SparseIterator& i)
  {
    integer_ = i.integer_;
    excluded_ = i.excluded_;
    return *this;
  }




  /*------------------*
   | SparseInterval.  |
   *------------------*/


  /// SparseInterval is a const adapter of a 3-uple :
  /// (from, begin, excluded).
  /// SparseInterval verifies the container concept.
  template <class Integer, class ExcludedContainer>
  SparseInterval<Integer, ExcludedContainer>
  ::SparseInterval(integer_t f, integer_t t, const excluded_container_t& c):
    excluded_(c),
    from_(f),
    to_(t)
  {
    precondition(from_ <= to_ + 1);
    precondition(excluded_.find(to_ + 1) == excluded_.end());
  }

  template <class Integer, class ExcludedContainer>
  SparseInterval<Integer, ExcludedContainer>
  ::SparseInterval(const SparseInterval& a) :
    excluded_(a.excluded_),
    from_(a.from_),
    to_(a.to_)
  {
  }

  template <class Integer, class ExcludedContainer>
  unsigned
  SparseInterval<Integer, ExcludedContainer>::size() const
  {
    //    std::cerr << this->to_string() << std::endl;
    return to_ < from_ ? 0 : to_ - from_ + 1 - excluded_.size();
  }

  template <class Integer, class ExcludedContainer>
  typename SparseInterval<Integer, ExcludedContainer>::integer_t
  SparseInterval<Integer, ExcludedContainer>::max() const
  {
    unsigned r = to_;

    while (excluded_.find(r) != excluded_.end())
      --r;
    return r;
  }

  template <class Integer, class ExcludedContainer>
  std::string
  SparseInterval<Integer, ExcludedContainer>::to_string() const
  {
    std::stringstream s;
    s << "from :" << from_ << " to : " << to_ << " ex:";
    for (typename ExcludedContainer::iterator i = excluded_.begin();
	 i != excluded_.end();
	 ++i)
      s << *i << " ";
    return s.str();
  }

  template <class Integer, class ExcludedContainer>
  typename SparseInterval<Integer, ExcludedContainer>::iterator
  SparseInterval<Integer, ExcludedContainer>::begin() const
  {
    int from = from_;

    if (excluded_.size() != 0)
      while (excluded_.find(from) != excluded_.end())
	from = from + 1;
    return iterator(from, excluded_);
  }

  template <class Integer, class ExcludedContainer>
  typename SparseInterval<Integer, ExcludedContainer>::iterator
  SparseInterval<Integer, ExcludedContainer>::end() const
  {
    return iterator(to_ + 1, excluded_);
  }

} // utility

# include <vaucanson/misc/support.hxx>

#endif // ! VCSN_MISC_SUPPORT_HXX
