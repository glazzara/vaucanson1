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
    inline TWords<A>::TWords() 
    {}
    
    template <class A>
    inline TWords<A>::TWords(const A& a) : alph_(a) 
    {}
    
    template <class A>
    inline TWords<A>::TWords(const TWords& w) : 
      FreeMonoidBase<TWords<A> >(w),
      alph_(w.alph_) 
    {}
    
    template <class A>
    inline A& TWords<A>::alphabet()
    { 
      return alph_; 
    }
    
    template <class A>
    inline const A& TWords<A>::alphabet() const
    { 
      return alph_; 
    }

  } // algebra
    
} // vcsn

template<typename A>
bool operator==(const vcsn::algebra::TWords<A>& a,
		const vcsn::algebra::TWords<A>& b)
{ 
  return a.alphabet() == b.alphabet(); 
}

#endif // ALGEBRA_WORDS_HXX

