// str_words.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_STR_WORDS_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_STR_WORDS_HXX

# include <vaucanson/algebra/implementation/free_monoid/str_words.hh>

# include <vaucanson/misc/char_traits.hh>

namespace vcsn {

  template<typename A>
  void
  op_in_mul(const algebra::FreeMonoid<A>&,
	    std::basic_string<typename A::letter_t>& dst,
	    const std::basic_string<typename A::letter_t>& src)
  {
    dst += src;
  }

  template<typename A>
  std::basic_string<typename A::letter_t>
  op_mul(const algebra::FreeMonoid<A>&,
	 const std::basic_string<typename A::letter_t>& a,
	 const std::basic_string<typename A::letter_t>& b)
  {
    return a + b;
  }

  template <typename A>
  bool
  op_xeq(const algebra::FreeMonoid<A>& s,
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
  identity_value(SELECTOR(algebra::FreeMonoid<A>),
		 SELECTOR(std::basic_string<typename A::letter_t>))
  {
    static const std::basic_string<typename A::letter_t> instance;
    return instance;
  }

  template<typename A>
  const std::basic_string<typename A::letter_t,
			  utility::char_traits<typename A::letter_t> >&
  identity_value(SELECTOR(algebra::FreeMonoid<A>),
		 SELECTOR2(std::basic_string<typename A::letter_t,
			  utility::char_traits<typename A::letter_t> >))
  {
    static const std::basic_string<typename A::letter_t,
      utility::char_traits<typename A::letter_t> > instance;
    return instance;
  }
  
  template<typename A>
  std::basic_string<typename A::letter_t>
  op_convert(SELECTOR(algebra::FreeMonoid<A>),
	     SELECTOR(std::basic_string<typename A::letter_t>),
	     const typename A::letter_t& c)
  {
    std::basic_string<typename A::letter_t> str;
    str = c;
    return str;
  }

  template <class A>
  Element<algebra::FreeMonoid<A>, std::basic_string<typename A::letter_t> >
  op_choose(const algebra::FreeMonoid<A>& s,
	    SELECTOR(std::basic_string<typename A::letter_t>))
  {
    unsigned length =
      utility::random::generate<unsigned>(0, op_choose_max_word_length);
    std::basic_string<typename A::letter_t> r;
    for (unsigned i = 0; i < length; ++i)
      r = r + s.alphabet().choose();
    return Element<algebra::FreeMonoid<A>,
      std::basic_string<typename A::letter_t> >(s, r);
  }

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_FREE_MONOID_STR_WORDS_HXX
