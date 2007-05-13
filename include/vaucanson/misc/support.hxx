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
#ifndef VCSN_MISC_SUPPORT_HXX
# define VCSN_MISC_SUPPORT_HXX

# include <vaucanson/misc/support.hh>
# include <vaucanson/misc/contract.hh>
# include <vaucanson/automata/concept/handlers.hh>

namespace vcsn
{
  namespace misc
  {

  /*------------------.
  | SupportIterator.  |
  `------------------*/

    template <class C>
    SupportIterator<C>::SupportIterator (map_iterator mp)
      : i (mp)
    {}

    template <class C>
    typename SupportIterator<C>::key_type
    SupportIterator<C>::operator* () const
    {
      return i->first;
    }

    template <class C>
    SupportIterator<C>&	SupportIterator<C>::operator++ ()
    {
      ++i;
      return *this;
    }

    template <class C>
    SupportIterator<C> SupportIterator<C>::operator++ (int)
    {
      SupportIterator<C> tmp = *this;
      ++i;
      return tmp;
    }

    template <class C>
    bool
    SupportIterator<C>::operator!= (const SupportIterator& o) const
    {
      return o.i != i;
    }

    template <class C>
    bool
    SupportIterator<C>::operator== (const SupportIterator& o) const
    {
      return ! (*this != o);
    }

    //Specialization for std::vector<handler<T, U> >
    template <typename T, typename U>
    SupportIterator<std::vector<handler<T, U> > >::SupportIterator (vector_iterator mp)
      : i (mp)
    {}

    template <typename T, typename U>
    typename SupportIterator<std::vector<handler<T, U> > >::data_type
    SupportIterator<std::vector<handler<T, U> > >::operator* () const
    {
      return *i;
    }

    template <typename T, typename U>
    SupportIterator<std::vector<handler<T, U> > >&
    SupportIterator<std::vector<handler<T, U> > >::operator++ ()
    {
      ++i;
      return *this;
    }

    template <typename T, typename U>
    SupportIterator<std::vector<handler<T, U> > >&
    SupportIterator<std::vector<handler<T, U> > >::operator-- ()
    {
      --i;
      return *this;
    }

    template <typename T, typename U>
    SupportIterator<std::vector<handler<T, U> > >
    SupportIterator<std::vector<handler<T, U> > >::operator++ (int)
    {
      SupportIterator<std::vector<handler<T, U> > > tmp = *this;
      ++i;
      return tmp;
    }

    template <typename T, typename U>
    bool
    SupportIterator<std::vector<handler<T, U> > >::operator!= (const SupportIterator& o) const
    {
      return o.i != i;
    }

    template <typename T, typename U>
    bool
    SupportIterator<std::vector<handler<T, U> > >::operator== (const SupportIterator& o) const
    {
      return ! (*this != o);
    }


  /*----------.
  | Support.  |
  `----------*/


    /// support<map<U, T> > is a const adapter of std::map to container.
    template <class U, class T>
    Support<std::map<U, T> >::Support (const Support& s)
      : m_ (s.m_)
    {
    }

    template <class U, class T>
    Support<std::map<U, T> >::Support (const std::map<U, T>& m)
      : m_ (m)
    {
    }

    template <class U, class T>
    unsigned
    Support<std::map<U, T> >::size () const
    {
      return m_.size ();
    }

    template <class U, class T>
    typename Support<std::map<U, T> >::iterator
    Support<std::map<U, T> >::find (const U& k) const
    {
      return m_.find (k);
    }

    template <class U, class T>
    bool
    Support<std::map<U, T> >::empty () const
    {
      return m_.empty ();
    }

    template <class U, class T>
    typename Support<std::map<U, T> >::value_type
    Support<std::map<U, T> >::operator* () const
    {
      precondition (m_.size () == 1);
      return *m_.begin ();
    }

    template <class U, class T>
    typename Support<std::map<U, T> >::iterator
    Support<std::map<U, T> >::begin () const
    {
      return iterator (m_.begin ());
    }

    template <class U, class T>
    typename Support<std::map<U, T> >::iterator
    Support<std::map<U, T> >::end () const
    {
      return iterator (m_.end ());
    }

    template <class U, class T>
    U
    Support< std::map<U, T> >::max () const
    {
      return *max_element (begin (), end ());
    }

    /// support<vector<U, T> > is a const adapter of std::vector to container.
    template <class T, class U>
    Support<std::vector<handler<T, U> > >::Support (const Support& s)
      : m_ (s.m_)
    {
    }

    template <class T, class U>
    Support<std::vector<handler<T, U> > >::Support (const std::vector<handler<T, U> >& m)
      : m_ (m)
    {
    }

    template <class T, class U>
    unsigned
    Support<std::vector<handler<T, U> > >::size () const
    {
      return m_.size ();
    }

    template <class T, class U>
    typename Support<std::vector<handler<T, U> > >::iterator
    Support<std::vector<handler<T, U> > >::find (const handler<T, U>& k) const
    {
      return m_.find (k);
    }

    template <class T, class U>
    bool
    Support<std::vector<handler<T, U> > >::empty () const
    {
      return m_.empty ();
    }

    template <class T, class U>
    typename Support<std::vector<handler<T, U> > >::value_type
    Support<std::vector<handler<T, U> > >::operator* () const
    {
      precondition (m_.size () == 1);
      return *m_.begin ();
    }

    template <class T, class U>
    typename Support<std::vector<handler<T, U> > >::iterator
    Support<std::vector<handler<T, U> > >::begin () const
    {
      return iterator (m_.begin ());
    }

    template <class T, class U>
    typename Support<std::vector<handler<T, U> > >::iterator
    Support<std::vector<handler<T, U> > >::end () const
    {
      return iterator (m_.end ());
    }

    template <class T, class U>
    handler<T, U>
    Support<std::vector<handler<T, U> > >::max () const
    {
      return m_.back();
    }
    /// support<InitialContainer<U, HState> is a const adapter of InitialContainer to container.
    template <class U, class HState>
    Support<InitialContainer<U, HState> >::Support (const Support& s)
      : m_ (s.m_)
    {
    }

    template <class U, class HState>
    Support<InitialContainer<U, HState> >::Support (const Support::container_t& m)
      : m_ (m)
    {
    }

    template <class U, class HState>
    unsigned
    Support<InitialContainer<U, HState> >::size () const
    {
      return m_.size ();
    }

    template <class U, class HState>
    typename Support<InitialContainer<U, HState> >::iterator
    Support<InitialContainer<U, HState> >::find (const HState& k) const
    {
      return m_.find (k);
    }

    template <class U, class HState>
    bool
    Support<InitialContainer<U, HState> >::empty () const
    {
      return m_.empty ();
    }

    template <class U, class HState>
    typename Support<InitialContainer<U, HState> >::value_type
    Support<InitialContainer<U, HState> >::operator* () const
    {
      precondition (m_.size () == 1);
      return *m_.begin ();
    }

    template <class U, class HState>
    typename Support<InitialContainer<U, HState> >::iterator
    Support<InitialContainer<U, HState> >::begin () const
    {
      return iterator (m_.begin ());
    }

    template <class U, class HState>
    typename Support<InitialContainer<U, HState> >::iterator
    Support<InitialContainer<U, HState> >::end () const
    {
      return iterator (m_.end ());
    }

    template <class U, class HState>
    HState
    Support<InitialContainer<U, HState> >::max () const
    {
      return *max_element (begin (), end ());
    }



  } // misc
} // vcsn

#endif // ! VCSN_MISC_SUPPORT_HXX
