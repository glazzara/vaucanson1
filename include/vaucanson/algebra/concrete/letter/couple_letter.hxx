// couple_letter.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef VCSN_ALGEBRA_CONCRETE_COUPLE_LETTER_HXX
# define VCSN_ALGEBRA_CONCRETE_COUPLE_LETTER_HXX

# include <vaucanson/algebra/concrete/letter/couple_letter.hh>

namespace std {

  template <typename U, typename V>
  ostream& operator<<(ostream& o, pair<U, V> p)
  {
    return o << "(" << p.first << "," << p.second << ")";
  }

  template <typename U, typename V>
  ostream& operator<<(ostream& o, basic_string<pair<U, V> > s)
  {
    typename basic_string<pair<U, V> >::const_iterator	i;
    for (i = s.begin(); i != s.end(); ++i)
      o << "(" << i->first << "," << i->second << ")";
    return o;
  }

  template <typename U, typename V>
  int 
  char_traits<std::pair<U, V> >::
  compare(const char_type* __s1, const char_type* __s2, size_t __n)
  {
    size_t i;
      for (i = 0; (i != __n) && (__s1[i] == __s2[i]); ++i)
	;
      if (i == __n)
	return 0;
      else
	return __s1[i] > __s2[i] ? 1 : -1;
    }

  template <typename U, typename V>
  typename char_traits<std::pair<U, V> >::char_type* 
  char_traits<std::pair<U, V> >::
  move(char_type* __s1, const char_type* __s2, size_t __n)
  {
      char_type* tmp = new char_type[__n];
      copy(tmp, __s2, __n);
      copy(__s1, tmp, __n);
      delete[] tmp;
      return __s1;
  }
  
  template <typename U, typename V>
  typename char_traits<std::pair<U, V> >::char_type* 
  char_traits<std::pair<U, V> >::
  copy(char_type* __s1, const char_type* __s2, size_t __n)
  {  
    for (size_t i = 0; i != __n; ++i)
      __s1[i] = __s2[i];
    return __s1;
  }
  
  template <typename U, typename V>
  typename char_traits<std::pair<U, V> >::char_type* 
  char_traits<std::pair<U, V> >::
  assign(char_type* __s, size_t __n, char_type __a)
  { 
    for (size_t i = 0; i != __n; ++i)
      __s[i] = __a;
    return __s;
  }
  
} // std

#endif // VCSN_ALGEBRA_CONCRETE_COUPLE_LETTER_HXX
