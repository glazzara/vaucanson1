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

    template <typename HState>
    inline
    CounterSupportIterator<HState>::CounterSupportIterator (unsigned n)
      : i (n)
    {}

    template <typename HState>
    inline
    typename CounterSupportIterator<HState>::hstate_t
    CounterSupportIterator<HState>::operator* () const
    {
      return hstate_t (i);
    }

    template <typename HState>
    inline
    CounterSupportIterator<HState>&
    CounterSupportIterator<HState>::operator++ ()
    {
      ++i;
      return *this;
    }

    template <typename HState>
    inline
    CounterSupportIterator<HState>
    CounterSupportIterator<HState>::operator++ (int)
    {
      CounterSupportIterator tmp = *this;
      ++i;
      return tmp;
    }

    template <typename HState>
    inline
    bool
    CounterSupportIterator<HState>::operator!= (const CounterSupportIterator<HState>& o) const
    {
      return o.i != i;
    }

    template <typename HState>
    inline
    bool
    CounterSupportIterator<HState>::operator== (const CounterSupportIterator& o) const
    {
      return i == o.i;
    }



  /*----------.
  | Support.  |
  `----------*/


    /// support<map<U, T> > is a const adapter of std<HState>::map to container.
    template <typename HState>
    inline
    CounterSupport<HState>::CounterSupport ()
    { }

    template <typename HState>
    inline
    CounterSupport<HState>::CounterSupport (const CounterSupport& s)
      : i_ (s.i_)
    { }

    template <typename HState>
    inline
    CounterSupport<HState>::CounterSupport (unsigned i)
      : i_ (i)
    { }

    template <typename HState>
    inline
    unsigned
    CounterSupport<HState>::size () const
    {
      return i_;
    }

    template <typename HState>
    inline
    typename CounterSupport<HState>::iterator
    CounterSupport<HState>::find (unsigned k) const
    {
      if (k >= i_)
	return iterator(i_);
      return iterator(k);
    }

    template <typename HState>
    inline
    bool
    CounterSupport<HState>::empty () const
    {
      return i_ == 0;
    }

    template <typename HState>
    inline
    unsigned
    CounterSupport<HState>::operator* () const
    {
      precondition (i_ == 1);
      return 0;
    }

    template <typename HState>
    inline
    typename CounterSupport<HState>::iterator
    CounterSupport<HState>::begin () const
    {
      return iterator (0);
    }

    template <typename HState>
    inline
    typename CounterSupport<HState>::iterator
    CounterSupport<HState>::end () const
    {
      return iterator (i_);
    }

    template <typename HState>
    inline
    unsigned
    CounterSupport<HState>::max () const
    {
      return i_;
    }
  } // misc
} // vcsn

#endif // ! VCSN_MISC_SUPPORT_HXX
