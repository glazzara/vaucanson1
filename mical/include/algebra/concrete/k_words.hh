// k_words.hh
// 
// MICAL_HEADER

#ifndef   K_WORDS_HH_
# define   K_WORDS_HH_

# include <string>
# include <algebra/concept/k_monoid_base.hh>
# include <vaucanson/algebra/concrete/alphabets/set_alphabet.hh>

namespace vcsn {

  namespace algebra {
 
    template<typename A>
    struct KMonoid 
      : KMonoidBase<KMonoid<A> >
    {
      typedef A alphabets_elt_t;

      KMonoid(unsigned k);
      KMonoid(unsigned k, const A& a);
      KMonoid(const KMonoid& w);

      A&	alphabet();
      const A&	alphabet() const;

      unsigned window() const;

    protected:
      A alph_;
      unsigned k_;
    };


  } // algebra


  template<typename A>
  struct MetaSet<KMonoid<A> >
  {
    static const bool		dynamic_set = true;
    
    typedef algebra::mul_kind semigroup_kind;

    typedef A			alphabet_t;
  };
  
  template<typename A, typename T>
  struct MetaElement<KMonoid<A>, T>
    : MetaElement<KMonoidBase<KMonoid<A> >, T>
  {
    //MetaElement(unsigned k);
  };
  
  namespace traits {
    
    template <class A>
    struct virtual_types<KMonoid<A> >
    {
      typedef A		alphabet_t;
    };
    
  } // traits
  
template<typename A>
bool operator==(const vcsn::algebra::KMonoid<A>& a,
		const vcsn::algebra::KMonoid<A>& b);

template<typename A>
void op_insert(const KMonoidBase<A>&,
	       std::string& str, 
	       typename KMonoidBase<A>::letter_t l,
	       unsigned k);

template <typename A>
void 
op_in_mul(const KMonoid<A>& s, 
	  std::string& dst,
	  const std::string& src);
    
template<typename A>
std::string
op_mul(const KMonoid<A>& s,
       const std::string& a,
       const std::string& b);

template <typename A>
bool
op_xeq(const KMonoid<A>& s, 
       const std::string& a, 
       const std::string& b);

  template<typename A>
  const std::string&
  identity_value(SELECTOR(KMonoid<A>),
		 SELECTOR(std::string));
 
template<typename A>
std::string
op_convert(SELECTOR(std::string),
	   SELECTOR(KMonoid<A>), 
	   const typename A::letter_t& c);

} // vcsn

# include <algebra/concrete/k_words.hxx>


#endif /* !K_WORDS_HH_ */
