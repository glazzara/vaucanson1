// str_words.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef ALGEBRA_STR_WORDS_HXX
# define ALGEBRA_STR_WORDS_HXX

# include <vaucanson/algebra/concrete/free_monoid/str_words.hh>

namespace vcsn {

  template<typename A>
  void 
  op_in_mul(const FreeMonoid<A>& s, 
	    std::basic_string<typename A::letter_t>& dst,
	    const std::basic_string<typename A::letter_t>& src)
  { 
    dst += src; 
  }

  template<typename A>
  std::basic_string<typename A::letter_t>
  op_mul(const FreeMonoid<A>& s,
	 const std::basic_string<typename A::letter_t>& a,
	 const std::basic_string<typename A::letter_t>& b)
  { 
    return a + b; 
  }

  template <typename A>
  bool
  op_xeq(const FreeMonoid<A>& s, 
	 const std::basic_string<typename A::letter_t>& a, 
	 const std::basic_string<typename A::letter_t>& b)
  {
    typename std::basic_string<typename A::letter_t>::const_iterator 
      m = b.begin();
    typename std::basic_string<typename A::letter_t>::const_iterator l;
    for (l = a.begin(); m != b.end() && l != a.end(); ++l)
      {
	if (! s.alphabet().letter_equality(*l, *m))
	  return false;
	++m;
      }
    return (m == b.end() && l == a.end());
  }

  template<typename A>
  const std::basic_string<typename A::letter_t>&
  identity_value(SELECTOR(FreeMonoid<A>),
		 SELECTOR(std::basic_string<typename A::letter_t>))
  {
    static const std::basic_string<typename A::letter_t> instance;
    return instance;
  }

  template<typename A>
  std::basic_string<typename A::letter_t>
  op_convert(SELECTOR(std::basic_string<typename A::letter_t>),
	     SELECTOR(FreeMonoid<A>), const typename A::letter_t& c)
  { 
    std::basic_string<typename A::letter_t> str; 
    str = c; 
    return str; 
  }

  template <class A>
  Element<FreeMonoid<A>, std::basic_string<typename A::letter_t> >
  op_choose(const FreeMonoid<A>& s, 
	    SELECTOR(std::basic_string<typename A::letter_t>))
  {
    // FIXME : use global constants to define this !
    unsigned length = ((unsigned)(((float) rand() / (float) RAND_MAX) * 5));
    std::basic_string<typename A::letter_t> r;
    for (unsigned i = 0; i < length; ++i)
      r = r + s.alphabet().choose();
    return Element<FreeMonoid<A>, std::basic_string<typename A::letter_t> >(s, r);
  }

} // vcsn

#endif //  ALGEBRA_STR_WORDS_HXX
