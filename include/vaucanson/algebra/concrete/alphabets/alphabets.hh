// alphabets.hh
//
// VCSN_HEADER

#ifndef ALGEBRA_ALPHABETS_HH
# define ALGEBRA_ALPHABETS_HH

# include <vaucanson/algebra/concept/alphabets_base.hh>
# include <set>

namespace vcsn {
  namespace algebra {

    /*-------------.
    | SetAlphabets<L> |
    `-------------*/
    // 
    // Structuring element to define an alphabet
    //

    template<typename L>
    struct SetAlphabets
      : AlphabetsBase<SetAlphabets<L> >
    {
	typedef L		canonical_letter_t;
    };

  } // algebra

    /*------------------------.
    | MetaSet<SetAlphabets<L> |
    `------------------------*/
    //
    // Meta information about the structuring element
    //

    template<typename L>
    struct MetaSet<SetAlphabets<L> >
    {
      // by default an alphabet is a static object
      static const bool		dynamic_set = false;
    };     

} // vcsn 


#endif // ALGEBRA_ALPHABETS_HH

