// words.hxx
//
// VCSN_HEADER

#ifndef ALGEBRA_WORDS_HXX
# define ALGEBRA_WORDS_HXX

# include <vaucanson/algebra/concrete/free_monoid/words.hh>

namespace vcsn {

  namespace algebra {

    /*---------.
    | Words<A> |
    `---------*/

    template <class A>
    inline SetWords<A>::SetWords() 
    {}
    
    template <class A>
    inline SetWords<A>::SetWords(const A& a) : alph_(a) 
    {}
    
    template <class A>
    inline SetWords<A>::SetWords(const SetWords& w) : 
      FreeMonoidBase<SetWords<A> >(w),
      alph_(w.alph_) 
    {}
    
    template <class A>
    inline A& SetWords<A>::alphabet()
    { 
      return alph_; 
    }
    
    template <class A>
    inline const A& SetWords<A>::alphabet() const
    { 
      return alph_; 
    }

  } // algebra
    
} // vcsn

template<typename A>
bool operator==(const vcsn::algebra::SetWords<A>& a,
		const vcsn::algebra::SetWords<A>& b)
{ 
  return a.alphabet() == b.alphabet(); 
}

#endif // ALGEBRA_WORDS_HXX

