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

parser_options::options_grammar::options_grammar(parser_options::alphabet_t& arg_al,
						 parser_options::token_representation_t& arg_tok_rep)
: al(arg_al), tok_rep(arg_tok_rep)
{
}

parser_options::parser_options(const std::string& str)
{
  using namespace boost::spirit;
  options_grammar grammar(letters_, tok_rep_);

  BOOST_SPIRIT_DEBUG_NODE(grammar);

  parse_info<const char*> info = parse(str.c_str(), grammar);

  if (!info.full)
    throw;
}

const std::vector<std::string>&
parser_options::get_letters() { return letters_; }
const vcsn::algebra::token_representation_t&
parser_options::get_tok_rep() { return tok_rep_; }

template <typename ScannerT>
parser_options::options_grammar::definition<ScannerT>::definition(const parser_options::options_grammar& g)
: al_ref(g.al), tok_rep_ref(g.tok_rep)
{
  using namespace boost;
  using namespace boost::spirit;

  BOOST_SPIRIT_DEBUG_RULE(parser_properties);
  BOOST_SPIRIT_DEBUG_RULE(propertie);
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

#define NEW_TERMINAL_SYMBOL_STR(n, str) strlit<const char*> n(str)

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

#undef NEW_TERMINAL_SYMBOL_STR

#define NEW_TERMINAL_SYMBOL_SET(n, str) chset<> n(str)

  NEW_TERMINAL_SYMBOL_SET(space_c, " ");
  NEW_TERMINAL_SYMBOL_SET(equal  , "=");
  NEW_TERMINAL_SYMBOL_SET(obrack , "(");
  NEW_TERMINAL_SYMBOL_SET(comma  , ",");
  NEW_TERMINAL_SYMBOL_SET(cbrack , ")");
  NEW_TERMINAL_SYMBOL_SET(backs  , "\\");
  NEW_TERMINAL_SYMBOL_SET(colon  , ":");

#undef NEW_TERMINAL_SYMBOL_SET

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

  parser_properties = !list_p(propertie, space_c);
  propertie = ( alphabet     >> equal >> alphabet_definition ) |
              ( one          >> equal >> word[one_cb] ) |
              ( zero         >> equal >> word ) |
              ( opar >> equal >> character[open_par_cb] ) |
              ( cpar >> equal >> character[close_par_cb] ) |
              ( plus >> equal >> character[plus_cb] ) |
              ( times >> equal >> character[times_cb] ) |
              ( star >> equal >> character[star_cb] ) |
              ( oweight >> equal >> character[open_weight_cb] ) |
              ( cweight >> equal >> character[close_weight_cb] ) |
	      ( space >> equal >> character[push_space_cb] );
  // big fat warning: be carefull about spirit short-circuiting:
  // FIXME: it's ugly, we should add another letter trait.
  if (default_epsilon() == "1")
  {
    // it should be a char alphabet
    alphabet_definition = ( head_w >> colon >> !words ) |
                          ( !(head_l >> colon) >> !letters );
  }
  else
  {
    // it should be a word alphabet
    alphabet_definition = ( head_l >> colon >> !letters ) |
                          ( !(head_w >> colon) >> !words );
  }
  letters = *(letter[push_letter_cb]);
  words = !list_p(word[push_letter_cb], comma);
  word_pair = obrack >> word >> comma >> word >> cbrack;
  word = *letter;
  character = escaped_character | unescaped_character;
  letter = character | word_pair;
  escaped_character = backs >> special_character;
  unescaped_character = ~special_set;
  special_character = special_set;
}

template <typename ScannerT>
const boost::spirit::rule<ScannerT>&
parser_options::options_grammar::definition<ScannerT>::start() const
{
  return parser_properties;
}

template <typename ScannerT>
void
parser_options::options_grammar::definition<ScannerT>::push_letter(const char* from,
								   const char* to)
{
  al_ref.push_back(std::string(from, to));
}

template <typename ScannerT>
void
parser_options::options_grammar::definition<ScannerT>::open_par(const char* from,
								const char* to)
{
  tok_rep_ref.open_par = std::string(from, to);
}

template <typename ScannerT>
void
parser_options::options_grammar::definition<ScannerT>::close_par(const char* from,
								 const char* to)
{
  tok_rep_ref.close_par = std::string(from, to);
}

template <typename ScannerT>
void
parser_options::options_grammar::definition<ScannerT>::plus(const char* from,
							    const char* to)
{
  tok_rep_ref.plus = std::string(from, to);
}

template <typename ScannerT>
void
parser_options::options_grammar::definition<ScannerT>::times(const char* from,
							     const char* to)
{
  tok_rep_ref.times = std::string(from, to);
}

template <typename ScannerT>
void
parser_options::options_grammar::definition<ScannerT>::star(const char* from,
							    const char* to)
{
  tok_rep_ref.star = std::string(from, to);
}

template <typename ScannerT>
void
parser_options::options_grammar::definition<ScannerT>::open_weight(const char* from,
								   const char* to)
{
  tok_rep_ref.open_weight = std::string(from, to);
}

template <typename ScannerT>
void
parser_options::options_grammar::definition<ScannerT>::close_weight(const char* from,
								    const char* to)
{
  tok_rep_ref.close_weight = std::string(from, to);
}

template <typename ScannerT>
void
parser_options::options_grammar::definition<ScannerT>::push_space(const char* from,
								  const char* to)
{
  tok_rep_ref.spaces.push_back(std::string(from, to));
}

template <typename ScannerT>
void
parser_options::options_grammar::definition<ScannerT>::push_one(const char* from,
						      		const char* to)
{
  tok_rep_ref.one = std::string(from, to);
}

#endif // ! PARSER_OPTIONS_HXX
