// set_alphabet.hxx
//
// VCSN_HEADER

#ifndef ALGEBRA_SET_ALPHABET_HXX
# define ALGEBRA_SET_ALPHABET_HXX

# include <vaucanson/algebra/concrete/alphabets/set_alphabet.hh>

namespace vcsn
{
  namespace algebra
  {

    /*-----------------------------------------------------------.
    | Definition of an alphabet implementation based on std::set |
    `-----------------------------------------------------------*/
    template<typename L>
    bool op_contains(const SetAlphabets<L>& s, const std::set<L>& a)
    { 
      return true; 
    }

    template<typename L>
    bool op_is_finite(const SetAlphabets<L>& s, const std::set<L>& a)
    { 
      return true; 
    }

    template<typename L>
    bool op_contains_e(const SetAlphabets<L>& s, const std::set<L>& a,
		       const L& v)
    { 
      return a.find(v) != a.end(); 
    }

  } // algebra
} // vcsn
 
#endif // ALGEBRA_SET_ALPHABET_HXX
