// set_alphabet.hh
//
// VCSN_HEADER

#ifndef ALGEBRA_SET_ALPHABET_HH
# define ALGEBRA_SET_ALPHABET_HH

# include <vaucanson/algebra/concrete/alphabets/alphabets.hh>

namespace vcsn {

  namespace algebra {


    /*-----------------------------------------------------------.
    | Definition of an alphabet implementation based on std::set |
    `-----------------------------------------------------------*/
    template<typename L>
    struct alphabet_traits<Alphabets<L>, std::set<L> >
    {
      typedef L			letter_t;
    };

  } // algebra

    template<typename L>
    struct MetaElement<Alphabets<L>, std::set<L> >
      : MetaElement<AlphabetsBase<Alphabets<L> >, std::set<L> >
    {
      static const bool dynamic_values = true;
    };

    template<typename L>
    bool op_contains(const Alphabets<L>& s, const std::set<L>& a);

    template<typename L>
    bool op_is_finite(const Alphabets<L>& s, const std::set<L>& a);

    template<typename L>
    bool op_contains_e(const Alphabets<L>& s, const std::set<L>& a,
		       const L& v);

  namespace sugar {
  
  /*----------------------------------.
  | Define some useful alphabet stuff |
  `----------------------------------*/
    typedef algebra::Alphabets<char>				Alphabets;
    typedef Element<Alphabets, std::set<char> >			Alphabet;

  } // sugar

} // vcsn

# include <vaucanson/algebra/concrete/alphabets/set_alphabet.hxx>
 
#endif // ALGEBRA_SET_ALPHABET_HH
