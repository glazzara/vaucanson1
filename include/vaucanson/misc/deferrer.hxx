// deferrer.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_MISC_DEFERRER_HXX
# define VCSN_MISC_DEFERRER_HXX

/** @addtogroup utility */ /** @{ */
/**
 * @file deferrer.hxx
 *
 * This file contains definitions for the Deferrer class.
 *
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 * @see utility::Deferrer, utility::SafeDeferrer
 */
/** @} */

# include <vaucanson/misc/deferrer.hh>
# include <vaucanson/misc/contract.hh>

# include <new>
# include <cstdlib>

namespace utility
{

  /** @addtogroup utility *//** @{ */

  /*-----------------------------------------------.
  | DeferrerDebugPart, with runtime tests enabled  |
  `-----------------------------------------------*/

  template <class T, bool B>
  DeferrerDebugPart<T, B>::DeferrerDebugPart(void* ptr, bool is_valid) :
    is_valid_ (is_valid)
  {
    memset(ptr, 0, sizeof(T));
  }

  template <class T, bool B>
  void
  DeferrerDebugPart<T, B>::set_valid(bool b)
  {
    if (is_valid_)
      warning("Modifying a valid Deferrer<T, true>.");
    is_valid_ = b;
  }

  template <class T, bool B>
  T&
  DeferrerDebugPart<T, B>::cast(void *ptr)
  {
    precondition(is_valid_);
    return *reinterpret_cast<T*> (ptr);
  }

  template <class T, bool B>
  const T&
  DeferrerDebugPart<T, B>::cast(const void *ptr) const
  {
    precondition(is_valid_);
    return *reinterpret_cast<const T*> (ptr);
  }

  /*-------------------------------------------------.
  | DeferrerDebugPart, with runtime tests *disabled* |
  `-------------------------------------------------*/

  template <class T>
  DeferrerDebugPart<T, false>::DeferrerDebugPart(void*, bool)
  {
  }

  template <class T>
  void
  DeferrerDebugPart<T, false>::set_valid(bool)
  {
  }

  template <class T>
  T&
  DeferrerDebugPart<T, false>::cast(void *ptr)
  {
    return *reinterpret_cast<T*> (ptr);
  }

  template <class T>
  const T&
  DeferrerDebugPart<T, false>::cast(const void *ptr) const
  {
    return *reinterpret_cast<const T*> (ptr);
  }

  /*---------.
  | Deferrer |
  `---------*/

  template <class T, bool rt_checks>
  Deferrer<T, rt_checks>::Deferrer() : DeferrerDebugPart<T, rt_checks> (data)
  {
  }

  template <class T, bool rt_checks>
  Deferrer<T, rt_checks>&
  Deferrer<T, rt_checks>::operator = (const deferred_type& rhs)
  {
    new (data) deferred_type (rhs);
    this->set_valid(true);
    return *this;
  }

  template <class T, bool rt_checks>
  Deferrer<T, rt_checks>::operator T () const
  {
    return cast(data);
  }

  /** @} */
} // End of namespace utility.

#endif // ! VCSN_MISC_DEFERRER_HXX
