// support.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_SELF_ITERATOR_HH
# define VCSN_MISC_SELF_ITERATOR_HH

/**
 * @file   misc/self_iterator.hh
 * @brief  Iterator holding its container.
 *
 */

# include <iterator>

namespace vcsn
{
  namespace misc
  {

    /** @addtogroup misc *//** @{ */

    /// SelfIterator is an iterator which is also a container.
    template <template <class> class C, class T>
    class SelfIterator
    {
    public:
      SelfIterator (const C<T>& c);
      SelfIterator ();
      SelfIterator (const SelfIterator& s);

      const T& operator* () const;

      const SelfIterator& operator++ ();
      SelfIterator operator++ (int);

      bool operator!= (const SelfIterator& o) const;
      bool operator== (const SelfIterator& o) const;

    private:
      const C<T>* c_;
      typename C<T>::const_iterator pos_;
    };

    /** @} */

  } // misc
} // vcsn


# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/misc/self_iterator.hxx>
# endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_MISC_SELF_ITERATOR_HH
