// str_words.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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
  op_in_mul(const SetWords<A>& s, 
	    std::basic_string<typename A::letter_t>& dst,
	    const std::basic_string<typename A::letter_t>& src)
  { 
    dst += src; 
  }

  template<typename A>
  std::basic_string<typename A::letter_t>
  op_mul(const SetWords<A>& s,
	 const std::basic_string<typename A::letter_t>& a,
	 const std::basic_string<typename A::letter_t>& b)
  { 
    return a + b; 
  }

  template<typename A>
  const std::basic_string<typename A::letter_t>&
  identity_value(SELECTOR(SetWords<A>),
		 SELECTOR(std::basic_string<typename A::letter_t>))
  {
    static const std::basic_string<typename A::letter_t> instance;
    return instance;
  }

  template<typename A>
  std::basic_string<typename A::letter_t>
  op_convert(SELECTOR(std::basic_string<typename A::letter_t>),
	     SELECTOR(SetWords<A>), const typename A::letter_t& c)
  { 
    std::basic_string<typename A::letter_t> str; 
    str = c; 
    return str; 
  }

  template <class A>
  Element<SetWords<A>, std::basic_string<typename A::letter_t> >
  op_choose(const SetWords<A>& s, 
	    SELECTOR(std::basic_string<typename A::letter_t>))
  {
    // FIXME : use global constants to define this !
    unsigned length = ((unsigned) trunc(((float) random() / (float) RAND_MAX) * 5));
    std::basic_string<typename A::letter_t> r;
    for (unsigned i = 0; i < length; ++i)
      r = r + s.alphabet().choose();
    return Element<SetWords<A>, std::basic_string<typename A::letter_t> >(r);
  }

} // vcsn

#endif //  ALGEBRA_STR_WORDS_HXX
