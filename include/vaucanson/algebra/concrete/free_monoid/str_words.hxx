// str_words.hxx
//
// VCSN_HEADER

#ifndef ALGEBRA_STR_WORDS_HXX
# define ALGEBRA_STR_WORDS_HXX

# include <vaucanson/algebra/concrete/free_monoid/str_words.hh>

namespace vcsn {

    template<typename A>
    void 
    op_in_mul(const TWords<A>& s, 
	      std::basic_string<typename A::letter_t>& dst,
	      const std::basic_string<typename A::letter_t>& src)
    { 
      dst += src; 
    }

    template<typename A>
    std::basic_string<typename A::letter_t>
    op_mul(const TWords<A>& s,
	   const std::basic_string<typename A::letter_t>& a,
	   const std::basic_string<typename A::letter_t>& b)
    { 
      return a + b; 
    }

    template<typename A>
    const std::basic_string<typename A::letter_t>&
    identity_value(SELECTOR(TWords<A>),
		   SELECTOR(std::basic_string<typename A::letter_t>))
    {
      static const std::basic_string<typename A::letter_t> instance;
      return instance;
    }

    // one can create words from a single char

    template<typename A>
    std::basic_string<typename A::letter_t>
    op_convert(SELECTOR(std::basic_string<typename A::letter_t>),
	       SELECTOR(TWords<A>), const typename A::letter_t& c)
    { 
      std::basic_string<typename A::letter_t> str; 
      str = c; 
      return str; 
    }

} // vcsn

#endif //  ALGEBRA_STR_WORDS_HXX
