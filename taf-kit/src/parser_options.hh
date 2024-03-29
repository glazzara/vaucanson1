// parser_options.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008, 2010 The Vaucanson Group.
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
# include <boost/spirit/include/classic_core.hpp>
# include <boost/spirit/include/classic_lists.hpp>
# include <boost/spirit/include/classic_chset.hpp>

# include <vaucanson/misc/static.hh>

# include "boost_spirit_compatibility.hh"

/**
 * @file parser_options.hh
 * @author Jerome Galtier <jerome.galtier@lrde.epita.fr>
 *
 * This file defines the parser, for the following grammar:
 * (EBNF notations)
 *
 * @verbatim
 * parser-properties ::= [ property { ' ' property } ];
 * property ::= ( "ALPHABET"   '=' alphabet-definition ) |
 *              ( "ONE"        '=' word ) |
 *              ( "ZERO"       '=' word ) |
 *              ( special-name '=' character );
 * alphabet-definition ::= ( "words" ':' [ words ] ) |
 *                         ( [ "letters" ':' ] [ letters ] );
 * letters ::= letter*;
 * words ::= [ word { ',' word } ];
 * special-name ::= "OPAR" | "CPAR" | "PLUS" | "TIMES" |
 *                  "STAR" | "OWEIGHT" | "CWEIGHT" | "SPACE" | "CONCAT";
 * word-pair ::= '(' word ',' word ')';
 * word ::= letter*;
 * character ::= escaped-character | unescaped-character;
 * letter ::= character | word-pair;
 * escaped-character ::= '\' special-character;
 * unescaped-letter ::= ? all characters excluding special-character ?;
 * special-character ::= ' ' | '=' | '(' | ',' | ')' | '\' | ':';
 * @endverbatim
 */

template <typename M, typename S>
class parser_options
{
public:

  parser_options(const std::string&);

  const std::vector<std::string>& get_letters();
  const M& get_mrep();
  const S& get_srep();
  const cmd_flags_t& get_cmd_flags();
  void check_collision();

private:
  bool rec_check_collision(const std::string& str,
			   std::string::const_iterator it_str_curr);
  bool check_collision(const std::string& str);

  // type helpers
  typedef std::vector<std::string> alphabet_t;

  struct options_grammar : public boost::VCSN_SPIRIT_CLASSIC::grammar<options_grammar>
  {
    // CTOR
    options_grammar(alphabet_t& al, M& mrep, S& srep, cmd_flags_t& cf);

    template <typename ScannerT>
    struct definition
    {
      // type helpers
      typedef parser_options<M, S> parser_options_t;
      typedef typename parser_options_t::options_grammar options_grammar_t;
      typedef typename options_grammar_t::template definition<ScannerT> self_t;

      boost::VCSN_SPIRIT_CLASSIC::rule<ScannerT> parser_properties, property,
      alphabet_definition, letters, words, special_name, word_pair,
      word, character, letter, escaped_character, unescaped_character,
      special_character, true_is_char_letter, false_is_char_letter;

      // CTOR
      definition(const options_grammar& g);

      const boost::VCSN_SPIRIT_CLASSIC::rule<ScannerT>&
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
      boost::function<void(const char*, const char*)> concat_cb;

      // reference to parser_options creator
      typename parser_options<M, S>::alphabet_t& al_ref;
      M& mrep_ref;
      S& srep_ref;
      cmd_flags_t& cf_ref;
      bool first_space_;

      /**
       * function called to remove the '\' in front of the
       * escaped characters.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       *
       * @return a string without the '\' used to escape characters
       */

      inline std::string
      escape(const char* from,
	     const char* to);

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
       * into the series_rep_t structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      open_par(const char* from,
	       const char* to);

      /**
       * Callback function called to set close_par token representation
       * into the series_rep_t structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      close_par(const char* from,
	        const char* to);

      /**
       * Callback function called to set plus token representation
       * into the series_rep_t structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      plus(const char* from,
	   const char* to);

      /**
       * Callback function called to set times token representation
       * into the series_rep_t structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      times(const char* from,
	    const char* to);

      /**
       * Callback function called to set star token representation
       * into the series_rep_t structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      star(const char* from,
	   const char* to);

      /**
       * Callback function called to set open_weight token representation
       * into the series_rep_t structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      open_weight(const char* from,
		  const char* to);

      /**
       * Callback function called to set close_weight token representation
       * into the series_rep_t structure.
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

      /**
       * Callback function called to set concat token representation
       * into the monoid_rep_t structure.
       *
       * @param from Begin iterator.
       * @param to   End iterator.
       */
      void
      push_concat(const char* from,
		  const char* to);

    }; // ! definition

    typename parser_options<M, S>::alphabet_t& al;
    M& mrep;
    S& srep;
    cmd_flags_t& cf;

  }; // ! options_grammar

  alphabet_t letters_;
  M mrep_;
  S srep_;
  cmd_flags_t cf_;

}; // ! parser_options

// Assign case_true to out if the letter trait is_char_letter
// is true. Otherwise, it assigns case_false to out.
void
if_is_char_letter(boost::VCSN_SPIRIT_CLASSIC::rule<boost::VCSN_SPIRIT_CLASSIC::scanner<const char*> >& out,
		  const boost::VCSN_SPIRIT_CLASSIC::rule<boost::VCSN_SPIRIT_CLASSIC::scanner<const char*> >& case_true,
		  const boost::VCSN_SPIRIT_CLASSIC::rule<boost::VCSN_SPIRIT_CLASSIC::scanner<const char*> >& case_false);

# include "parser_options.hxx"

#endif // ! PARSER_OPTIONS_HH
