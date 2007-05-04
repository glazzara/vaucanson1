// counter_support.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_COUNTER_SUPPORT_HXX
# define VCSN_MISC_COUNTER_SUPPORT_HXX

# include <vaucanson/misc/counter_support.hh>
# include <vaucanson/misc/contract.hh>

namespace vcsn
{
  namespace misc
  {

  /*------------------.
  | SupportIterator.  |
  `------------------*/

    inline
    CounterSupportIterator::CounterSupportIterator (unsigned n)
      : i (n)
    {}

    inline
    unsigned
    CounterSupportIterator::operator* () const
    {
      return i;
    }

    inline
    CounterSupportIterator&
    CounterSupportIterator::operator++ ()
    {
      ++i;
      return *this;
    }

    inline
    CounterSupportIterator
    CounterSupportIterator::operator++ (int)
    {
      CounterSupportIterator tmp = *this;
      ++i;
      return tmp;
    }

    inline
    bool
    CounterSupportIterator::operator!= (const CounterSupportIterator& o) const
    {
      return o.i != i;
    }

    inline
    bool
    CounterSupportIterator::operator== (const CounterSupportIterator& o) const
    {
      return i == o.i;
    }



  /*----------.
  | Support.  |
  `----------*/


    /// support<map<U, T> > is a const adapter of std::map to container.
    inline
    CounterSupport::CounterSupport ()
    { }

    inline
    CounterSupport::CounterSupport (const CounterSupport& s)
      : i_ (s.i_)
    { }

    inline
    CounterSupport::CounterSupport (unsigned i)
      : i_ (i)
    { }

    inline
    unsigned
    CounterSupport::size () const
    {
      return i_;
    }

    inline
    CounterSupport::iterator
    CounterSupport::find (unsigned k) const
    {
      if (k >= i_)
	return iterator(i_);
      return iterator(k);
    }

    inline
    bool
    CounterSupport::empty () const
    {
      return i_ == 0;
    }

    inline
    unsigned
    CounterSupport::operator* () const
    {
      precondition (i_ == 1);
      return 0;
    }

    inline
    CounterSupport::iterator
    CounterSupport::begin () const
    {
      return iterator (0);
    }

    inline
    CounterSupport::iterator
    CounterSupport::end () const
    {
      return iterator (i_);
    }

    inline
    unsigned
    CounterSupport::max () const
    {
      return i_;
    }
  } // misc
} // vcsn

#endif // ! VCSN_MISC_SUPPORT_HXX
