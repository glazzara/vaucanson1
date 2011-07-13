// ORR.cc: this file is part of the Vaucanson project.
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

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <vaucanson/misc/contract.hh>
#include <vaucanson/boolean_transducer.hh>
#include <vaucanson/algorithms/transpose.hh>
#include <vaucanson/algorithms/sub_normalize.hh>
#include <vaucanson/algorithms/rw_to_fmp.hh>
#include <vaucanson/fmp_transducer.hh>
#include <vaucanson/xml/contexts/fmp.hh>


using namespace vcsn;


std::map<boolean_transducer::letter_t, boolean_transducer::letter_t>
alpha_map(const boolean_transducer::alphabet_t& A,
    const boolean_transducer::alphabet_t& B)
{
  using namespace boolean_transducer;
  typedef alphabet_t::const_iterator alphabet_iterator;

  std::map<letter_t, letter_t>  m;

  alphabet_iterator j = B.begin();
  for_all_letters(i, A)
  m[*i] = *j++;

  return m;
}


/**
 * Convert one word from a source alphabet to a destition
 * alphabet using the provided map.
 *
 * @param conv_map
 *   A map between two alphabets.
 * @param str
 *   A word to convert.
 * @return
 *   The word after convertion.
 */
std::string
alpha_convert(const std::map<boolean_transducer::letter_t, boolean_transducer::letter_t>& conv_map,
  const std::string& str)
{
  using namespace boolean_transducer;
  std::string r;
  int n = str.size();
  r.reserve(n);

  for (int i = 0; i < n; ++i)
    r += conv_map.find(str[i])->second;

  return r;
}


std::string
prefsuf(const std::string& u, const std::string& v)
{
  int vs = v.size();
  int s = std::min(u.size(), v.size());

  for (int n = s; n > 0; --n)
  {
    std::string tmp = u.substr(0, n);
    if (tmp == v.substr(vs - n, n))
return tmp;
  }

  return "";
}


/**
 * Generate a boolean transducer who apply the rule by reading
 * a word from left to right.
 *
 * @param from
 *   A string containing the word being replaced.
 * @param to
 *   A string containing the replacement word.
 * @param A
 *   The alphabet used by the first word.
 * @param B
 *   The alphabet used by the second word.
 * @return
 *   The cautious left automaton.
 */
boolean_transducer::automaton_t
replace_left(const std::string& from, const std::string& to,
       const boolean_transducer::alphabet_t& A, const boolean_transducer::alphabet_t& B)
{
  using namespace boolean_transducer;
  automaton_t a = make_automaton(A, B);

  int   n = from.size();

  // Create a map to make the 2 alphabets correspond.
  std::map<letter_t, letter_t> a2b = alpha_map(A, B);

  // Create a vector to handle all the states.
  std::vector<hstate_t> s (n);

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
const letter_t  l[] = {*j, 0};

const std::string in = from.substr(0, i) + *j;
const std::string factor = prefsuf(from, in);
const int   len = factor.size();

a.add_io_transition(s[i], s[len], l,
        alpha_convert(a2b, in.substr(0, i - len + 1)));
    }

  // Last state goes back to state i (length of w) with a transition
  // of the type : (un | y) (to = y.w)
  const letter_t  l[] = {from[n - 1], 0};

  std::string   f = prefsuf(alpha_convert(a2b, from), to);
  int     f_len = f.size();

  a.add_io_transition(s[n - 1], s[f_len], l, to.substr(0, n - f_len));

  return a;
}


/**
 * Generate a boolean transducer who apply the rule by reading
 * a word from right to left.
 *
 * @param from
 *   A string containing the word being replaced.
 * @param to
 *   A string containing the replacement word.
 * @param A
 *   The alphabet used by the first word.
 * @param B
 *   The alphabet used by the second word.
 * @return
 *   The cautious right automaton.
 */
boolean_transducer::automaton_t
replace_right(const std::string& from, const std::string& to,
  const boolean_transducer::alphabet_t& A,
  const boolean_transducer::alphabet_t& B)
{
  using namespace boolean_transducer;

// We mirror the two word, apply replace_left and return
// the transposed automaton.

  monoid_elt_t from_elt(A, from);
  monoid_elt_t to_elt(B, to);

  from_elt.mirror();
  to_elt.mirror();

  automaton_t left = replace_left(from_elt.value(), to_elt.value(), A, B);

  return transpose(left);
}


static
void
usage(int, char** argv)
{
  const char* program = strrchr(argv[0], '/');
  program = program? program+1 : argv[0];
  std::cerr << "Usage: " << std::endl
      << "\t" << program << " <word> <replace_word> <name> [<fmt>]" << std::endl;
  exit(1);
}


using namespace vcsn::fmp_transducer;
#include <vaucanson/tools/dumper.hh>


int main(int argc, char** argv)
{
  //using namespace ORR;

  if ((argc != 5) && (argc != 4))
    usage(argc, argv);
  const char* format = (argc == 5) ? argv[4] : "xml";

  boolean_transducer::alphabet_t  A;

  for(char* i = argv[1]; (*i)!=0; i++)
  {
    A.insert(*i);
  }
  for(char* i = argv[2]; (*i)!=0; i++)
  {
    A.insert(*i);
  }
  std::string from = argv[1];
  std::string to = argv[2];
  std::string name = argv[3];

  // right
  boolean_transducer::automaton_t left_auto = replace_left(from, to, A, A);

  automaton_t fmp_left = make_automaton(A, A);
  rw_to_fmp(left_auto, fmp_left);

  automaton_t sub_left = make_automaton(A, A);
  sub_normalize(fmp_left, sub_left);

  // left
  boolean_transducer::automaton_t right_auto = replace_right(from, to, A, A);

  automaton_t fmp_right = make_automaton(A, A);
  rw_to_fmp(right_auto, fmp_right);

  automaton_t sub_right = make_automaton(A, A);
  sub_normalize(fmp_right, sub_right);

  // output
  std::string left_name = name + "_left."+format;//.xml";
  std::string right_name = name + "_right."+format;//.xml";

  std::ofstream left_file(left_name.c_str());
  std::ofstream right_file(right_name.c_str());

  vcsn::tools::dumper (argc, argv, 4)(left_file, sub_left, "left");
  vcsn::tools::dumper (argc, argv, 4)(right_file, sub_right, "right");

  left_file.close();
  right_file.close();

  std::cout << "Cautious left sequential transducer: " << left_name
      << std::endl
      << "Cautious right sequential transducer: " << right_name
      << std::endl;
}
