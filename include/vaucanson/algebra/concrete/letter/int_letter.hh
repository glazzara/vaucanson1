#ifndef VCSN_ALGEBRA_CONCRETE_LETTER_INT_LETTER_HH
# define VCSN_ALGEBRA_CONCRETE_LETTER_INT_LETTER_HH

# include <vaucanson/algebra/concept/freemonoid_base.hh>
# include <string>
# include <iostream>

namespace vcsn {
  // Specialization for integers.
  template <typename S, typename U, typename V>
  bool op_parse(const algebra::FreeMonoidBase<S>& set,
		std::list<int>& v,
		const std::string& s,
		typename std::string::const_iterator& i,
		const std::list<char>& escaped);

} // vcsn

namespace std {

  ostream& operator<<(ostream& o, list<int> s);

}

#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/algebra/concrete/letter/int_letter.hxx>
#endif // VCSN_USE_INTERFACE_ONLY

#endif // VCSN_ALGEBRA_CONCRETE_LETTER_INT_LETTER_HH
