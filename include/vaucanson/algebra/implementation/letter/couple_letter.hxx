// couple_letter.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HXX

# include <sstream>

# include <vaucanson/algebra/implementation/letter/couple_letter.hh>

namespace vcsn {

  // Specialization for pairs.
  template <typename S, typename U, typename V>
  bool op_parse(const algebra::FreeMonoidBase<S>& set,
		std::basic_string< std::pair<U, V> >& v,
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

namespace utility {

  template <typename U, typename V>
  std::ostream& operator<<(std::ostream& o, std::pair<U, V> p)
  {
    return o << "(" << p.first << "," << p.second << ")";
  }

  template <typename U, typename V, class Traits, class Allocator>
  std::ostream& operator<<(std::ostream& o,
    std::basic_string<std::pair<U, V>, Traits, Allocator> s)
  {
    typename
    std::basic_string<std::pair<U, V>, Traits, Allocator>::const_iterator i;
    for (i = s.begin(); i != s.end(); ++i)
      o << "(" << i->first << "," << i->second << ")";
    return o;
  }

  template <typename U, typename V>
  std::istream& operator>>(std::istream& i, std::pair<U, V>& p)
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

} // utility

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_LETTER_COUPLE_LETTER_HXX
