// check_rw_composition.cc: this file is part of the Vaucanson project.
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
#include "one_rule_rewriting.hh"

#include <string>

#include <vaucanson/boolean_transducer.hh>
#include <vaucanson/algorithms/rw_composition.hh>

using namespace vcsn;
using namespace vcsn::boolean_transducer;

bool
check_an_expression(const vcsn::boolean_transducer::automaton_t& t,
		    const std::string& str,
		    const std::string& ref)
{
  std::stringstream s_res;
  const alphabet_t& alphabet = t.structure().series().monoid().alphabet();

  using namespace vcsn::boolean_automaton;
  using namespace vcsn::rat; // For setpm and MODE_STAR.

  rat_exp_t exp = make_rat_exp(alphabet, str);

  s_res << setpm(MODE_STAR) << expand(evaluation(t, exp));
  std::string res;
  s_res >> res;

  if (res != ref)
  {
    std::cout << "wrong return value: got " << res << " should be " << ref << std::endl;
    return false;
  }

  return true;
}

int main()
{
  using namespace ORR;
  using namespace vcsn;
  using namespace vcsn::algebra;
  using namespace vcsn::boolean_transducer;

  alphabet_t A;

  A.insert('a');
  A.insert('b');

  // fibonacci rewriting rule
  std::string from = "abb";
  std::string to   = "baa";

  // build the automata
  automaton_t left_auto = replace_left(from, to, A, A);
  realtime_here(left_auto);
  automaton_t right_auto = replace_right(from, to, A, A);

  // composition of left_auto and right_auto
  automaton_t res_auto = make_automaton(A, A);
  rw_composition(left_auto, right_auto, res_auto);

  bool tmp;
  bool ret = true;

  // we check basic cases
  std::cout << "abb -> baa" << std::endl;
  tmp = check_an_expression(res_auto, "abb", "baa");
  ret = ret && tmp;
  std::cout << "babb -> bbaa" << std::endl;
  tmp = check_an_expression(res_auto, "babb", "bbaa");
  ret = ret && tmp;
  std::cout << "ababb -> baaaa" << std::endl;
  tmp = check_an_expression(res_auto, "ababb", "baaaa");
  ret = ret && tmp;


  if (ret)
    std::cout << "All tests went OK." << std::endl;
  else
    std::cout << "Tests failed." << std::endl;

  return !ret;
}
