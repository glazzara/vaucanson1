// char_traits.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_MISC_CHAR_TRAITS_HXX
# define VCSN_MISC_CHAR_TRAITS_HXX

# include <vaucanson/misc/char_traits.hh>
# include <vaucanson/misc/contract.hh>

namespace utility
{

  /*-----------------.
  | generic_int_type |
  `-----------------*/

  template <class CharT>
  generic_int_type<CharT>::generic_int_type() :
//     val_ (char_type()),
    eof_ (true)
  {
  }

  template <class CharT>
  generic_int_type<CharT>::generic_int_type(const char_type& val) :
    val_ (val),
    eof_ (false)
  {
  }

  template <class CharT>
  generic_int_type<CharT>::operator CharT () const
  {
    return val_;
  }

  template <class CharT>
  bool
  generic_int_type<CharT>::
  operator == (const generic_int_type<CharT>& rhs) const
  {
    if (rhs.eof_)
      return eof_;
    else
      return not eof_ and (rhs.val_ == val_);
  }

  template <class CharT>
  bool
  generic_int_type<CharT>::eof() const
  {
    return eof_;
  }

  /*------------.
  | char_traits |
  `------------*/

  template <typename CharT>
  void
  char_traits<CharT>::assign(char_type& lhs, const char_type& rhs)
  {
    lhs = rhs;
  }

  template <typename CharT>
  bool
  char_traits<CharT>::eq(const char_type& lhs, const char_type& rhs)
  {
    return lhs == rhs;
  }

  template <typename CharT>
  bool
  char_traits<CharT>::lt(const char_type& lhs, const char_type& rhs)
  {
    return lhs < rhs;
  }

  template <typename CharT>
  int
  char_traits<CharT>::compare(const char_type* p,
			      const char_type* q,
			      size_t n)
  {
    size_t i;

    for (i = 0; (i < n) and eq(p[i], q[i]); ++i)
      ;
    if (i == n)
      return 0;
    else
      return lt(p[i], q[i]) ? -1 : 1;
  }

  template <typename CharT>
  size_t
  char_traits<CharT>::length(const char_type* p)
  {
    size_t i = 0;
    while (not eq(p[i], char_type()))
      ++i;
    return i;
  }

  template <typename CharT>
  const typename char_traits<CharT>::char_type*
  char_traits<CharT>::find(const char_type* p,
			   size_t n,
			   const char_type& c)
  {
    size_t i;

    for (i = 0; (i < n) and not eq(p[i], c); ++i)
      ;
    return i < n ? p + i: 0;
  }

  template <typename CharT>
  typename char_traits<CharT>::char_type*
  char_traits<CharT>::move(char_type* s, const char_type* p, size_t n)
  {
    // FIXME:  This  code has  been  (almost)  dummy  pasted from  the
    // standard library. Maybe it should  be usefull to have a special
    // optimized version when pointers do not overlap.

    char_type* tmp = new char_type[n];
    copy(tmp, p, n);
    copy(s, tmp, n);
    delete[] tmp;
    return s;
  }

  template <typename CharT>
  typename char_traits<CharT>::char_type*
  char_traits<CharT>::copy(char_type* s, const char_type* p, size_t n)
  {
    precondition((p < s) or (p > s + n));

    for (size_t i = 0; i < n; ++i)
      assign(s[i], p[i]);
    return s;
  }

  template <typename CharT>
  typename char_traits<CharT>::char_type*
  char_traits<CharT>::assign(char_type* s, size_t n, char_type c)
  {
    for (size_t i = 0; i < n; ++i)
      assign(s[i], c);
    return s;
  }

  template <typename CharT>
  typename char_traits<CharT>::int_type
  char_traits<CharT>::not_eof(const int_type& e)
  {
    return eq_int_type(e, eof()) ? int_type(char_type()) : e;
  }

  template <typename CharT>
  typename char_traits<CharT>::char_type
  char_traits<CharT>::to_char_type(const int_type& e)
  {
    return e; // Calls generic_int_type<char_type>::operator char_type ().
  }

  template <typename CharT>
  typename char_traits<CharT>::int_type
  char_traits<CharT>::to_int_type(const char_type& e)
  {
    return int_type(e);
  }

  template <typename CharT>
  bool
  char_traits<CharT>::eq_int_type(const int_type& e, const int_type& f)
  {
    return e == f;
  }

  template <typename CharT>
  typename char_traits<CharT>::int_type
  char_traits<CharT>::eof()
  {
    return int_type();
  }

} // end of namespace utility

#endif // ! VCSN_MISC_CHAR_TRAITS_HXX
