// words.hh
//
// VCSN_HEADER
#ifndef ALGEBRA_WORDS_HH
# define ALGEBRA_WORDS_HH

# include <string>

# include <vaucanson/algebra/concept/freemonoid_base.hh>
// # include <vaucanson/algebra/concrete/alphabets.hh>

namespace vcsn {

  namespace algebra {

    /*---------.
    | TWords<A> |
    `---------*/

    template<typename A>
    struct TWords 
      : FreeMonoidBase<TWords<A> >
    {
      // in case of default constructor, do not forget to attach an
      // alphabet, otherwise the alphabet is empty.
      TWords();
      TWords(const A& a);
      TWords(const TWords& w);

      A&	alphabet();
      const A&	alphabet() const;

    protected:
      A alph_;
    };

  }

    /*-------------------.
    | MetaSet<TWords<A> > |
    `-------------------*/
    template<typename A>
    struct MetaSet<TWords<A> >
    {
      static const bool		dynamic_set = A::dynamic;
      typedef algebra::mul_kind semigroup_kind;
      typedef A			alphabet_t;
    };

    /*-------------------------.
    | MetaElement<TWords<A>, T> |
    `-------------------------*/
    template<typename A, typename T>
    struct MetaElement<TWords<A>, T>
      : MetaElement<FreeMonoidBase<TWords<A> >, T>
    {};

  namespace traits {
    
    template<typename A>
    struct virtual_types<algebra::TWords<A> >
    {
      typedef A alphabet_t;
    };

  } // traits

} // vcsn

template<typename A>
bool operator==(const vcsn::algebra::TWords<A>& a,
		const vcsn::algebra::TWords<A>& b);

# include <vaucanson/algebra/concrete/free_monoid/words.hxx>

#endif // ALGEBRA_WORDS_HH

