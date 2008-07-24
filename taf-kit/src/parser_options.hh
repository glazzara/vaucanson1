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
# include <boost/ref.hpp>
# include <boost/spirit/core.hpp>
# include <boost/spirit/utility/lists.hpp>
# include <boost/spirit/utility/chset.hpp>

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

private:

  // type helpers
  typedef std::vector<std::string> alphabet_t;

  typedef struct options_grammar : public boost::spirit::grammar<options_grammar>
  {
    // CTOR
    options_grammar(alphabet_t& al);

    template <typename ScannerT>
    struct definition
    {
      // type helpers
      typedef typename parser_options::options_grammar::definition<ScannerT> self_t;

      boost::spirit::rule<ScannerT> parser_properties, propertie,
      alphabet_definition, letters, words, special_name, word_pair,
      word, character, letter, escaped_character, unescaped_character,
      special_character;

      // CTOR
      definition(const options_grammar& g);

      const boost::spirit::rule<ScannerT>&
      start() const;

      // callbacks
      boost::function<void(const char*, const char*)> push_letter_cb;

      // reference to parser_options creator
      parser_options::alphabet_t& ref;

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
    };

    parser_options::alphabet_t& al;
  };

  alphabet_t letters_;

};

# include "parser_options.hxx"

#endif // ! PARSER_OPTIONS_HH
