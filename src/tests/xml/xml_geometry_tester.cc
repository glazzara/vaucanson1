// xml_geometry_tester.cc: this file is part of the Vaucanson project.
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
#include <string.h>
#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/tools/dot_dump.hh>
#include <vaucanson/xml/XML.hh>

int main(int argc, char** argv)
{
  using namespace vcsn;
  using namespace vcsn::xml;

  if (argc > 1 && ! strcmp(argv[1], "output"))
    {
      using namespace vcsn::boolean_automaton;

      alphabet_t alpha; alpha.insert('a'); alpha.insert('b');
      automaton_t a = new_automaton(alpha);

      hstate_t s0 = a.add_state();
      hstate_t s1 = a.add_state();
      hstate_t s2 = a.add_state();
      hedge_t e;

      a.set_initial(s0);
      a.set_final(s1);

      e = a.add_letter_edge(s0, s1, 'a');
      a.add_letter_edge(s1, s2, 'b');

      a.geometry().edges()[e] = make_pair(1, 2);
      a.geometry().states()[s2] = make_pair(12, 14);
      a.geometry().initials()[s0] = make_pair(10, 3.14);
      a.geometry().finals()[s1] = make_pair(5, 5);

      std::cout << automaton_saver(a, io::string_out(), xml::XML());
    }
  else
    {
      using namespace vcsn::boolean_automaton;

      alphabet_t alpha;
      automaton_t a = new_automaton(alpha);

      std::cin >> automaton_loader(a, io::string_out(), xml::XML());
      vcsn::tools::dot_dump(std::cout, a, "A");
    }
}
