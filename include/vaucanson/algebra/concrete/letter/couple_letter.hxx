// couple_letter.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_CONCRETE_LETTER_COUPLE_LETTER_HXX
# define VCSN_ALGEBRA_CONCRETE_LETTER_COUPLE_LETTER_HXX

# include <vaucanson/algebra/concrete/letter/couple_letter.hh>

namespace vcsn {

  // Specialization for pairs.
  template <typename S, typename U, typename V>
  bool op_parse(const algebra::FreeMonoidBase<S>& set,
		std::string<std::pair<U,V> >& v,
		const std::string& s,
		typename std::string::const_iterator& i,
		const std::list<char>&)
  {
    typename std::string::const_iterator j = i;

    while (i != s.end()) {
      if (*i != '(')
	break ;
      std::string sub(i, s.end());
      std::istringstream is(sub);
      std::pair<U,V> p;
      is >> p;
      if (!set.alphabet().contains(p))
	break ;
      int inc = sub.size() - is.str().size();
      for (int k = 0; k < inc; k++, i++) ;
      v += p;
    }
    return (i != j);
  }
} // vcsn

namespace std {

  template <typename U, typename V>
  ostream& operator<<(ostream& o, pair<U, V> p)
  {
    return o << "(" << p.first << "," << p.second << ")";
  }

  template <typename U, typename V, class Traits, class Allocator>
  ostream& operator<<(ostream& o,
		      basic_string<pair<U, V>, Traits, Allocator> s)
  {
    typename basic_string<pair<U, V>, Traits, Allocator>::const_iterator i;
    for (i = s.begin(); i != s.end(); ++i)
      o << "(" << i->first << "," << i->second << ")";
    return o;
  }
<<<<<<< .working
=======

  template <typename U, typename V>
  istream& operator>>(istream& i, pair<U, V>& p)
  {
    char c = i.get();
    if (c != '(')
      i.unget();
    i >> p.first;
    c = i.get();
    if (c != ',')
      i.unget();
    i >> p.second;
    c = i.get();
    if (c != ')')
      i.unget();
    return i;
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
  
>>>>>>> .merge-right.r558
} // std

#endif // VCSN_ALGEBRA_CONCRETE_LETTER_COUPLE_LETTER_HXX
