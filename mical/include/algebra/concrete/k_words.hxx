// k_words.hxx
//
// MICAL_HEADER

#ifndef K_WORDS_HXX
# define K_WORDS_HXX

# include <algebra/concrete/k_words.hh>

namespace vcsn {

  namespace algebra {

    /*---------.
    | Words<A> |
    `---------*/

    template <class A>
    KMonoid<A>::KMonoid(unsigned k) : k_(k) 
    {}

    template <class A>
    KMonoid<A>::KMonoid(unsigned k, const A& a) : k_(k), alph_(a) 
    {}
    
    template <class A>
    KMonoid<A>::KMonoid(const KMonoid& w) : 
      KMonoidBase<KMonoid<A> >(w),
      alph_(w.alph_) 
    {}
    
    template <class A>
    A& KMonoid<A>::alphabet()
    { 
      return alph_; 
    }
    
    template <class A>
    const A& KMonoid<A>::alphabet() const
    { 
      return alph_; 
    }
    template <class A>
    unsigned  KMonoid<A>::window() const
    {
      return k_;
    }

  } // algebra

  using namespace algebra;

//   template<class A, typename T>
//   MetaElement<KMonoid<A>, T>::MetaElement(unsigned k) :
//     MetaElement<KMonoidBase<KMonoid<A> >, T>(k)
//   {}

  template<typename A>
  bool operator==(const vcsn::algebra::KMonoid<A>& a,
		  const vcsn::algebra::KMonoid<A>& b)
  { 
    return a.alphabet() == b.alphabet(); 
  }
  
  template<typename A>
  void op_insert(const KMonoidBase<A>&,
		 std::string& str, 
		 typename KMonoidBase<A>::letter_t l,
		 unsigned k)
  {
    while (str.size() >= k)
      str.erase(str.begin());

    std::string tmp = l;
    str = str * tmp;
  }
  
  template <typename A>
  void 
  op_in_mul(const KMonoid<A>& s, 
	    std::string& dst,
	    const std::string& src)
  { 
    dst += src; 
    while (dst.size() >= s.window())
      dst.erase(dst.begin());
  }

  template<typename A>
  std::string
  op_mul(const KMonoid<A>& s,
	 const std::string& a,
	 const std::string& b)
  { 
     std::string res = a + b; 

     while (res.size() >= K)
       res.erase(res.begin());

     return res;
  }

  template <typename A>
  bool
  op_xeq(const KMonoid<A>& s, 
	 const std::string& a, 
	 const std::string& b)
  {
    typename std::string::const_iterator 
      m = b.begin();
    typename std::string::const_iterator l;
    for (l = a.begin(); m != b.end() && l != a.end(); ++l)
      {
	if (! s.alphabet().letter_equality(*l, *m))
	  return false;
	++m;
      }
    return (m == b.end() && l == a.end());
  }
  
  template<typename A>
  const std::string&
  identity_value(SELECTOR(KMonoid<A>),
		 SELECTOR(std::string))
  {
    static const std::string instance;
    return instance;
  }


  template<typename A>
  std::string
  op_convert(SELECTOR(std::string),
	     SELECTOR(KMonoid<A>), 
	     const typename A::letter_t& c)
  { 
    std::string str; 
    str = c; 
    return str; 
  }
 

} // vcsn

#endif // K_WORDS_HXX
