// xml_label_node_tester.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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
#include <iostream>
#include <string>
#include <vaucanson/z_automaton.hh>
#include <vaucanson/tools/dot_dump.hh>
#include <vaucanson/xml/XML.hh>


int main(int argc, char** argv)
{
  using namespace vcsn;
  using namespace vcsn::xml;
  using namespace vcsn::tools;

  if (argc > 1 && ! strcmp(argv[1], "output"))
  {
    using namespace z_automaton;

    alphabet_t alpha;
    alpha.insert('a');
    alpha.insert('b');
    alpha.insert('c');
    alpha.insert('d');

    automaton_t a = make_automaton(alpha);

    hstate_t s0 = a.add_state();
    hstate_t s1 = a.add_state();
    hstate_t s2 = a.add_state();

    a.set_initial(s0);
    a.set_final(s1);

    a.add_series_transition(s0, s0, make_rat_exp(alpha, "{3} (({2} (a+b))+({5} (c+d)))"));
    a.add_series_transition(s0, s1, make_rat_exp(alpha, "{6} a+{5} b"));
    a.add_series_transition(s0, s2, make_rat_exp(alpha, "a.a+{3} b"));
    a.add_series_transition(s1, s0, make_rat_exp(alpha, "{5} (a.b)"));
    a.add_series_transition(s1, s1, make_rat_exp(alpha, "{5} (a+b)"));

    std::cout << automaton_saver(a, string_out(), xml::XML());
  }
  else
  {
    using namespace z_automaton;

    alphabet_t alpha;
    automaton_t a = make_automaton(alpha);

    std::cin >> automaton_loader(a, string_out(), xml::XML());
    dot_dump(std::cout, a, "A");
  }
}
