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
    int parse(vcsn::algebra::krat_exp_virtual& rexp, std::string& error);

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
	    const token_representation<typename S::monoid_t::letter_t> tok_rep,
	    std::string& error) :
	from_(from),
	e_(e),
	parser_(parser),
	lex_trace_(lex_trace),
	close_weight_("}"),
	token_tab_(9),
	error_(error)
      {
	precondition(!tok_rep.open_par.empty());
	precondition(!tok_rep.close_par.empty());
	precondition(!tok_rep.plus.empty());
	precondition(!tok_rep.times.empty());
	precondition(!tok_rep.star.empty());
	precondition(!tok_rep.one.empty());
	precondition(!tok_rep.zero.empty());
	precondition(!tok_rep.open_weight.empty());
	precondition(!tok_rep.close_weight.empty());

	token_tab_[0] = tok_rep.open_par;
	token_tab_[1] = tok_rep.close_par;
	token_tab_[2] = tok_rep.plus;
	token_tab_[3] = tok_rep.times;
	token_tab_[4] = tok_rep.star;
	token_tab_[5] = tok_rep.one;
	token_tab_[6] = tok_rep.zero;
	token_tab_[7] = tok_rep.open_weight;
	close_weight_ = tok_rep.close_weight;
	for (unsigned i = 0; i < tok_rep.spaces.size(); i++)
	{
	  assertion(!tok_rep.spaces[i].empty());
	  token_tab_[8 + i] = tok_rep.spaces[i];
	}

	std::string::const_iterator sit;
	semiring_elt_t ww(e_.structure().semiring());
	sit = close_weight_.begin();
	if (parse_weight(ww, close_weight_, sit))
	  error_ += "Warning : the token '" + close_weight_ +
		    + "' is already defined as a weight.\n";
	sit = token_tab_[7].begin();
	if (parse_weight(ww, token_tab_[7], sit))
	  error_ += "Warning : the token '" + token_tab_[7]
		    + "' is already defined as a weight.\n";
	for (unsigned i = 0; i < token_tab_.size(); i++)
	{
	  sit = token_tab_[i].begin();
	  monoid_elt_t w(e_.structure().monoid());
	  if (parse_word(w, token_tab_[i], sit, std::set<char>()))
	    error_ +=  "Warning : the token '" + token_tab_[i]
		       + "' is already defined as a word.\n";
	}

      }

      bool
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
		if (!insert_word(curr, it))
		  return false;
	      if (i == 7)
	      {
		if (!insert_weight(it))
		  return false;
	      }
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
	  if (!insert_word(curr, it))
	    return false;
	return true;
      }

      private:
      bool
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
	  error_ += "Lexer error : " + s
		    + " some characters are not part of the alphabet\n";
	  return false;
	}
	return true;
      }

      bool
      insert_weight(size_t& it)
      {
	it += token_tab_[7].size();
	size_t bg = it;
	size_t size = from_.size();
	unsigned cpt = 1;
	for (; it < size; it++)
	{
	  if (!from_.compare(it, token_tab_[7].size(), token_tab_[7]))
	    cpt++;
	  else
	    if (!from_.compare(it, close_weight_.size(), close_weight_))
	    {
	      if (cpt == 1)
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
		  error_ += "Lexer error : " + s + " is not a weight\n";
		  return false;
		}
		it += close_weight_.size();
		return true;
	      }
	      else
		cpt--;
	    }
	}
	error_ += "Lexer error : Expected " + close_weight_
		  + "instead of END\n";
	return false;
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
      std::string& error_;
    }; // Lexer

    template <class S, class T>
    std::pair<bool, std::string>
    parse(const std::string& from,
	Element<S, T>& exp,
	const token_representation<typename S::monoid_t::letter_t> tok_rep
	= token_representation<typename S::monoid_t::letter_t>(),
	bool lex_trace = false,
	bool parse_trace = false)
    {
      parse_trace = parse_trace;
      std::string error;
      yy::krat_exp_parser parser;
      Lexer<S, T> lex(from, exp, parser, lex_trace, tok_rep, error);
      if (!lex.lex())
	return std::make_pair(true, error);
      krat_exp_proxy<S, T> rexp(exp);
      if (parser.parse(rexp, error))
	return std::make_pair(true, error);
      exp = rexp.self;
      return std::make_pair(false, error);
    }

  } // algebra

} // vcsn

#endif // ! VCSN_ALGEBRA_IMPLEMENTATION_SERIES_KRAT_EXP_PARSER_HXX
