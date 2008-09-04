// parser_options.hh: this file is part of the Vaucanson project.
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

#ifndef PARSER_OPTIONS_HH
# define PARSER_OPTIONS_HH

// debug purpose only
# if 0
#  define BOOST_SPIRIT_DEBUG
# endif

# include <string>
# include <vector>

# include <boost/bind.hpp>
# include <boost/function.hpp>
# include <boost/spirit/core.hpp>
# include <boost/spirit/utility/lists.hpp>
# include <boost/spirit/utility/chset.hpp>

# include <vaucanson/misc/static.hh>

/**
 * @file parser_options.hh
 * @author Jerome Galtier <jerome.galtier@lrde.epita.fr>
 *
 * This file defines the parser, for the following grammar:
 * (EBNF notations)
 *
 * @verbatim
 * parser-properties ::= [ propertie { ' ' propertie } ];
 * propertie ::= ( "ALPHABET"   '=' alphabet-definition ) |
 *               ( "ONE"        '=' word ) |
 *               ( "ZERO"       '=' word ) |
 *               ( special-name '=' character );
 * alphabet-definition ::= ( "words" ':' [ words ] ) |
 *                         ( [ "letters" ':' ] [ letters ] );
 * letters ::= letter*;
 * words ::= [ word { ',' word } ];
 * special-name ::= "OPAR" | "CPAR" | "PLUS" | "TIMES" |
 *                  "STAR" | "OWEIGHT" | "CWEIGHT" | "SPACE";
 * word-pair ::= '(' word ',' word ')';
 * word ::= letter*;
 * character ::= escaped-character | unescaped-character;
 * letter ::= character | word-pair;
 * escaped-character ::= '\' special-character;
 * unescaped-letter ::= ? all characters excluding special-character ?;
 * special-character ::= ' ' | '=' | '(' | ',' | ')' | '\' | ':';
 * @endverbatim
 */

class parser_options
{
public:

  parser_options(const std::string&);

  const std::vector<std::string>&
  get_letters();
  const vcsn::algebra::token_representation_t&
  get_tok_rep();
  void
  check_collision();

private:
  bool
  rec_check_collision(const std::string& str, std::string::const_iterator it_str_curr);
  bool
  check_collision(const std::string& str);

  // type helpers
  typedef std::vector<std::string> alphabet_t;
  typedef vcsn::algebra::token_representation_t token_representation_t;

  struct options_grammar : public boost::spirit::grammar<options_grammar>
  {
    // CTOR
    options_grammar(alphabet_t& al, token_representation_t& tok_rep);

    template <typename ScannerT>
    struct definition
    {
      // type helpers
      typedef typename parser_options::options_grammar::definition<ScannerT> self_t;

      boost::spirit::rule<ScannerT> parser_properties, propertie,
      alphabet_definition, letters, words, special_name, word_pair,
      word, character, letter, escaped_character, unescaped_character,
      special_character, true_is_char_letter, false_is_char_letter;

      // CTOR
      definition(const options_grammar& g);

      const boost::spirit::rule<ScannerT>&
      start() const;

      // callbacks
      boost::function<void(const char*, const char*)> push_letter_cb;
      boost::function<void(const char*, const char*)> open_par_cb;
      boost::function<void(const char*, const char*)> close_par_cb;
      boost::function<void(const char*, const char*)> plus_cb;
      boost::function<void(const char*, const char*)> times_cb;
      boost::function<void(const char*, const char*)> star_cb;
      boost::function<void(const char*, const char*)> open_weight_cb;
      boost::function<void(const char*, const char*)> close_weight_cb;
      boost::function<void(const char*, const char*)> push_space_cb;
      boost::function<void(const char*, const char*)> one_cb;
      boost::function<void(const char*, const char*)> zero_cb;

      // reference to parser_options creator
      parser_options::alphabet_t& al_ref;
      parser_options::token_representation_t& tok_rep_ref;

      /**
       * Callback function called to push a new letter into
       * the alphabet vector.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      push_letter(const char* from,
		  const char* to);

      /**
       * Callback function called to set open_par token representation
       * into the token_representation structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      open_par(const char* from,
	       const char* to);

      /**
       * Callback function called to set close_par token representation
       * into the token_representation structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      close_par(const char* from,
	        const char* to);

      /**
       * Callback function called to set plus token representation
       * into the token_representation structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      plus(const char* from,
	   const char* to);

      /**
       * Callback function called to set times token representation
       * into the token_representation structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      times(const char* from,
	    const char* to);

      /**
       * Callback function called to set star token representation
       * into the token_representation structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      star(const char* from,
	   const char* to);

      /**
       * Callback function called to set open_weight token representation
       * into the token_representation structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      open_weight(const char* from,
		  const char* to);

      /**
       * Callback function called to set close_weight token representation
       * into the token_representation structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      close_weight(const char* from,
		   const char* to);

      /**
       * Callback function called to push a new space token representation
       * into the token representation structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      push_space(const char* from,
		 const char* to);

      /**
       * Callback function called to push the token representation of epsilon
       * into the token representation structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      push_one(const char* from,
	       const char* to);

      /**
       * Callback function called to push the token representation of zero
       * into the token representation structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      push_zero(const char* from,
		const char* to);

    }; // ! definition

    parser_options::alphabet_t& al;
    parser_options::token_representation_t& tok_rep;

  }; // ! options_grammar

  alphabet_t letters_;
  token_representation_t tok_rep_;

}; // ! parser_options

// Assign case_true to out if the letter trait is_char_letter
// is true. Otherwise, it assigns case_false to out.
void
if_is_char_letter(boost::spirit::rule<boost::spirit::scanner<const char*> >& out,
		  const boost::spirit::rule<boost::spirit::scanner<const char*> >& case_true,
		  const boost::spirit::rule<boost::spirit::scanner<const char*> >& case_false);

# include "parser_options.hxx"

#endif // ! PARSER_OPTIONS_HH
