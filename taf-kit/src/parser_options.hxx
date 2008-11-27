// parser_options.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//

#ifndef PARSER_OPTIONS_HXX
# define PARSER_OPTIONS_HXX

# include "parser_options.hh"

template <typename M, typename S>
parser_options<M, S>::options_grammar::options_grammar(typename parser_options<M, S>::alphabet_t&
						       arg_al,
						       M& arg_mrep,
						       S& arg_srep)
: al(arg_al), mrep(arg_mrep), srep(arg_srep)
{
}

template <typename M, typename S>
parser_options<M, S>::parser_options(const std::string& str)
{
  using namespace boost::spirit;
  options_grammar grammar(letters_, mrep_, srep_);

  BOOST_SPIRIT_DEBUG_NODE(grammar);

  parse_info<const char*> info = parse(str.c_str(), grammar);

  if (!info.full)
    throw std::logic_error(std::string("unexpected token: ") + info.stop);
}

template <typename M, typename S>
const std::vector<std::string>&
parser_options<M, S>::get_letters()
{
  return letters_;
}

template <typename M, typename S>
const M&
parser_options<M, S>::get_mrep()
{
  return mrep_;
}

template <typename M, typename S>
const S&
parser_options<M, S>::get_srep()
{
  return srep_;
}

template <typename M, typename S>
bool
parser_options<M, S>::rec_check_collision(const std::string& str, std::string::const_iterator it_str_curr)
{
  std::string::const_iterator it_str;
  for_all(std::vector<std::string>, it_vect, letters_)
  {
    std::string::const_iterator it_let = it_vect->begin();
    it_str = it_str_curr;
    while (it_str != str.end() &&
	   it_let != it_vect->end() &&
	   *it_let == *it_str)
    {
      it_str++;
      it_let++;
    }
    // if we reach the end of str by adding or not some other letter return true
    if (it_str == str.end() || (it_let == it_vect->end() && rec_check_collision(str, it_str)))
      return true;
  }
  return false;
}

template <typename M, typename S>
bool
parser_options<M, S>::check_collision(const std::string& str)
{
  std::string::const_iterator it_str;
  for_all(std::vector<std::string>, it_vect, letters_)
  {
    std::string::const_iterator it_let = it_vect->begin();
    it_str = str.begin();
    while (it_let != it_vect->end() &&
	   *it_let != *it_str)
      it_let++;
    while (it_str != str.end() &&
	   it_let != it_vect->end() &&
	   *it_let == *it_str)
    {
      it_str++;
      it_let++;
    }
    // if we reach the end of str by adding or not some other letter return true
    if (it_str == str.end() || (it_let == it_vect->end() && rec_check_collision(str, it_str)))
      return true;
  }
  return false;
}

template <typename M, typename S>
void
parser_options<M, S>::check_collision()
{
#define CHECK_COLISION(TOKEN, NAME)						\
  if (check_collision(TOKEN))							\
    std::cerr << "Warning: The token " << NAME <<				\
		 " could also be a part of a word in your alphabet." << std::endl;
  CHECK_COLISION(srep_.open_par, "OPAR")
  CHECK_COLISION(srep_.close_par, "CPAR")
  CHECK_COLISION(srep_.plus, "PLUS")
  CHECK_COLISION(srep_.times, "TIMES")
  CHECK_COLISION(srep_.star, "STAR")
  CHECK_COLISION(srep_.open_weight, "OWEIGHT")
  CHECK_COLISION(mrep_.empty, "ONE")
  CHECK_COLISION(mrep_.concat, "CONCAT")
  CHECK_COLISION(srep_.zero, "ZERO")
  for_all(std::vector<std::string>, it, srep_.spaces)
    CHECK_COLISION(*it, "SPACE")
#undef CHECK_COLISION
}

template <typename M, typename S>
template <typename ScannerT>
parser_options<M, S>::options_grammar::definition<ScannerT>::definition(const parser_options::options_grammar& g)
: al_ref(g.al), mrep_ref(g.mrep), srep_ref(g.srep)
{
  using namespace boost;
  using namespace boost::spirit;

  BOOST_SPIRIT_DEBUG_RULE(parser_properties);
  BOOST_SPIRIT_DEBUG_RULE(property);
  BOOST_SPIRIT_DEBUG_RULE(alphabet_definition);
  BOOST_SPIRIT_DEBUG_RULE(letters);
  BOOST_SPIRIT_DEBUG_RULE(words);
  BOOST_SPIRIT_DEBUG_RULE(special_name);
  BOOST_SPIRIT_DEBUG_RULE(word_pair);
  BOOST_SPIRIT_DEBUG_RULE(word);
  BOOST_SPIRIT_DEBUG_RULE(character);
  BOOST_SPIRIT_DEBUG_RULE(letter);
  BOOST_SPIRIT_DEBUG_RULE(escaped_character);
  BOOST_SPIRIT_DEBUG_RULE(unescaped_character);
  BOOST_SPIRIT_DEBUG_RULE(special_character);

# define NEW_TERMINAL_SYMBOL_STR(n, str) strlit<const char*> n(str)

  NEW_TERMINAL_SYMBOL_STR(head_l  , "letters");
  NEW_TERMINAL_SYMBOL_STR(head_w  , "words");
  NEW_TERMINAL_SYMBOL_STR(alphabet, "ALPHABET");
  NEW_TERMINAL_SYMBOL_STR(one     , "ONE");
  NEW_TERMINAL_SYMBOL_STR(zero    , "ZERO");
  NEW_TERMINAL_SYMBOL_STR(opar    , "OPAR");
  NEW_TERMINAL_SYMBOL_STR(cpar    , "CPAR");
  NEW_TERMINAL_SYMBOL_STR(plus    , "PLUS");
  NEW_TERMINAL_SYMBOL_STR(times   , "TIMES");
  NEW_TERMINAL_SYMBOL_STR(star    , "STAR");
  NEW_TERMINAL_SYMBOL_STR(oweight , "OWEIGHT");
  NEW_TERMINAL_SYMBOL_STR(cweight , "CWEIGHT");
  NEW_TERMINAL_SYMBOL_STR(space   , "SPACE");
  NEW_TERMINAL_SYMBOL_STR(concat  , "CONCAT");

# undef NEW_TERMINAL_SYMBOL_STR

# define NEW_TERMINAL_SYMBOL_SET(n, str) chset<> n(str)

  NEW_TERMINAL_SYMBOL_SET(space_c, " ");
  NEW_TERMINAL_SYMBOL_SET(equal  , "=");
  NEW_TERMINAL_SYMBOL_SET(obrack , "(");
  NEW_TERMINAL_SYMBOL_SET(comma  , ",");
  NEW_TERMINAL_SYMBOL_SET(cbrack , ")");
  NEW_TERMINAL_SYMBOL_SET(backs  , "\\");
  NEW_TERMINAL_SYMBOL_SET(colon  , ":");

# undef NEW_TERMINAL_SYMBOL_SET

  // special characters set
  chset<> special_set = space_c | equal | obrack |
                        comma | cbrack | backs | colon;

  push_letter_cb  = bind(&self_t::push_letter	 , this, _1, _2);
  open_par_cb	  = bind(&self_t::open_par	 , this, _1, _2);
  close_par_cb	  = bind(&self_t::close_par	 , this, _1, _2);
  plus_cb	  = bind(&self_t::plus		 , this, _1, _2);
  times_cb	  = bind(&self_t::times		 , this, _1, _2);
  star_cb	  = bind(&self_t::star		 , this, _1, _2);
  open_weight_cb  = bind(&self_t::open_weight    , this, _1, _2);
  close_weight_cb = bind(&self_t::close_weight   , this, _1, _2);
  push_space_cb	  = bind(&self_t::push_space     , this, _1, _2);
  one_cb	  = bind(&self_t::push_one       , this, _1, _2);
  zero_cb	  = bind(&self_t::push_zero      , this, _1, _2);
  concat_cb	  = bind(&self_t::push_concat	 , this, _1, _2);

  parser_properties = !list_p(property, space_c);
  property = ( alphabet     >> equal >> alphabet_definition ) |
             ( one          >> equal >> word[one_cb] ) |
             ( zero         >> equal >> word[zero_cb] ) |
             ( opar >> equal >> word[open_par_cb] ) |
             ( cpar >> equal >> word[close_par_cb] ) |
             ( plus >> equal >> word[plus_cb] ) |
             ( times >> equal >> word[times_cb] ) |
             ( star >> equal >> word[star_cb] ) |
             ( oweight >> equal >> word[open_weight_cb] ) |
             ( cweight >> equal >> word[close_weight_cb] ) |
             ( concat >> equal >> word[concat_cb] ) |
	     ( space >> equal >> word[push_space_cb] );

  letters = *(letter[push_letter_cb]);
  words = !list_p(word[push_letter_cb], comma);
  word_pair = obrack >> word >> comma >> word >> cbrack;
  word = *letter;
  character = escaped_character | unescaped_character;
  letter = character | word_pair;
  escaped_character = backs >> anychar_p;
  unescaped_character = ~special_set;

  // be carefull about spirit short-circuiting
  true_is_char_letter =	( head_w >> colon >> !words ) |
			( !(head_l >> colon) >> !letters );
  false_is_char_letter = ( head_l >> colon >> !letters ) |
			 ( !(head_w >> colon) >> !words );

  if_is_char_letter(
		    // assignee
		    alphabet_definition,
		    // true case
		    true_is_char_letter,
		    // false case
		    false_is_char_letter
		   );
}

template <typename M, typename S>
template <typename ScannerT>
std::string
parser_options<M, S>::options_grammar::definition<ScannerT>::escape(const char* from,
								    const char* to)
{
  std::string res;
  while (from != to)
  {
    if (*from == '\\')
      from++;
    res += *from;
    from++;
  }
  return res;
}

template <typename M, typename S>
template <typename ScannerT>
const boost::spirit::rule<ScannerT>&
parser_options<M, S>::options_grammar::definition<ScannerT>::start() const
{
  return parser_properties;
}

template <typename M, typename S>
template <typename ScannerT>
void
parser_options<M, S>::options_grammar::definition<ScannerT>::push_letter(const char* from,
									 const char* to)
{
  al_ref.push_back(escape(from, to));
}

template <typename M, typename S>
template <typename ScannerT>
void
parser_options<M, S>::options_grammar::definition<ScannerT>::open_par(const char* from,
								      const char* to)
{
  srep_ref.open_par = escape(from, to);
}

template <typename M, typename S>
template <typename ScannerT>
void
parser_options<M, S>::options_grammar::definition<ScannerT>::close_par(const char* from,
								       const char* to)
{
  srep_ref.close_par = escape(from, to);
}

template <typename M, typename S>
template <typename ScannerT>
void
parser_options<M, S>::options_grammar::definition<ScannerT>::plus(const char* from,
								  const char* to)
{
  srep_ref.plus = escape(from, to);
}

template <typename M, typename S>
template <typename ScannerT>
void
parser_options<M, S>::options_grammar::definition<ScannerT>::times(const char* from,
								   const char* to)
{
  srep_ref.times = escape(from, to);
}

template <typename M, typename S>
template <typename ScannerT>
void
parser_options<M, S>::options_grammar::definition<ScannerT>::star(const char* from,
								  const char* to)
{
  srep_ref.star = escape(from, to);
}

template <typename M, typename S>
template <typename ScannerT>
void
parser_options<M, S>::options_grammar::definition<ScannerT>::open_weight(const char* from,
									 const char* to)
{
  srep_ref.open_weight = escape(from, to);
}

template <typename M, typename S>
template <typename ScannerT>
void
parser_options<M, S>::options_grammar::definition<ScannerT>::close_weight(const char* from,
									  const char* to)
{
  srep_ref.close_weight = escape(from, to);
}

template <typename M, typename S>
template <typename ScannerT>
void
parser_options<M, S>::options_grammar::definition<ScannerT>::push_space(const char* from,
									const char* to)
{
  static bool first = true;
  if (first)
    srep_ref.spaces.clear();
  srep_ref.spaces.push_back(escape(from, to));
  first = false;
}

template <typename M, typename S>
template <typename ScannerT>
void
parser_options<M, S>::options_grammar::definition<ScannerT>::push_one(const char* from,
								      const char* to)
{
  mrep_ref.empty = escape(from, to);
}

template <typename M, typename S>
template <typename ScannerT>
void
parser_options<M, S>::options_grammar::definition<ScannerT>::push_concat(const char* from,
									 const char* to)
{
  mrep_ref.concat = escape(from, to);
}

template <typename M, typename S>
template <typename ScannerT>
void
parser_options<M, S>::options_grammar::definition<ScannerT>::push_zero(const char* from,
								       const char* to)
{
  srep_ref.zero = escape(from, to);
}

#endif // ! PARSER_OPTIONS_HXX
