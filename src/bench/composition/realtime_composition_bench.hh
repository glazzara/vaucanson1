// realtime_composition_bench.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2008 The Vaucanson Group.
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
#include <vaucanson/algorithms/rw_composition.hh>
#include <vaucanson/algorithms/transpose.hh>

using namespace vcsn;
using namespace vcsn::boolean_transducer;

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

automaton_t
replace_left(const std::string& from,	const std::string& to,
	     const alphabet_t& A,	const alphabet_t& B)
{
  automaton_t	a = make_automaton(A, B);

  int		n = from.size();

  // Create a vector to handle all the states.
  std::vector<hstate_t>	s (n);

  // Create states and set them all final.
  for (int i = 0; i < n; ++i)
  {
    s[i] = a.add_state();
    a.set_o_final(s[i], from.substr(0, i));
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
			    in.substr(0, i - len + 1));
      }

  // Last state goes back to state i (length of w) with a transition
  // of the type : (un | y) (to = y.w)
  const letter_t	l[] = {from[n - 1], 0};

  std::string		f = prefsuf(from, to);
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

void realtime_composition_bench(int n)
{
  alphabet_t	A;
  A.insert('a');
  A.insert('b');

  alphabet_t	B;
  B.insert('a');
  B.insert('b');

  alphabet_t	C;
  C.insert('a');
  C.insert('b');

  std::string	from, to;

  from = "a";
  to = "b";

  for (int i = 0; i < n; ++i)
  {
    from += "b";
    to += "a";
  }

  std::stringstream n_str;
  n_str << n;

  BENCH_START("Vaucanson composition (realtime)",
	      "FIXME.");

  automaton_t	left_auto = replace_left(from, to, A, B);
  automaton_t	right_auto = replace_right(from, to, B, C);
  automaton_t	res_auto = make_automaton(A, C);

  rw_composition(left_auto, right_auto, res_auto);

  BENCH_STOP();

  // Set extra parameters/results
  BENCH_PARAMETER("n", (long) n);
  BENCH_RESULT("left states", (long) left_auto.states().size());
  BENCH_RESULT("left transitions", (long) left_auto.transitions().size());
  BENCH_RESULT("right states", (long) right_auto.states().size());
  BENCH_RESULT("right transitions",(long) right_auto.states().size());
  BENCH_RESULT("states", (long) res_auto.states().size());
  BENCH_RESULT("transitions", (long) res_auto.states().size());

  std::string name = "realtime/bench_realtime_composition_" + n_str.str();

  // Save and print
  BENCH_VCSN_SAVE_AND_PRINT(name);
}
