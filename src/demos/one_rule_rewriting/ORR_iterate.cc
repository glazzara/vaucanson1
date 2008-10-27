// ORR_iterate.cc: this file is part of the Vaucanson project.
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
//#include "one_rule_rewriting.hh"

#include <sstream>

#include <vaucanson/boolean_transducer.hh>
#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/fmp_transducer.hh>

#ifdef DEBUG
#include <vaucanson/tools/xml_dump.hh>
#include <vaucanson/tools/dot_display.hh>
#endif

#include "shortest.hh"

using namespace std;
using namespace vcsn;
using namespace vcsn::boolean_transducer;

int
string_to_int(const string& s)
{
  stringstream ss(s);
  int res;
  ss >> res;
  if (!ss.eof ()) {
    cerr << "invalid integer: " << s << endl;
    exit (1);
  }
  return res;
}

string
prefsuf(const string& u, const string& v)
{
  int vs = v.size();
  int s = min(u.size(), v.size());

  for (int n = s; n > 0; n--) {
    string tmp = u.substr(0, n);
    if (tmp == v.substr(vs - n, n))
      return tmp;
  }

  return "";
}

string
alpha_convert(const map<letter_t, letter_t>& conv_map,
              const string& str)
{
  string r;
  int n = str.size();
  r.reserve(n);

  for (int i = 0; i < n; i++)
    r += conv_map.find(str[i])->second;

  return r;
}

map<letter_t, letter_t>
alpha_map(const alphabet_t& A, const alphabet_t& B)
{
  typedef alphabet_t::const_iterator alphabet_iterator;

  map<letter_t, letter_t> m;
  alphabet_iterator j = B.begin();
  for_all_letters(i, A)
    m[*i] = *j++;

  return m;
}

automaton_t
replace_left(const string& from, const string& to,
             const alphabet_t& A, const alphabet_t& B)
{
  automaton_t a = make_automaton(A, B);
  int n = from.size();

  // Create a map between the two alphabets.
  map<letter_t, letter_t> a2b = alpha_map(A, B);

  // Create a vector to handle all the states.
  vector<hstate_t> s(n);

  // Create states and set them all final.
  for (int i = 0; i < n; i++)
  {
    s[i] = a.add_state();
    a.set_o_final(s[i], alpha_convert(a2b, from.substr(0, i)));
  }

  // Set the first state initial.
  a.set_initial(s[0]);

  // Create all the edges of the type (ui | 1).
  for (int i = 0; i < n - 1; i++)
  {
    const letter_t l[] = {from[i], 0};
    a.add_io_transition(s[i], s[i + 1], l, "");
  }

  // Create the backward edges.
  for (int i = 0; i < n; i++)
    for_all_letters(j, A)
      if (*j != from[i])
      {
        const letter_t l[] = {*j, 0};
        const string in = from.substr(0, i) + *j;
        const string factor = prefsuf(from, in);
        const int len = factor.size();
        
        a.add_io_transition(s[i], s[len], l,
                            alpha_convert(a2b, in.substr(0, i - len + 1)));
      }

  // Last state goes back to state i (length of w) with an edge
  // of type (un | y) (to = y.w)
  const letter_t l[] = {from[n - 1], 0};
  string f = prefsuf(alpha_convert(a2b, from), to);
  a.add_io_transition(s[n - 1], s[f.size()], l, to.substr(0, to.size() - f.size()));

  return a;
}

automaton_t
replace_right(const string& from, const string& to,
              const alphabet_t& A, const alphabet_t& B)
{
  monoid_elt_t from_elt(A, from);
  monoid_elt_t to_elt(B, to);
  from_elt.mirror();
  to_elt.mirror();

  automaton_t left = replace_left(from_elt.value(), to_elt.value(), A, B);
  return transpose(left);
}

boolean_automaton::automaton_t
qcq(const boolean_automaton::automaton_t& a)
{
  return transpose(quotient(transpose(quotient(a))));
}

static void
usage(int, char** argv)
{
  cerr << "Usage: " << argv[0] <<
    " <no_of_letters> <word> <replace_word> <name>" << endl;
  exit(1);
}

int
main(int argc, char** argv)
{
  // Read the parameters
  if (argc != 5)
    usage(argc, argv);
  int nb_letter = string_to_int(argv[1]);
  string from = argv[2];
  string to = argv[3];
  string name = argv[4];

  // Creation of the alphabet
  alphabet_t A;
  for (int i = 0; i < nb_letter; i++)
    A.insert('a' + i);

  // Compute an automaton for the non-reduced words
  boolean_automaton::rat_exp_t expA = boolean_automaton::make_rat_exp(A, "0");
  for_all_letters (x, A)
    expA += *x;
  boolean_automaton::rat_exp_t expfrom = boolean_automaton::make_rat_exp(A, from);
  expA.star();
  boolean_automaton::rat_exp_t expL = expA * expfrom * expA;
  boolean_automaton::automaton_t autL = qcq(boolean_automaton::standard_of(expL));

  // The cautious transducers
  automaton_t left_tdc = replace_left(from, to, A, A);
  automaton_t right_tdc = replace_right(from, to, A, A);

  // Perform the iterated composition
  string lr_name = name + "_lr";
  automaton_t lr_tdc = trim(rw_composition(left_tdc, right_tdc));
  automaton_t iter_tdc = right_tdc;
  for (int iteration = 1; true; iteration++)
  {
    boolean_automaton::automaton_t iter_ima = boolean_automaton::make_automaton(A);
    iter_tdc = trim(rw_composition(iter_tdc, lr_tdc));
    fmp_transducer::automaton_t iter_fmp = fmp_transducer::make_automaton(A, A);
    rw_to_fmp(iter_tdc, iter_fmp);
    image(iter_fmp, iter_ima);
    boolean_automaton::automaton_t iter_imac = qcq(realtime(iter_ima));
    cout << "Iteration: " << iteration << ": "
         << iter_imac.states().size() << " states, "
         << iter_imac.transitions().size() << " transitions" << endl;
#ifdef DEBUG
    tools::xml_dump(cout, iter_imac, lr_name);
    tools::dot_display(iter_imac, lr_name, true);
#endif
    
    boolean_automaton::automaton_t autR = product(iter_imac, autL);
    if (trim(autR).states().size() == 0) // Is it reduced?
      cerr << "Reduction complete" << endl;
    else
    {
      cerr << "Shortest unreduced word: " << shortest(autR) << endl
           << "Do you want to iterate [y/n]? " ;
      string user_string;
      getline(cin, user_string);
      if (user_string == "y")
        continue;
    }
    break;
  }

#ifdef DEBUG
    tools::xml_dump(cout, iter_imac, lr_name);
    tools::dot_display(iter_imac, lr_name, true);
#endif
}
