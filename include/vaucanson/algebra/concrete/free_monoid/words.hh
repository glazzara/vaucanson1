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
    | SetWords<A> |
    `---------*/

    template<typename A>
    struct SetWords 
      : FreeMonoidBase<SetWords<A> >
    {
      typedef A alphabets_elt_t;

      // in case of default constructor, do not forget to attach an
      // alphabet, otherwise the alphabet is empty.
      SetWords();
      SetWords(const A& a);
      SetWords(const SetWords& w);

      A&	alphabet();
      const A&	alphabet() const;

    protected:
      A alph_;
    };

  }

    /*-------------------.
    | MetaSet<SetWords<A> > |
    `-------------------*/
    template<typename A>
    struct MetaSet<SetWords<A> >
    {
      static const bool		dynamic_set = A::dynamic;
      typedef algebra::mul_kind semigroup_kind;
      typedef A			alphabet_t;
    };

    /*-------------------------.
    | MetaElement<SetWords<A>, T> |
    `-------------------------*/
    template<typename A, typename T>
    struct MetaElement<SetWords<A>, T>
      : MetaElement<FreeMonoidBase<SetWords<A> >, T>
    {};

  namespace traits {
    
    template<typename A>
    struct virtual_types<algebra::SetWords<A> >
    {
      typedef A alphabet_t;
    };

  } // traits

} // vcsn

template<typename A>
bool operator==(const vcsn::algebra::SetWords<A>& a,
		const vcsn::algebra::SetWords<A>& b);

# include <vaucanson/algebra/concrete/free_monoid/words.hxx>

#endif // ALGEBRA_WORDS_HH

