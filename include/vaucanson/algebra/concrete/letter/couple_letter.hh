// couple_letter.hh
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

#ifndef COUPLE_LETTER_HH
# define COUPLE_LETTER_HH

// Here is functions and traits used to manipulate letters
// which are couple

// FIXME: Only used function are defined in the char_traits.
//        So some functions and types are missing.

namespace std
{
  // To display a single pair
  // It supposes that each element of the pair is printable
  // (i.e. the operator << is defined on it)
  template <typename U, typename V>
  ostream& operator<<(ostream& o, pair<U, V> p);

  // To display a basic_string of pair (idem)
  template <typename U, typename V>
  ostream& operator<<(ostream& o, basic_string<pair<U, V> > s);

  // The char trait on pair (needed by basic_string for example)
  template <typename U, typename V>
  struct char_traits<pair<U, V> >
  {
    typedef pair<U, V> 	char_type;

    static int 
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

    static char_type* 
    move(char_type* __s1, const char_type* __s2, size_t __n)
    {
      char_type* tmp = new char_type[__n];
      copy(tmp, __s2, __n);
      copy(__s1, tmp, __n);
      delete[] tmp;
      return __s1;
    }

    static char_type* 
    copy(char_type* __s1, const char_type* __s2, size_t __n)
    {  
      for (size_t i = 0; i != __n; ++i)
	__s1[i] = __s2[i];
      return __s1;
    }

    static char_type* 
    assign(char_type* __s, size_t __n, char_type __a)
    { 
      for (size_t i = 0; i != __n; ++i)
	__s[i] = __a;
      return __s;
    }
  };
}

# include <vaucanson/algebra/concrete/letter/couple_letter.hxx>

#endif // !COUPLE_LETTER_HH
