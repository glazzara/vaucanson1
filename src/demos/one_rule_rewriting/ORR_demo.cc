// ORR_demo.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/boolean_transducer.hh>

#include <vaucanson/tools/dot_display.hh>
#include <vaucanson/algorithms/krat_exp_expand.hh>
#include <vaucanson/algorithms/evaluation.hh>
#include <vaucanson/algorithms/realtime_composition.hh>
#include <vaucanson/algorithms/transpose.hh>

using namespace vcsn;
using namespace vcsn::boolean_transducer;

void
eval_an_expression(const automaton_t& t)
{
  const alphabet_t&	alphabet = t.structure().series().monoid().alphabet();
  std::string		user_string;

  do
  {
    std::cout << "Enter your expression over " << alphabet
	      <<" (\"next\", otherwise): ";
    std::cin >> user_string;
    if (user_string != "next")
    {
      using namespace vcsn::boolean_automaton;
      using namespace vcsn::rat;

      rat_exp_t exp = make_rat_exp(alphabet, user_string);
      std::cout << setpm (MODE_STAR) << expand(evaluation(t, exp))
		<< std::endl;
    }
  }
  while (user_string != "next");
}


std::string
prefsuf(const std::string& u, const std::string& v)
{
  int	vs = v.size();
  int	s = std::min(u.size(), v.size());

  for (int n = s; n > 0; --n)
  {
    std::string tmp = u.substr(0, n);
    if (tmp == v.substr(vs - n, n))
      return tmp;
  }

  return "";
}

std::string
alpha_convert(const std::map<letter_t, letter_t>& conv_map,
	      const std::string& str)
{
  std::string r;
  int n = str.size();
  r.reserve(n);

  for (int i = 0; i < n; ++i)
    r += conv_map.find(str[i])->second;

  return r;
}

std::map<letter_t, letter_t>
alpha_map(const alphabet_t& A,
	  const alphabet_t& B)
{
  typedef alphabet_t::const_iterator alphabet_iterator;

  std::map<letter_t, letter_t>	m;

  alphabet_iterator j = B.begin();
  for_all_letters(i, A)
    m[*i] = *j++;

  return m;
}

automaton_t
replace_left(const std::string& from,	const std::string& to,
	     const alphabet_t& A,	const alphabet_t& B)
{
  automaton_t	a = make_automaton(A, B);

  int		n = from.size();

  // Create a map to make the 2 alphabets correspond.
  std::map<letter_t, letter_t> a2b = alpha_map(A, B);

  // Create a vector to handle all the states.
  std::vector<hstate_t>	s (n);

  // Create states and set them all final.
  for (int i = 0; i < n; ++i)
  {
    s[i] = a.add_state();
    a.set_o_final(s[i], alpha_convert(a2b, from.substr(0, i)));
  }

  // Set the first state initial.
  a.set_initial(s[0]);

  // Create all the transitions of the type (ui | 1).
  for (int i = 0; i < n - 1; ++i)
  {
    const letter_t l[] = {from[i], 0 };
    a.add_io_transition(s[i], s[i + 1], l, "");
  }

  // Create the backward transitions.
  for (int i = 0; i < n; ++i)
    for_all_letters(j, A)
      if (*j != from[i])
      {
	const letter_t	l[] = {*j, 0};

	const std::string	in = from.substr(0, i) + *j;
	const std::string	factor = prefsuf(from, in);
	const int		len = factor.size();

	a.add_io_transition(s[i], s[len], l,
			    alpha_convert(a2b, in.substr(0, i - len + 1)));
      }

  // Last state goes back to state i (length of w) with a transition
  // of the type : (un | y) (to = y.w)
  const letter_t	l[] = {from[n - 1], 0};

  std::string		f = prefsuf(alpha_convert(a2b, from), to);
  int			f_len = f.size();

  a.add_io_transition(s[n - 1], s[f_len], l, to.substr(0, n - f_len));

  return a;
}

automaton_t
replace_right(const std::string& from,	const std::string& to,
	      const alphabet_t& A,	const alphabet_t& B)
{
  monoid_elt_t from_elt(A, from);
  monoid_elt_t to_elt(B, to);
  from_elt.mirror();
  to_elt.mirror();

  automaton_t left = replace_left(from_elt.value(), to_elt.value(), A, B);
  return transpose(left);
}

int
main()
{
  alphabet_t	A;
  A.insert('a');
  A.insert('b');
  /*
     std::map<letter_t, letter_t> a2b = alpha_map(A, B);
     std::map<letter_t, letter_t> a2c = alpha_map(A, C);
     */
  std::string	from, to;

  std::cout << "Enter your pattern over " << A <<" : ";
  std::cin >> from;

  std::cout << "Enter your replacement pattern over " << A <<" : ";
  std::cin >> to;

  /*-----------------.
  | Left automaton.  |
  `-----------------*/

  automaton_t	left_auto = replace_left(from, to, A, A);

  tools::dot_display(left_auto, "G", true);
  eval_an_expression(left_auto);

  /*------------------.
  | Right automaton.  |
  `------------------*/

  automaton_t	right_auto = replace_right(from, to, A, A);

  tools::dot_display(right_auto, "D", true);
  eval_an_expression(right_auto);

  /*-------------------.
  | Result automaton.  |
  `-------------------*/

  automaton_t	res_auto = make_automaton(A, A);
  realtime_composition(left_auto, right_auto, res_auto);

  /*----------------.
  | Dump and eval.  |
  `----------------*/

  tools::dot_display(res_auto, "GD", true);
  eval_an_expression(res_auto);
}

