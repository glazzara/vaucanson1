// support.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey 
// and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_MISC_SUPPORT_HH
# define VCSN_MISC_SUPPORT_HH

/**
 * @file   support.hh
 * @brief  Stuff to adapt containers.
 * 
 */

# include <iterator>
# include <map>

namespace vcsn {

   /** @addtogroup utility *//** @{ */

  template <class T>
  class Support;

  /// Iterator over the Support generic class.
  /// @bug is not STL compliant yet.
  template <class C>
  class SupportIterator
  {
  public:
    typedef typename C::key_type	key_type;
    typedef typename C::const_iterator	map_iterator;
    typedef SupportIterator<C>		self_t;
    
    SupportIterator(map_iterator);
    
    key_type	operator*() const;
    self_t&	operator++();
    self_t	operator++(int);
    bool	operator!=(const SupportIterator&) const;

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

    Support(const std::map<U, T>&);
    Support(const Support&);
    
    iterator begin() const;
    iterator end() const;
    unsigned size() const;

  private:
    const std::map<U, T>&	m_;
  };

  /// SparseIterator is an iterator over range except some points.
  template <class Integer, class ExcludedContainer>
  class SparseIterator
  {
  public:
    typedef Integer		integer_t;
    typedef ExcludedContainer	excluded_container_t;

    SparseIterator(integer_t, const excluded_container_t&);

    SparseIterator& operator++();
    SparseIterator  operator++(int);
    SparseIterator& operator--();
    SparseIterator  operator--(int);
    integer_t	    operator*();
    bool	    operator!=(const SparseIterator&);
    bool	    operator==(const SparseIterator&);
    SparseIterator& operator=(const SparseIterator&);

  private:
    const excluded_container_t*	excluded_;
    integer_t			integer_;
  };

  /*! @} */

} // vcsn

namespace std {

  template <class Integer, class ExcludedContainer>
  struct iterator_traits<vcsn::SparseIterator<Integer, ExcludedContainer> >
  {
    typedef input_iterator_tag  iterator_category;
    typedef Integer		value_type;
    typedef int			difference_type;
    typedef int*		pointer;
    typedef int&		reference;
  };

} // std

namespace vcsn {

   /** @addtogroup utility *//** @{ */

  /** 
   *
   * @brief Container over a sparse integer range.
   *
   * SparseInterval is a const adapter of a 3-uple :
   *  (from, begin, excluded).
   *  SparseInterval verifies the container concept.
   */
  template <class Integer, class ExcludedContainer>
  class SparseInterval
  {
  public:
    typedef Integer		integer_t;
    typedef ExcludedContainer	excluded_container_t;
    typedef SparseIterator<integer_t, excluded_container_t> iterator;

    SparseInterval(integer_t, integer_t, const excluded_container_t&);
    
    iterator begin() const;
    iterator end() const;
    unsigned size() const;
    std::string to_string() const;

  private:
    const excluded_container_t&	excluded_;
    integer_t			from_;
    integer_t			to_;
  };

  /// SelfIterator is an iterator which is also a container.
  template <template <class> class C, class T>
  class SelfIterator 
  {
  public:
    SelfIterator(const C<T>& c):
      c_(&c),
      pos_(c.begin())
    {}
    
    SelfIterator():
      c_(0),
      pos_()
    {}
    
    SelfIterator(const SelfIterator& s):
      c_(s.c_),
      pos_(s.pos_)
    {}

    const T& operator*() const
    {
      return *pos_;
    }

    const SelfIterator& operator++() 
    {
      pos_++;
      return *this;
    }

    SelfIterator operator++(int) 
    {
      SelfIterator tmp(*this);
      ++pos_;
      return tmp;
    }

    bool operator!=(const SelfIterator& o) const
    {
      if (c_ == 0)
	if (o.c_ == 0)
	  return false;
	else
	  return o.pos_ != o.c_->end();
      else if (o.c_ == 0)
	return pos_ != c_->end();
      return (o.c_ != c_ ||
	      o.pos_ != pos_);
    }

    bool operator==(const SelfIterator& o) const
    {
      if (c_ == 0)
	if (o.c_ == 0)
	  return true;
	else
	  return o.pos_ == o.c_->end();
      else if (o.c_ == 0)
	return pos_ == c_->end();
      return (o.c_ == c_ &&
	      o.pos_ == pos_);
    }

  private:
    const C<T>* c_;
    typename C<T>::const_iterator pos_;
  };

   /** @} */
  
} // vcsn

# include <vaucanson/misc/support.hxx>

#endif // VCSN_MISC_SUPPORT_HH
