// support.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_MISC_SUPPORT_HXX
# define VCSN_MISC_SUPPORT_HXX

# include <vaucanson/misc/support.hh>
# include <vaucanson/misc/contract.hh>
# include <sstream>

namespace utility {

  template <class C>
  inline
  SupportIterator<C>::SupportIterator(map_iterator mp):
    i(mp)
  {}
    
  template <class C>
  inline
  typename SupportIterator<C>::key_type	
  SupportIterator<C>::operator*() const
  {
    return i->first;
  }

  template <class C>
  inline
  SupportIterator<C>&	SupportIterator<C>::operator++()
  {
    ++i;
    return *this;
  }

  template <class C>
  inline
  SupportIterator<C>	SupportIterator<C>::operator++(int)
  {
    SupportIterator<C> tmp = *this;
    ++i;
    return tmp;
  }

  template <class C>
  inline
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

  //! support<map<U, T> > is a const adapter of std::map to container.
  template <class U, class T>
  inline
  Support<std::map<U, T> >::Support(const Support& s):
    m_(s.m_)
  {
  }

  template <class U, class T>
  inline
  Support<std::map<U, T> >::Support(const std::map<U, T>& m):
    m_(m)
  {
  }

  template <class U, class T>
  inline
  unsigned
  Support<std::map<U, T> >::size() const
  {
    return m_.size();
  }

  template <class U, class T>
  inline
  SupportIterator<std::map<U, T> >
  Support<std::map<U, T> >::begin() const
  {
    return iterator(m_.begin());
  }
  
  template <class U, class T>
  inline
  SupportIterator<std::map<U, T> >
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

  //! SparseIterator

  template <class Integer, class ExcludedContainer>
  inline
  SparseIterator<Integer, ExcludedContainer>::
  SparseIterator(integer_t from, 
		 const excluded_container_t& c):
    excluded_(&c),
    integer_(from)
  {}

  template <class Integer, class ExcludedContainer>
  inline
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
  inline
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
  inline
  SparseIterator<Integer, ExcludedContainer>
  SparseIterator<Integer, ExcludedContainer>::operator++(int)
  {
    SparseIterator tmp = *this;
    ++*this;
    return tmp;
  }

  template <class Integer, class ExcludedContainer>
  inline
  SparseIterator<Integer, ExcludedContainer>
  SparseIterator<Integer, ExcludedContainer>::operator--(int)
  {
    SparseIterator tmp = *this;
    --*this;
    return tmp;
  }

  template <class Integer, class ExcludedContainer>
  inline
  typename SparseIterator<Integer, ExcludedContainer>::
  integer_t	    
  SparseIterator<Integer, ExcludedContainer>::operator*()
  {
    return integer_;
  }
  
  template <class Integer, class ExcludedContainer>
  inline
  bool	    
  SparseIterator<Integer, ExcludedContainer>
  ::operator!=(const SparseIterator& i)
  {
    return i.integer_ != integer_;
  }

  template <class Integer, class ExcludedContainer>
  inline
  bool	    
  SparseIterator<Integer, ExcludedContainer>
  ::operator==(const SparseIterator& i)
  {
    return i.integer_ == integer_;
  }

  template <class Integer, class ExcludedContainer>
  inline
  SparseIterator<Integer, ExcludedContainer>&
  SparseIterator<Integer, ExcludedContainer>
  ::operator=(const SparseIterator& i)
  {
    integer_ = i.integer_;
    excluded_ = i.excluded_;
    return *this;
  }

  //! SparseInterval is a const adapter of a 3-uple :
  //! (from, begin, excluded).
  //! SparseInterval verifies the container concept.
  template <class Integer, class ExcludedContainer>
  inline
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
  inline
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
  inline
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
  inline
  typename SparseInterval<Integer, ExcludedContainer>::iterator 
  SparseInterval<Integer, ExcludedContainer>::begin() const
  {
    return iterator(from_, excluded_);
  }

  template <class Integer, class ExcludedContainer>
  inline
  typename SparseInterval<Integer, ExcludedContainer>::iterator 
  SparseInterval<Integer, ExcludedContainer>::end() const
  {
    return iterator(to_ + 1, excluded_);
  }

} // utility 

# include <vaucanson/misc/support.hxx>

#endif // VCSN_MISC_SUPPORT_HXX
