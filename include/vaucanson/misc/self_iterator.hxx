// support.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_SELF_ITERATOR_HXX
# define VCSN_MISC_SELF_ITERATOR_HXX

# include <vaucanson/misc/self_iterator.hh>

namespace vcsn
{
  namespace misc
  {

    template <template <class> class C, class T>
    inline
    class SelfIterator::SelfIterator (const C<T>& c)
      : c_ (&c),
	pos_ (c.begin ())
    {}

    template <template <class> class C, class T>
    inline
    class SelfIterator::SelfIterator ()
      : c_ (0),
	pos_ ()
    {}

    template <template <class> class C, class T>
    inline
    class SelfIterator::SelfIterator (const SelfIterator& s)
      : c_ (s.c_),
	pos_ (s.pos_)
    {}

    template <template <class> class C, class T>
    inline
    const T&
    class SelfIterator::operator* () const
    {
      return *pos_;
    }

    template <template <class> class C, class T>
    inline
    const SelfIterator&
    class SelfIterator::operator++ ()
    {
      pos_++;
      return *this;
    }

    template <template <class> class C, class T>
    inline
    SelfIterator
    class SelfIterator::operator++ (int)
    {
      SelfIterator tmp (*this);
      ++pos_;
      return tmp;
    }

    template <template <class> class C, class T>
    inline
    bool
    class SelfIterator::operator!= (const SelfIterator& o) const
    {
      if (c_ == 0)
	if (o.c_ == 0)
	  return false;
	else
	  return o.pos_ != o.c_->end ();
      else if (o.c_ == 0)
	return pos_ != c_->end ();
      return o.c_ != c_ || o.pos_ != pos_;
    }

    template <template <class> class C, class T>
    inline
    bool
    class SelfIterator::operator== (const SelfIterator& o) const
    {
      if (c_ == 0)
	return o.c_ == 0 || o.pos_ == o.c_->end ();
      else if (o.c_ == 0)
	return pos_ == c_->end ();
      return o.c_ == c_ && o.pos_ == pos_;
    }

  } // misc
} // vcsn

#endif // ! VCSN_MISC_SUPPORT_HXX
