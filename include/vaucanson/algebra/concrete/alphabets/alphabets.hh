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
    | Alphabets<L> |
    `-------------*/
    // 
    // Structuring element to define an alphabet
    //

    template<typename L>
    struct Alphabets
      : AlphabetsBase<Alphabets<L> >
    {
	typedef L		canonical_letter_t;
    };

  } // algebra

    /*---------------------.
    | MetaSet<Alphabets<L> |
    `---------------------*/
    //
    // Meta information about the structuring element
    //

    template<typename L>
    struct MetaSet<Alphabets<L> >
    {
      // by default an alphabet is a static object
      static const bool		dynamic_set = false;
    };     

} // vcsn 


#endif // ALGEBRA_ALPHABETS_HH

