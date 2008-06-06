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
# include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_proxy.hh>
# include <vaucanson/algebra/concept/monoid_base.hh>
# include <vaucanson/misc/usual_escaped_characters.hh>

// Declaration to link with libkrat_exp
namespace yy
{
  struct token_queue;
  struct krat_exp_parser
  {
    krat_exp_parser();
    void insert_word(vcsn::algebra::krat_exp_virtual* rexp);
    void insert_weight(vcsn::algebra::semiring_virtual* sem);
    void insert_one(vcsn::algebra::krat_exp_virtual* rexp);
    void insert_zero(vcsn::algebra::krat_exp_virtual* rexp);
    void insert_token(int i, std::string* str);
    int parse(vcsn::algebra::krat_exp_virtual& rexp);

    // Attributs
    token_queue* tok_q_;
   }; // krat_exp_parser
} // yy

namespace vcsn
{
  namespace algebra
  {
    template <class S, class T>
    struct Lexer
    {
      typedef typename Element<S, T>::monoid_elt_t monoid_elt_t;
      typedef typename Element<S, T>::semiring_elt_t semiring_elt_t;
      Lexer(const std::string& from,
	    Element<S, T>& e,
	    yy::krat_exp_parser& parser,
	    bool lex_trace) :
	from_(from),
	e_(e),
	parser_(parser),
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
	  Element<S, T> ww = Element<S, T>(e_.structure(), w.value());
	  krat_exp_proxy<S, T>* rexp = new krat_exp_proxy<S, T>(ww);
	  parser_.insert_word(rexp);
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
	      semiring_proxy<S, T>* sem = new semiring_proxy<S, T>(w);
	      parser_.insert_weight(sem);
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
	if (i == 5)
	{
	  Element<S, T> w = identity_as<T>::of(e_.structure());
	  krat_exp_proxy<S, T>* rexp = new krat_exp_proxy<S, T>(w);
	  parser_.insert_one(rexp);
	}
	else
	  if (i == 6)
	  {
	    Element<S, T> w = zero_as<T>::of(e_.structure());
	    krat_exp_proxy<S, T>* rexp = new krat_exp_proxy<S, T>(w);
	    parser_.insert_zero(rexp);
	  }
	  else
	  {
	    std::string* str = new std::string(token_tab_[i]);
	    parser_.insert_token(i, str);
	  }
      }

      const std::string& from_;
      Element<S, T>& e_;
      yy::krat_exp_parser& parser_;
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
      yy::krat_exp_parser parser;
      Lexer<S, T> lex(from, exp, parser, lex_trace);
      lex.lex();
      krat_exp_proxy<S, T> rexp(exp);
      res = parser.parse(rexp);
      exp = rexp.self;
      return std::make_pair(res, "");
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PARSER_HXX
