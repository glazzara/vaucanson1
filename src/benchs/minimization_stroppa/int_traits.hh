// int_traits.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.
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
#ifndef VCSN_BENCHS_MINIMIZATION_STROPPA_INT_TRAITS_HH
# define VCSN_BENCHS_MINIMIZATION_STROPPA_INT_TRAITS_HH

# include <string>
# include <locale>




// Provide std::char_traits specialization.
namespace std
{
  template <>
  struct char_traits<unsigned int>
  {
    typedef unsigned int	char_type;

    // NB: this type should be bigger than char_type, so as to
    // properly hold EOF values in addition to the full range of
    // char_type values.
    typedef unsigned long       int_type;

    typedef streampos           pos_type;
    typedef streamoff           off_type;
    typedef mbstate_t           state_type;

    static void 
    assign(char_type& __c1, const char_type& __c2)
    { __c1 = __c2; }

    static bool 
    eq(const char_type& __c1, const char_type& __c2)
    { return __c1 == __c2; }

    static bool 
    lt(const char_type& __c1, const char_type& __c2)
    { return __c1 < __c2; }

    static int
    compare(const char_type* __s1, const char_type* __s2, size_t __n)
    { 
      for (size_t __i = 0; __i < __n; ++__i)
	if (!eq(__s1[__i], __s2[__i]))
	  return lt(__s1[__i], __s2[__i]) ? -1 : 1;
      return 0; 
    }

    static size_t
    length(const char_type* __s)
    {
      const char_type* __p = __s; 
      while (*__p) ++__p; 
      return (__p - __s); 
    }

    static const char_type* 
    find(const char_type* __s, size_t __n, const char_type& __a)
    {
      for (const char_type* __p = __s; size_t(__p - __s) < __n; ++__p)
	if (*__p == __a) return __p;
      return 0;
    }

    static char_type* 
    move(char_type* __s1, const char_type* __s2, size_t __n)
    {
      return (char_type*) memmove(__s1, __s2, __n * sizeof(char_type));
    }

    static char_type* 
    copy(char_type* __s1, const char_type* __s2, size_t __n)
    {
      return (char_type*) memcpy(__s1, __s2, __n * sizeof(char_type));
    }

    static char_type* 
    assign(char_type* __s, size_t __n, char_type __a)
    {
      for (char_type* __p = __s; __p < __s + __n; ++__p) 
	assign(*__p, __a);
      return __s; 
    }
    
    static char_type 
    to_char_type(const int_type& __c)
    {
      char_type __r = { __c };
      return __r;
    }

    static int_type 
    to_int_type(const char_type& __c) 
    {
      return int_type(__c);
    }

    static bool 
    eq_int_type(const int_type& __c1, const int_type& __c2)
    { return __c1 == __c2; }

    static int_type 
    eof() { return static_cast<int_type>(-1); }

    static int_type
    not_eof(const int_type& __c)
    { return eq_int_type(__c, eof()) ? int_type(0) : __c; }
  };


};



#endif // ! VCSN_BENCHS_MINIMIZATION_STROPPA_INT_TRAITS_HH
