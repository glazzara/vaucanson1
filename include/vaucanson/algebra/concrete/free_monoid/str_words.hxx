// str_words.hxx
//
// $Id$
// VCSN_HEADER
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
