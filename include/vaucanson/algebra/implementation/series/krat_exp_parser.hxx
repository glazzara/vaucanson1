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
# include <map>
# include <queue>
# include <set>
# include <vaucanson/algebra/implementation/series/krat_exp_parser.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_proxy.hh>
# include <vaucanson/algebra/concept/monoid_base.hh>

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
	    bool lex_trace,
	    const token_representation_t tok_rep) :
	from_(from),
	e_(e),
	parser_(parser),
	lex_trace_(lex_trace),
	close_weight_("}"),
	token_tab_(9)
      {
	// default token representation
	if (tok_rep.open_par.empty())
	  token_tab_[0] = "(";
	else
	  token_tab_[0] = tok_rep.open_par;
	if (tok_rep.close_par.empty())
	  token_tab_[1] = ")";
	else
	  token_tab_[1] = tok_rep.close_par;
	if (tok_rep.plus.empty())
	  token_tab_[2] = "+";
	else
	  token_tab_[2] = tok_rep.plus;
	if (tok_rep.times.empty())
	  token_tab_[3] = ".";
	else
	  token_tab_[3] = tok_rep.times;
	if (tok_rep.star.empty())
	  token_tab_[4] = "*";
	else
	  token_tab_[4] = tok_rep.star;
	if (tok_rep.one.empty())
	  token_tab_[5] = "1";
	else
	  token_tab_[5] = tok_rep.one;
	if (tok_rep.zero.empty())
	  token_tab_[6] = "0";
	else
	  token_tab_[6] = tok_rep.zero;
	if (tok_rep.open_weight.empty())
	  token_tab_[7] = "{";
	else
	  token_tab_[7] = tok_rep.open_weight;
	if (tok_rep.close_weight.empty())
	  close_weight_ = "}";
	else
	  close_weight_ = tok_rep.close_weight;
	if (tok_rep.spaces.empty())
	  token_tab_[8] = " ";
	else
	  for (unsigned i = 0; i < tok_rep.spaces.size(); i++)
	  {
	    token_tab_[8 + i] = tok_rep.spaces[i];
	  }

# ifndef VCSN_NDEBUG
	std::string::const_iterator sit;
	semiring_elt_t ww(e_.structure().semiring());
	sit = close_weight_.begin();
	if (parse_weight(ww, close_weight_, sit))
	  std::cerr << "Warning : the token '" << close_weight_
		    << "' is already defined as a weight." << std::endl;
	sit = token_tab_[7].begin();
	if (parse_weight(ww, token_tab_[7], sit))
	  std::cerr << "Warning : the token '" << token_tab_[7]
		    << "' is already defined as a weight." << std::endl;
	for (unsigned i = 0; i < token_tab_.size(); i++)
	{
	  sit = token_tab_[i].begin();
	  monoid_elt_t w(e_.structure().monoid());
	  if (parse_word(w, token_tab_[i], sit, std::set<char>()))
	    std::cerr << "Warning : the token '" << token_tab_[i]
		      << "' is already defined as a word." << std::endl;
	}
# endif // !VCSN_NDEBUG

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
	monoid_elt_t w(e_.structure().monoid());
	std::string s = from_.substr(curr, it - curr);
	std::string::const_iterator sit = s.begin();
	if (parse_word(w, s, sit, std::set<char>()))
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
	size_t bg = ++it;
	size_t size = from_.size();
	for (; it < size; it++)
	  if (!from_.compare(it, close_weight_.size(), close_weight_))
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
      std::string close_weight_;
      std::vector<std::string> token_tab_;
    }; // Lexer

    template <class S, class T>
    std::pair<bool, std::string>
    parse(const std::string& from,
	Element<S, T>& exp,
	const token_representation_t tok_rep = token_representation_t(),
	bool lex_trace = false,
	bool parse_trace = false)
    {
      parse_trace = parse_trace;
      int res;
      yy::krat_exp_parser parser;
      Lexer<S, T> lex(from, exp, parser, lex_trace, tok_rep);
      lex.lex();
      krat_exp_proxy<S, T> rexp(exp);
      res = parser.parse(rexp);
      exp = rexp.self;
      return std::make_pair(res, "");
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PARSER_HXX
