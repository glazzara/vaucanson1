// krat_exp_parser.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey
// and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PARSER_HXX
# define VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PARSER_HXX

# include <vaucanson/algebra/concrete/series/krat_exp_parser.hh>
# include <list>

namespace vcsn {

  namespace algebra {

    namespace krat_exp_lexing {

      enum token_e 
	{
	  lparen,
	  rparen,
	  space, 
	  plus,
	  star,
	  dot,
	  zero,
	  one,
	  a_word, 
	  a_weight, 
	  eof
	};

      enum lexing_status 
	{
	  success,
	  invalid_character,
	  invalid_token
	};

    } // krat_exp_lexing

    using namespace krat_exp_lexing;

    // Schrödinger's token.
    template <class MonoidValue, class WeightValue>
    class KRatExpToken
    {
    public:      
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

	token(const token_e& tok_type, const WeightValue& weight)
	{
	  w = weight;
	  type = tok_type;
	}

	std::string to_string() const
	{
	  switch (type) {
	  case a_word   : return "word";
	  case a_weight : return "weight";
	  case lparen   : return "(";
	  case rparen   : return ")";
	  case one      : return "one";
	  case zero     : return "zero";
	  case dot      : return ".";
	  case star     : return "*";
	  case plus     : return "+";
	  case space    : return " ";
	  case eof      : return "EOF";
	  }
	  return "";
	}

	token_e type;
	MonoidValue m;
	WeightValue w;
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
	    for (typename std::list<token>::const_iterator i = tok_.begin();
		 i != tok_.end();
		 )
	      s += (*i).to_string() + (i++ != tok_.end() ? " ": "");
	    s += ")";
	    return s;
	  }
	return "?";
      }

      bool is_just_a(const token_e tok)
      {
	return ((tok_.size() == 1) && (tok_.front().type == tok));
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
	  if ((*i).type == tok)
	    return true;
	return false;
      }

      MonoidValue as_word()
      {
	for (typename std::list<token>::const_iterator i = tok_.begin();
	     i != tok_.end();
	     ++i)
	  if ((*i).type == a_word)
	    return (*i).m;
	assert(! ("internal error in krat_exp parser."));
	return MonoidValue();
      }

      WeightValue as_weight()
      {
	for (typename std::list<token>::const_iterator i = tok_.begin();
	     i != tok_.end();
	     ++i)
	  if ((*i).type == a_weight)
	    return (*i).w;
	assert(! ("internal error in krat_exp parser."));
	return WeightValue();
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

      KRatExpToken& operator=(const WeightValue& weight_value)
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

    // FIXME: space is used as an operator ! it could imply several pbs.
    // FIXME: for the moment, no layout is permit
    // grammar:
    //
    // exp ::= '(' exp ')'
    //     |   exp '+' exp
    //     |   exp '.' exp
    //     |   exp '*'
    //	   |   weight ' ' exp
    //     |   exp ' ' weight
    //     |   0
    //     |   1
    //     |   word
    // weight lexer is a parameter.
    // word lexer is a parameter.
    // it is assumed that these lexer will not interfere with global lexer.
    template <class S, class T>
    inline
    std::pair<lexing_status, 
	      std::list<KRatExpToken
    <
      typename Element<S, T>::monoid_value_t,
      typename Element<S, T>::weight_value_t
    > 
    > >
    lex(const std::string& in, 
	Element<S, T>& e)
    {
      typedef typename Element<S, T>::monoid_elt_t    monoid_elt_t;
      typedef typename Element<S, T>::monoid_value_t  monoid_value_t;
      typedef typename monoid_elt_t::set_t	      monoid_t;
      typedef typename Element<S, T>::weight_t	      weight_t;
      typedef typename weight_t::set_t		      weights_t;
      typedef typename Element<S, T>::weight_value_t  weight_value_t;
      typedef typename std::string::const_iterator    iterator_t;
      typedef KRatExpToken
	<
	typename Element<S, T>::monoid_value_t,
	typename Element<S, T>::weight_value_t
	> 
	krat_exp_token_t;

      iterator_t i = in.begin();
      std::list<krat_exp_token_t> tokens;
      int len = 0;

      while (i != in.end())
	{
	  len = 0;
	  krat_exp_token_t tok;
	  switch (*i) 
	    {
	    case '(' : tok = lparen; len = 1; break;
	    case ')' : tok = rparen; len = 1; break;
	    case '+' : tok = plus;   len = 1; break;
	    case '*' : tok = star;   len = 1; break;
	    case '.' : tok = dot;    len = 1; break;
	    case ' ' : tok = space;  len = 1; break;
	    case '0' : tok = zero;   len = 1; break;
	    case '1' : tok = one;    len = 1; break;
	    }
	  // try word parser.
	  iterator_t mli = i;
	  monoid_elt_t w(e.set().monoid());
	  if (parse_word(w, in, mli))
	    {
	      if (mli - i > 1)
		tok.reset();
	      tok = w;
	      len = mli - i;
	    }
	  // try weight lexer.
	  iterator_t wli = i;
	  weight_t ww;
	  if (parse_weight(ww, in, wli))
	    {
	      if (wli - i > len)
		tok.reset();
	      if (wli - i >= len)
		{
		  tok = ww;
		  len = wli - i;
		}
	    }
	  // we assume that this is in fact the _same_ token 
	  // which can be interpreted differently in function
	  // of the context.
	  // std::cout << tok.to_string() << std::endl;
	  // std::cout << "len :" << len << std::endl;
	  if (len == 0)
	    return std::make_pair(invalid_token, 
				  std::list<krat_exp_token_t>());
	  tokens.push_back(tok);
	  i += len;
	}
      return std::make_pair(success, tokens);
    }

    template <class S, class T>
    struct Parser
    {
      typedef KRatExpToken
      <
	typename Element<S, T>::monoid_value_t,
	typename Element<S, T>::weight_value_t
      >						      krat_exp_token_t; 
      typedef typename Element<S, T>::monoid_elt_t    monoid_elt_t;
      typedef typename Element<S, T>::monoid_value_t  monoid_value_t;
      typedef typename monoid_elt_t::set_t	      monoid_t;
      typedef typename Element<S, T>::weight_t	      weight_t;
      typedef typename weight_t::set_t		      weights_t;
      typedef typename Element<S, T>::weight_value_t  weight_value_t;
      typedef krat_exp_token_t			      token_t;
      typedef std::list<krat_exp_token_t>	      token_stream_t;
      
      Parser() :
	error_(false),
	error_msg_("")
      {}

      void parse_error(const std::string msg = "parse_error.")
      {
	error_     = true;
	error_msg_ = msg;
      }

      void accept(token_stream_t& toks, token_e tok)
      {
	//	std::cout << "accept a " << tok << std::endl;
	token_t        get_token = toks.front();
	typename token_t::token expected(tok);
	if (!(get_token.is_a(tok) && (toks.size() > 0)))
	  parse_error("waiting for a '"+expected.to_string()
		      +"' get a '"+get_token.to_string()+"'");
	toks.pop_front();
      }

      token_t first(token_stream_t& toks)
      {
	if (toks.size() > 0)
	  return toks.front();
	return token_t(eof);
      }

      token_t second(token_stream_t& toks)
      {
	if (toks.size() >= 2)
	  {
	    typename token_stream_t::const_iterator i = toks.begin();
	    ++i;
	    return *i;
	  }
	return token_t(eof);
      }

      void parse_exp(token_stream_t& toks, Element<S, T>& exp)
      {
	//	std::cout << "get " << first(toks).to_string() << std::endl;
	if (error_) return;
	parse_term (toks, exp);
	while (first(toks).is_a(plus))
	  {
	    Element<S, T> rhs;
	    accept(toks, plus);
	    parse_term(toks, rhs);
	    exp = exp + rhs;
	  }
      }

      void parse_term(token_stream_t& toks, Element<S, T>& exp)
      {
	// std::cout << "get " << first(toks).to_string() << std::endl;
	if (error_) return;
	parse_factor (toks, exp);
	while (first(toks).is_a(dot)
	       || first (toks).is_a (lparen))
	  {
	    Element<S, T> rhs;
	    if (first(toks).is_a(dot))
	      accept(toks, dot);
	    parse_factor(toks, rhs);
	    exp = exp * rhs;
	  }
      }

      void parse_factor(token_stream_t& toks, Element<S, T>& exp)
      {
	//std::cout << "get " << first(toks).to_string() << std::endl;
	if (error_) return;
	parse_factor_without_star(toks, exp);
	while (first(toks).is_a(star))
	  {
	    accept(toks, star);
	    exp = exp.star();
	  }
      }

      void parse_factor_without_star(token_stream_t& toks, Element<S, T>& exp)
      {
	// std::cout << "get " << first(toks).to_string() << std::endl;

	if (error_) return;
	// a 2-lookahead will be sufficient to disambiguate.
	if ((first(toks).is_a(a_weight)) && 
	    (((first(toks).is_schrod()) && (second(toks).is_a(space))) ||
	     (!(first(toks).is_schrod()))))
	  {
	    // token must be a weight.
	    weight_t w = first(toks).as_weight();
	    accept(toks, a_weight);
	    accept(toks, space);
	    // then it could be a word or 1.
	    if (first(toks).is_a(one))
	      {
		monoid_elt_t word;
		accept(toks, one);
		exp = word;
		exp = w * exp;
		return;
	      }
	    else if (first(toks).is_a(a_word))
	      {
		monoid_elt_t word = first(toks).as_word();
		accept(toks, a_word);
		exp = word;
		exp = w * exp;
		return;
	      }
	  }
	else if (first(toks).is_a(one))
	  {
	    monoid_elt_t empty;
	    exp = empty;
	    accept(toks, one);
	    return;
	  }
	else if (first(toks).is_a(zero))
	  {
	    Element<S, T> z;
	    exp = z;
	    accept(toks, zero);
	    return;
	  }
	else if (first(toks).is_a(a_word))
	  {
	    monoid_elt_t word = first(toks).as_word();
	    accept(toks, a_word);
	    exp = word;
	    return;
	  }
	else if (first(toks).is_a(lparen))
	  {
	    accept(toks, lparen);
	    parse_exp(toks, exp);
	    accept(toks, rparen);
	    return;
	  }
	std::cout << "bad exit on " << first(toks).to_string() << std::endl;
      }

      bool error() const
      {
	return error_;
      }

      const std::string& error_msg() const
      {
	return error_msg_;
      }

    private:
      bool		error_;
      std::string	error_msg_;
    };

    template <class S, class T>
    std::pair<bool, std::string>
    parse(const std::string& from, Element<S, T>& exp)
    {
      typedef KRatExpToken
      <
	typename Element<S, T>::monoid_value_t,
	typename Element<S, T>::weight_value_t
      > krat_exp_token_t; 

      std::pair<bool, 
	std::list<krat_exp_token_t>
	> tokens = lex(from, exp);
      Parser<S, T> parser;
      parser.parse_exp(tokens.second, exp);
      return std::make_pair(parser.error(), parser.error_msg());
    }
    

} // algebra

} // vcsn

#endif // VCSN_ALGEBRA_CONCRETE_SERIES_KRAT_EXP_PARSER_HXX
