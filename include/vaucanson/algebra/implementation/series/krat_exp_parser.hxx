// krat_exp_parser.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008, 2009, 2011 The Vaucanson Group.
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
# include <vaucanson/algebra/concept/monoid_base.hh>
# include <vaucanson/algebra/implementation/series/krat_exp_parser_private.hh>

namespace vcsn
{
  namespace algebra
  {

    template <class S, class T>
    struct Lexer
    {
      // Type helpers.
      typedef typename Element<S, T>::monoid_elt_t monoid_elt_t;
      typedef typename Element<S, T>::semiring_elt_t semiring_elt_t;
      typedef typename Element<S, T>::set_t::shared_series_rep_t
	shared_series_rep_t;

      Lexer(const std::string& from,
	    Element<S, T>& e,
	    vcsnyy::krat_exp_parser& parser,
	    bool lex_trace,
	    std::string& error) :
	from_(from),
	e_(e),
	parser_(parser),
	lex_trace_(lex_trace),
	close_weight_("}"),
	// Reserve seven elements for the "visible" tokens.
	token_tab_(7),
	error_(error)
      {
	// Get the series representation.
	const shared_series_rep_t& rep = e.structure().representation();

	token_tab_[0] = rep->open_par;
	token_tab_[1] = rep->close_par;
	token_tab_[2] = rep->plus;
	token_tab_[3] = rep->times;
	token_tab_[4] = rep->star;
	token_tab_[5] = rep->zero;
	token_tab_[6] = rep->open_weight;
	close_weight_ = rep->close_weight;

	// Concat the spaces representation vector.
	token_tab_.insert(token_tab_.end(), rep->spaces.begin(), rep->spaces.end());

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
	  monoid_elt_t w(e_.structure().monoid());
	  if (parse_word(w, token_tab_[i]).first)
	    error_ +=  "Warning : the token '" + token_tab_[i]
		       + "' is already defined as a word.\n";
	}

      }

      bool
      lex()
      {
	size_t size = from_.size();
	size_t it = 0;
	while (it < size)
	{
	  // Try to recognize a word.
	  monoid_elt_t w(e_.structure().monoid());
	  std::pair<bool, int> res = parse_word(w, from_.substr(it));
	  if (res.second > 0)
	    {
	      insert_word(w);
	      // If the entire input was a word there is nothing else to lex.
	      if (res.first)
		{
		  assertion(it + res.second == size);
		  break;
		}
	      it += res.second;
	    }

	  // Try to recognize a regex token.
	  size_t i;
	  for (i = 0; i < token_tab_.size(); i++)
	  {
	    if (!from_.compare(it, token_tab_[i].size(), token_tab_[i]))
	    {
	      if (i == 6)
	      {
		if (!insert_weight(it))
		  return false;
	      }
	      else
	      {
		if (i < 6)
		  insert_token(i);
		it += token_tab_[i].size();
	      }
	      break;
	    }
	  }
	  if (i >= token_tab_.size())
	    {
	      error_ += "Lexer error, unrecognized characters: "
		+ from_.substr(it) + "\n";
	      return false;
	    }
	}
	return true;
      }

      private:
      void
      insert_word(monoid_elt_t& w)
      {
	Element<S, T> ww = (w.value().empty() ?
			    identity_as<T>::of(e_.structure()) :
			    Element<S, T>(e_.structure(), w.value()));

	krat_exp_proxy<S, T>* rexp = new krat_exp_proxy<S, T>(ww);
	parser_.insert_word(rexp);
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
      vcsnyy::krat_exp_parser& parser_;
      bool lex_trace_;
      std::string close_weight_;
      std::vector<std::string> token_tab_;
      std::string& error_;
    }; // Lexer

    template <class S, class T>
    std::pair<bool, std::string>
    parse(const std::string& from, Element<S, T>& exp,
	  bool lex_trace, bool parse_trace)
    {
      parse_trace = parse_trace;
      std::string error;
      vcsnyy::krat_exp_parser parser;
      Lexer<S, T> lex(from, exp, parser, lex_trace, error);
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
