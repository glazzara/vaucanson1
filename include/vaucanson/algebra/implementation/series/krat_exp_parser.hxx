// krat_exp_parser.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PARSER_HXX
# define VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PARSER_HXX

# include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>

# include <vaucanson/algebra/concept/monoid_base.hh>
# include <vaucanson/tools/usual_escaped_characters.hh>

# include <list>
# include <set>

namespace vcsn {

  namespace algebra {

    /** @addtogroup algebra *//** @{ */
    /** @addtogroup series *//** @{ */

    /// Misc. declarations used for rational expression lexing.
    namespace krat_exp_lexing {

      /**
       * Token types enumeration.
       *
       * Those are the different token types the lexer could encounter.
       *
       * @see @c KRatExpToken, @c KRatExpToken::token
       * @anchor token_e
       */
      enum token_e
	{
	  lparen,
	  rparen,
	  space,
	  plus,
	  e_star,
	  dot,
	  zero,
	  one,
	  a_word,
	  a_weight,
	  eof
	};

    } // krat_exp_lexing

    using namespace krat_exp_lexing;

    /**
     * Schrödinger's token for rational expression lexing.
     *
     * Tokens are ambiguous. For example, '1' could be interpreted
     * both as a weight and as the empty word. So we assume that each
     * possible token is in fact part of the *same* token. This
     * is the Schrödinger's token this class represents.
     *
     * @see @c KRatExpToken::token, @ref token_e "token_e"
     */
    template <class MonoidValue, class SemiringEltValue>
    class KRatExpToken
    {
    public:
      /**
       * Simple token.
       *
       * This classes represents a simple unambiguous token. Its type
       * is one of token_e. When a_word or a_weight, an extra information
       * is carried, which is (of course) the corresponding weight or
       * word. A Schrödinger's token contains a list of such tokens.
       *
       * @see @c KRatExpToken, @ref token_e "token_e"
       */
      struct token
      {
	token(const token_e& tok_type) :
	  type(tok_type)
	{}

	token(const token_e& tok_type, const MonoidValue& word)
	{
	  m = word;
	  type = tok_type;
	}

	token(const token_e& tok_type, const SemiringEltValue& weight)
	{
	  w = weight;
	  type = tok_type;
	}

	std::string to_string() const
	{
	  switch (type)
	    {
	    case a_word   : return "word";
	    case a_weight : return "weight";
	    case lparen   : return "(";
	    case rparen   : return ")";
	    case one      : return "one";
	    case zero     : return "zero";
	    case dot      : return ".";
	    case e_star   : return "*";
	    case plus     : return "+";
	    case space    : return " ";
	    case eof      : return "EOF";
	    }
	  return "";
	}

	token_e type;
	MonoidValue m;
	SemiringEltValue w;
      };

      KRatExpToken(const token_e& tok)
      {
	tok_.push_back(tok);
      }

      KRatExpToken()
      {
      }

      std::string to_string() const
      {
	if (tok_.size() == 0)
	  return "no token";
	else if (tok_.size() == 1)
	  return tok_.front().to_string();
	else
	  {
	    std::string s("schrod(");
	    typename std::list<token>::const_iterator i = tok_.begin();
	    while (i != tok_.end())
	      s += i->to_string() + (++i != tok_.end() ? " ": "");
	    s += ")";
	    return s;
	  }
      }

      bool is_just_a(const token_e tok)
      {
	return ((tok_.size() == 1) && (tok_.front().type == tok));
      }

      bool is_defined()
      {
	return (tok_.size() > 0);
      }

      bool is_schrod()
      {
	return (tok_.size() > 1);
      }

      bool is_a(const token_e tok)
      {
	for (typename std::list<token>::const_iterator i = tok_.begin();
	     i != tok_.end();
	     ++i)
	  if (i->type == tok)
	    return true;
	return false;
      }

      MonoidValue as_word()
      {
	for (typename std::list<token>::const_iterator i = tok_.begin();
	     i != tok_.end();
	     ++i)
	  if (i->type == a_word)
	    return i->m;
	assertion(! "internal error in krat_exp parser.");
	return MonoidValue();
      }

      SemiringEltValue as_weight()
      {
	for (typename std::list<token>::const_iterator i = tok_.begin();
	     i != tok_.end();
	     ++i)
	  if (i->type == a_weight)
	    return i->w;
	assertion(! "internal error in krat_exp parser.");
	return SemiringEltValue();
      }

      KRatExpToken& operator=(const token_e tok)
      {
	tok_.push_back(token(tok));
	return *this;
      }

      KRatExpToken& operator=(const MonoidValue& word_value)
      {
	tok_.push_back(token(a_word, word_value));
	return *this;
      }

      KRatExpToken& operator=(const SemiringEltValue& weight_value)
      {
	tok_.push_back(token(a_weight, weight_value));
	return *this;
      }

      void reset()
      {
	tok_.clear();
      }

    private:
      std::list<token> tok_;
    };

    /**
     * Lexer class for the rational expression parser.
     *
     * @see @c Parser
     */
    template <class S, class T>
    struct Lexer
    {
      typedef KRatExpToken
      <
	typename Element<S, T>::monoid_value_t,
	typename Element<S, T>::semiring_elt_value_t
      >						      krat_exp_token_t;
      typedef std::list<krat_exp_token_t>	      token_stream_t;

      Lexer(bool trace = false) :
	tokens_ (),
	trace_ (trace),
	error_msg_ ("No error."),
	error_ (false)
      {
      }

      /// Put the lexer into an error state.
      void
      lex_error(const std::string& msg = "Lex error.")
      {
	error_ = true;
	error_msg_ = msg;
      }

      /**
       * Perform lexing.
       *
       * @param in The rational expression to lex, as a string.
       * @param e The element which will be used later for parsing.
       *          It used to guess words and semiring types.
       */
      void
      lex(const std::string& in, const Element<S, T>& e)
      {
	typedef typename Element<S, T>::monoid_elt_t	monoid_elt_t;
	typedef typename Element<S, T>::monoid_value_t	monoid_value_t;
	typedef typename Element<S, T>::semiring_elt_t	semiring_elt_t;
	typedef std::string::const_iterator		iterator_t;

	iterator_t i = in.begin();
	std::set<char> escaped = tools::usual_escaped_characters();
	int len = 0;

	while (!error_ & (i != in.end()))
	  {
	    len = 0;
	    krat_exp_token_t tok;
	    switch (*i)
	      {
		// operator case.
	      case '(' : tok = lparen; len = 1; break;
	      case ')' : tok = rparen; len = 1; break;
	      case '+' : tok = plus;   len = 1; break;
	      case '*' : tok = e_star; len = 1; break;
	      case '.' : tok = dot;    len = 1; break;
	      case ' ' : tok = space;  len = 1; break;
	      case '0' : tok = zero;   len = 1; break;
	      case '1' : tok = one;    len = 1; break;
	      }
	    // try word parser.
	    iterator_t mli = i;
	    monoid_elt_t w(e.set().monoid());
	    if (parse_word(w, in, mli, escaped))
	      {
		if (mli - i > 1)
		  tok.reset();
		tok = w.value();
		len = mli - i;
	      }
	    // try weight lexer.
	    iterator_t wli = i;
	    semiring_elt_t ww;
	    if (parse_weight(ww, in, wli))
	      {
		if (wli - i > len)
		  tok.reset();
		if (wli - i >= len)
		  {
		    tok = ww.value();
		    len = wli - i;
		  }
	      }
	    if (len == 0)
	      lex_error(std::string("Invalid token '") + *i + "'.");
	    else
	      tokens_.push_back(tok);
	    i += len;
	  }
      }

      /// Return true when an error occured.
      bool
      error() const
      {
	return error_;
      }

      /// Return the error message.
      const std::string&
      error_msg() const
      {
	return error_msg_;
      }

      /// Return the first token.
      krat_exp_token_t first() const
      {
	return (tokens_.size() > 0) ? tokens_.front() :
	  krat_exp_token_t (eof);
      }

      /// Return the second token.
      krat_exp_token_t second() const
      {
	return (tokens_.size() >= 2) ?
	  *++tokens_.begin() : krat_exp_token_t (eof);
      }

      /**
       * Shift tokens.
       *
       * Remove the first token from the token stream. So second
       * becames first, third becames second, and so on...
       */
      void eat()
      {
	if (tokens_.size() > 0)
	  {
	    if (trace_)
	      std::cerr << "LEXER: eating '" << tokens_.front().to_string()
			<< "'." << std::endl;
	    tokens_.pop_front();
	  }
      }

      void set_trace(bool trace)
      {
	trace_ = trace;
      }

    protected:
      token_stream_t tokens_;
      bool trace_;
      std::string error_msg_;
      bool error_;
    };

    /**
     * Parser class used in the ::parse() function.
     *
     * This class handles rational expression parsing, once a Lexer has
     * been created.
     *
     * Ideally, we would like to parse:
     *
     @verbatim
     exp ::= '(' exp ')'
         |   exp '+' exp
         |   exp '.' exp
         |   exp exp
         |   exp '*'
         |   weight ' ' exp
         |   exp ' ' weight
         |   0
         |   1
         |   word
     @endverbatim
     *
     * But this grammar has to be changed to allow a classical LL(2)
     * parsing:
     *
     @verbatim
     exp		::= term ('+' term)*
     term		::= right_weighted ('.'? right_weighted)*
     right_weighted	::= left_weighted (' ' weight)*
     left_weighted	::= weight ' ' left_weighted
                        |   stared
     stared		::= factor '*'*
     factor		::= '(' exp ')' | word | 0 | 1
     @endverbatim
     */
    template <class S, class T>
    struct Parser
    {
      typedef KRatExpToken
      <
	typename Element<S, T>::monoid_value_t,
	typename Element<S, T>::semiring_elt_value_t
      >						      krat_exp_token_t;
      typedef typename Element<S, T>::monoid_elt_t    monoid_elt_t;
      typedef typename Element<S, T>::monoid_value_t  monoid_value_t;
      typedef typename monoid_elt_t::set_t	      monoid_t;
      typedef typename Element<S, T>::semiring_elt_t	      semiring_elt_t;
      typedef typename semiring_elt_t::set_t		      semiring_t;
      typedef typename Element<S, T>::semiring_elt_value_t  semiring_elt_value_t;
      typedef std::list<krat_exp_token_t>	      token_stream_t;

      Parser(Lexer<S, T>& lexer, bool trace = false) :
	lexer_		(lexer),
	trace_		(trace),
	error_		(lexer.error()),
	error_msg_	(lexer.error_msg())
      {
      }

      /// Do the parsing.
      void parse(Element<S, T>& exp)
      {
	if (!error_)
	  {
	    trace("*** START ***");
	    try
	      {
		parse_exp(exp);
		accept(eof);
	      }
	    catch (const std::string& s)
	      {
		error_ = true;
		error_msg_ = s;
	      }
	    trace("*** END ***");
	  }
      }

      /// Return true when an error occured.
      bool error() const
      {
	return error_;
      }

      /// Return the error message.
      const std::string& error_msg() const
      {
	return error_msg_;
      }

      void set_trace(bool trace)
      {
	trace_ = trace;
      }

    protected:

      //@{
      /// Trace parsing.
      void
      trace(const std::string& msg)
      {
	if (trace_)
	  std::cerr << "PARSER: " << msg << '.' << std::endl;
      }

      template <class Misc>
      void
      trace(const std::string& msg, const Misc& v)
      {
	if (trace_)
	  std::cerr << "PARSER: " << msg << " (" << v << ")." << std::endl;
      }
      //@}

      /// Generate a parse error.
      void parse_error(const std::string& msg = "parse_error.")
	throw (const std::string&)
      {
	trace("Stop on error.", msg);
	throw msg;
      }

      /**
       * Accept token, or generate an error.
       *
       * This function asks the lexer whether the first input token
       * matches the argument or not. When matching is successfull,
       * the first input token is eaten, an error is risen else.
       *
       * @param tok The token to match.
       */
      void accept(token_e tok)
      {
	krat_exp_token_t			get_token = lexer_.first();
	typename krat_exp_token_t::token	expected (tok);

	trace("accept", expected.to_string());
	if (!get_token.is_a(tok))
	  parse_error("waiting for a '" + expected.to_string() +
		      "' get a '" + get_token.to_string() + "'.");
	else
	  lexer_.eat();
      }

      /// exp ::= term ('+' term)*
      void parse_exp(Element<S, T>& exp)
      {
	trace("parse_exp: Start");
	parse_term (exp);
	while (lexer_.first().is_a(plus))
	  {
	    accept(plus);
	    Element<S, T> rhs (exp.set());
	    parse_term(rhs);
	    exp = exp + rhs;
	  }
	trace("parse_exp: End",  exp);
      }

      /// term ::= right_weighted ('.'? right_weighted)*
      void parse_term(Element<S, T>& exp)
      {
	trace("parse_term: Start");
	parse_right_weighted (exp);
	while (lexer_.first().is_a(dot)		||
	       lexer_.first().is_a(a_weight)	||
	       lexer_.first().is_a(lparen)	||
	       lexer_.first().is_a(one)		||
	       lexer_.first().is_a(zero)	||
	       lexer_.first().is_a(a_word))
	  {
	    if (lexer_.first().is_a(dot))
	      accept(dot);
	    Element<S, T> rhs (exp.set());
	    parse_right_weighted(rhs);
	    exp = exp * rhs;
	  }
	trace("parse_term: End",  exp);
      }

      /// right_weighted ::= left_weighted (' ' weight)*
      void parse_right_weighted(Element<S, T>& exp)
      {
	trace("parse_right_weighted: Start");
	parse_left_weighted(exp);
	while (lexer_.first().is_a(space))
	  {
	    accept(space);
	    krat_exp_token_t tok = lexer_.first();
	    accept(a_weight);
	    exp = exp * semiring_elt_t (exp.set().semiring(), tok.as_weight());
	  }
	trace("parse_right_weighted: End", exp);
      }

      /// left_weighted ::= weight ' ' left_weighted | stared
      void parse_left_weighted(Element<S, T>& exp)
      {
	trace("parse_left_weighted: Start");
	// a 2-lookahead will be sufficient to disambiguate.
	if (lexer_.first().is_a(a_weight) &&
	    (!lexer_.first().is_schrod() || lexer_.second().is_a(space)))
	  {
	    // token must be a weight, but may be a monoid '1' or '0'.
	    // i.e. in "1 2" or "0 2".
	    // token may even be a word!
	    // i.e. in '2 3' when 2 is in the alphabet
	    semiring_elt_t w (exp.set().semiring(), lexer_.first().as_weight());
	    bool just_a_weight = true;
	    Element<S, T> m (exp.set());
	    if (lexer_.first().is_a(zero))
	      {
		just_a_weight = false;
		m = zero_as<T>::of(exp.set());
	      }
	    else if (lexer_.first().is_a(one))
	      {
		just_a_weight = false;
		m = identity_as<T>::of(exp.set());
	      }
	    else if (lexer_.first().is_a(a_word))
	      {
		just_a_weight = false;
		m = Element<S, T> (exp.set(), lexer_.first().as_word());
	      }
	    accept(a_weight);
	    accept(space);
	    if (just_a_weight ||
		!lexer_.first().is_a(a_weight) ||
		lexer_.second().is_a(space))
	      {
		// Then it could be any weighted.
		Element<S, T> rhs (exp.set());
		parse_left_weighted(rhs);
		exp = w * rhs;
	      }
	    else
	      {
		// Arg ! First was not a weight, but a monoid value !
		w = lexer_.first().as_weight();
		accept(a_weight);
		exp = m * w;
	      }
	  }
	else
	  /* !lexer_.first().is_a(a_weight)  ||
	     (lexer_.first.is_schrod() && !lexer_.second().is_a(space)) */
	  parse_stared(exp);
	trace("parse_left_weighted: End",  exp);
      }

      /// stared ::= factor '*'*
      void parse_stared(Element<S, T>& exp)
      {
	trace("parse_stared: Start");
	parse_factor(exp);
	while (lexer_.first().is_a(e_star))
	  {
	    accept(e_star);
	    exp.star();
	  }
	trace("parse_stared: End",  exp);
      }

      /// factor ::= 1 | 0 | word | '(' exp ')'
      void parse_factor(Element<S, T>& exp)
      {
	trace("parse_factor: Start");
	if (lexer_.first().is_a(one))
	  {
	    accept(one);
	    exp = identity_as<T>::of(exp.set());
	  }
	else if (lexer_.first().is_a(zero))
	  {
	    accept(zero);
	    exp = zero_as<T>::of(exp.set());
	  }
	else if (lexer_.first().is_a(a_word))
	  {
	    exp = monoid_elt_t (exp.set().monoid(), lexer_.first().as_word());
	    accept(a_word);
	  }
	else if (lexer_.first().is_a(lparen))
	  {
	    accept(lparen);
	    parse_exp(exp);
	    accept(rparen);
	  }
	else
	  parse_error("waiting for a factor get a " +
		      lexer_.first().to_string());
	trace("parse_factor: End",  exp);
      }

      Lexer<S, T>&	lexer_;
      bool		trace_;
      bool		error_;
      std::string	error_msg_;
    };

    template <class S, class T>
    std::pair<bool, std::string>
    parse(const std::string& from,
	  Element<S, T>& exp,
	  bool lex_trace,
	  bool parse_trace)
    {
      Lexer<S, T> lexer(lex_trace);
      lexer.lex(from, exp);
      Parser<S, T> parser(lexer, parse_trace);
      parser.parse(exp);
      return std::make_pair(parser.error(), parser.error_msg());
    }

    /** @} */
    /** @} */

  } // algebra

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PARSER_HXX
