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
    struct alphabet_traits<SetAlphabets<L>, std::set<L> >
    {
      typedef L			letter_t;
    };

  } // algebra

    template<typename L>
    struct MetaElement<SetAlphabets<L>, std::set<L> >
      : MetaElement<AlphabetsBase<SetAlphabets<L> >, std::set<L> >
    {
      static const bool dynamic_values = true;
    };

    template<typename L>
    bool op_contains(const SetAlphabets<L>& s, const std::set<L>& a);

    template<typename L>
    bool op_is_finite(const SetAlphabets<L>& s, const std::set<L>& a);

    template<typename L>
    bool op_contains_e(const SetAlphabets<L>& s, const std::set<L>& a, 
		       const L& v);

  /*----------------------------------.
  | Define some useful alphabet stuff |
  `----------------------------------*/
    typedef algebra::SetAlphabets<char>				Alphabets;
    typedef Element<Alphabets, std::set<char> >			Alphabet;

} // vcsn

# include <vaucanson/algebra/concrete/alphabets/set_alphabet.hxx>
 
#endif // ALGEBRA_SET_ALPHABET_HH
