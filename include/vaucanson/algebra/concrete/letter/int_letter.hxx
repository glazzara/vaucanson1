#ifndef VCSN_ALGEBRA_CONCRETE_LETTER_INT_LETTER_HXX
# define VCSN_ALGEBRA_CONCRETE_LETTER_INT_LETTER_HXX

# include <vaucanson/algebra/concrete/letter/int_letter.hh>

namespace vcsn {

  template <typename S>
  bool op_parse(const algebra::FreeMonoidBase<S>& set,
		std::list<int>& v,
		const std::string& s,
		typename std::string::const_iterator& i,
		const std::list<char>& escaped)
  {
    typename std::string::const_iterator j = i;
    typename std::string::const_iterator k;
    typename std::string::const_iterator back;

    while ((i != s.end()) &&
	   (std::find(escaped.begin(), escaped.end(), *i) == escaped.end())) {
      std::string out;
      back = i;

      while ((i != s.end()) && (((*i >= '0') && (*i <= '9'))) || (*i == '\\'))
	if (*i == '\\') {
	  k = i;
	  ++k;
	  if (k != s.end())
	    i = k;
	  out += *i;
	  ++i;
	}
	else {
	  out += *i;
	  ++i;
	}

      int value;
      std::istringstream is(out);
      is >> value;
      if (!set.alphabet().contains(value)) {
	i = back;
	break ;
      }
      v.push_back(value);
    }
    return (i != j);
  }

} // vcsn

namespace std {

  ostream& operator<<(ostream& o, list<int> s)
  {
    list<int>::const_iterator i;
    list<int>::const_iterator j;

    for (i = s.begin(); i != s.end(); ) {
      o << *i;
      i++;
      if (i != s.end())
	o << ",";
    }

    return o;
  }

} // std

#endif // VCSN_ALGEBRA_CONCRETE_LETTER_COUPLE_LETTER_HXX
