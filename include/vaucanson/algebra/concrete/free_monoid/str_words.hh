// str_words.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGEBRA_STR_WORDS_HH
# define ALGEBRA_STR_WORDS_HH

# include <string>

# include <vaucanson/algebra/concrete/free_monoid/words.hh>
// Using this implementation of alphabet :
# include <vaucanson/algebra/concrete/alphabets/set_alphabet.hh>


namespace vcsn {

  /*------------------------------------------.
  | Implementation of words with basic_string |
  `------------------------------------------*/

  template <typename A>
  void 
  op_in_mul(const SetWords<A>& s, 
	    std::basic_string<typename A::letter_t>& dst,
	    const std::basic_string<typename A::letter_t>& src);
    
  template<typename A>
  std::basic_string<typename A::letter_t>
  op_mul(const SetWords<A>& s,
	 const std::basic_string<typename A::letter_t>& a,
	 const std::basic_string<typename A::letter_t>& b);

  template<typename A>
  const std::basic_string<typename A::letter_t>&
  identity_value(SELECTOR(SetWords<A>),
		 SELECTOR(std::basic_string<typename A::letter_t>));

  // one can create words from a single character
  template<typename A>
  std::basic_string<typename A::letter_t>
  op_convert(SELECTOR(std::basic_string<typename A::letter_t>),
	     SELECTOR(SetWords<A>), const typename A::letter_t& c);

  template <class A>
  Element<SetWords<A>, std::basic_string<typename A::letter_t> >
  op_choose(const SetWords<A>& s, 
	    SELECTOR(std::basic_string<typename A::letter_t>));



  /*------.
    | sugar |
    `------*/
  // Define the classical structuring element Words which denotes A*
  // implemented by alphabet implemented by std::set<char>.
  // Consequently, Word is the type of element structured by Words and
  // implemented by std::string.
  //

  typedef 
  algebra::SetWords<Element<Alphabets, std::set<char> > >  Words;
  typedef
  Element<Words, std::string>				  Word;

} // vcsn

# include <vaucanson/algebra/concrete/free_monoid/str_words.hxx>

#endif //  ALGEBRA_STR_WORDS_HH
