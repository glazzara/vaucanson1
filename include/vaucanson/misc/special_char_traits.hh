// special_char_traits.hh: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_MISC_SPECIAL_CHAR_TRAITS_HH
# define VCSN_MISC_SPECIAL_CHAR_TRAITS_HH

/** @addtogroup utility *//** @{ */
/**
 * @brief This file holds specialized versions of std::char_traits for
 *        a few common types.
 *
 * If you  do not  want to have  to specialize char_traits  for common
 * types, this file may help you.  It provides generic implementations
 * of char_traits for many types. If you only want to have a framework
 * to  do  this kind  of  specialization  easily,  but with  your  own
 * specializations,   you   should   have   a   look   at   the   file
 * vaucanson/misc/char_traits.hh.
 *
 * @author Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
 * @see vaucanson/misc/char_traits.hh
 */
/** @} */

# include <vaucanson/misc/char_traits.hh>

# define VCSN_USE_GENERIC_CHAR_TRAITS_FOR(Type)				\
  template <>								\
  struct char_traits<Type> : public ::utility::char_traits<Type> { }

namespace std
{
  // Specialize char_traits for builtin types.
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(int);
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(long int);
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(unsigned int);
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(unsigned long int);
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(float);
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(double);
  VCSN_USE_GENERIC_CHAR_TRAITS_FOR(long double);

  // Specialize char_traits for pointers.
  template <class T>
  struct char_traits<T*> : public ::utility::char_traits<T*> { };

  // Specialize char_traits for pairs.
  template <class U, class V>
  struct char_traits< pair<U, V> > :
    public ::utility::char_traits< pair<U, V> >
  {
  };
} // end of namespace std

#endif // ! VCSN_MISC_SPECIAL_CHAR_TRAITS_HH
