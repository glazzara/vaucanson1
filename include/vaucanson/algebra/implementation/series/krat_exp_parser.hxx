// krat_exp_parser.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PARSER_HXX
# define VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PARSER_HXX
# include <string>
# include <vector>
# include <map>
# include <queue>
# include <set>
# include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
# include <krat_exp_bison.tab.hh>
# include <vaucanson/algebra/concept/monoid_base.hh>
# include <vaucanson/misc/usual_escaped_characters.hh>

namespace vcsn
{
  namespace algebra
  {
    using namespace yy; // bison doesn't allow me to put my parser in vcsn::algebra

    typedef std::queue<std::pair<krat_exp_parser::token_type, krat_exp_parser::semantic_type> > tok_queue_t;

    template <class S, class T>
    struct Lexer
    {
      typedef typename Element<S, T>::monoid_elt_t monoid_elt_t;
      typedef typename Element<S, T>::semiring_elt_t semiring_elt_t;
      Lexer(const std::string& from,
	    Element<S, T>& e,
	    tok_queue_t& tok_q,
	    bool lex_trace) :
	from_(from),
	e_(e),
	tok_q_(tok_q),
	lex_trace_(lex_trace),
	end_weight_("}"),
	token_tab_(9)
      {
	// default token representation
	token_tab_[0] = "(";
	token_tab_[1] = ")";
	token_tab_[2] = "+";
	token_tab_[3] = ".";
	token_tab_[4] = "*";
	token_tab_[5] = "1";
	token_tab_[6] = "0";
	token_tab_[7] = "{";
	token_tab_[8] = " ";
      }

      void
      lex()
      {
	size_t curr = 0;
	size_t size = from_.size();
	size_t it = curr;
	while (it < size)
	{
	  for (size_t i = 0; i < token_tab_.size(); i++)
	  {
	    if (!from_.compare(it, token_tab_[i].size(), token_tab_[i]))
	    {
	      if (curr != it)
		insert_word(curr, it);
	      if (i == 7)
		insert_weight(it);
	      else
	      {
		if (i < 7)
		  insert_token(i);
		it += token_tab_[i].size();
	      }
	      curr = it--;
	      break;
	    }
	  }
	  it++;
	}
	if (curr != it)
	  insert_word(curr, it);
      }

      private:
      void
      insert_word(size_t curr, size_t it)
      {
	std::set<char> escaped = misc::usual_escaped_characters();
	monoid_elt_t w(e_.structure().monoid());
	std::string s = from_.substr(curr, it - curr);
	std::string::const_iterator sit = s.begin();
	if (parse_word(w, s, sit, escaped))
	{
	  krat_exp_parser::semantic_type rexp;
	  Element<S, T> ww = Element<S, T>(e_.structure(), w.value());
	  rexp.rexp = new krat_exp_proxy<S, T>(ww);
	  tok_q_.push(std::make_pair(krat_exp_parser::token::WORD, rexp));
	}
	else
	{
	  std::cerr << "Lexer error : " << s
		    << " some characters are not part of the alphabet" << std::endl;
	}
      }

      void
      insert_weight(size_t& it)
      {
	std::set<char> escaped = misc::usual_escaped_characters();
	size_t bg = ++it;
	size_t size = from_.size();
	for (; it < size; it++)
	  if (!from_.compare(it, end_weight_.size(), end_weight_))
	  {
	    semiring_elt_t w(e_.structure().semiring());
	    std::string s = from_.substr(bg, it - bg);
	    std::string::const_iterator sit = s.begin();
	    if (parse_weight(w, s, sit))
	    {
	      krat_exp_parser::semantic_type rexp;
	      rexp.sem = new semiring_proxy<S, T>(w);
	      tok_q_.push(std::make_pair(krat_exp_parser::token::WEIGHT, rexp));
	    }
	    else
	    {
	      std::cerr << "Lexer error : " << s << " is not a weight" << std::endl;
	    }
	    it++;
	    return;
	  }
      }

      void
      insert_token(int i)
      {
	krat_exp_parser::token_type tmp;
	if (i < 4)
	  if (i < 2)
	    if (i == 0)
	      tmp = krat_exp_parser::token::OPAR;
	    else
	      tmp = krat_exp_parser::token::CPAR;
	  else
	    if (i == 2)
	      tmp = krat_exp_parser::token::PLUS;
	    else
	      tmp = krat_exp_parser::token::TIMES;
	else
	  if (i < 6)
	    if (i == 4)
	      tmp = krat_exp_parser::token::STAR;
	    else
	      tmp = krat_exp_parser::token::ONE;
	  else
	    tmp = krat_exp_parser::token::ZERO;
	krat_exp_parser::semantic_type rexp;
	if (i == 5)
	{
	  Element<S, T> w = identity_as<T>::of(e_.structure());
	  rexp.rexp = new krat_exp_proxy<S, T>(w);
	}
	else
	  if (i == 6)
	  {
	    Element<S, T> w = zero_as<T>::of(e_.structure());
	    rexp.rexp = new krat_exp_proxy<S, T>(w);
	  }
	  else
	    rexp.str = new std::string(token_tab_[i]);
	tok_q_.push(std::make_pair(tmp, rexp));
      }

      const std::string& from_;
      Element<S, T>& e_;
      tok_queue_t& tok_q_;
      bool lex_trace_;
      std::string end_weight_;
      std::vector<std::string> token_tab_;
    }; // Lexer

    template <class S, class T>
    std::pair<bool, std::string>
    parse(const std::string& from,
	Element<S, T>& exp,
	bool lex_trace = false,
	bool parse_trace = false)
    {
      parse_trace = parse_trace;
      int res;
      tok_queue_t tok_q;
      Lexer<S, T> lex(from, exp, tok_q, lex_trace);
      lex.lex();
      krat_exp_proxy<S, T> rexp(exp);
      yy::krat_exp_parser parser(tok_q, rexp);
      res = parser.parse();
      exp = rexp.self;
      return std::make_pair(res, "");
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PARSER_HXX
