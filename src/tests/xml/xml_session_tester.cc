// xml_session_tester.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005 The Vaucanson Group.
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
#include <vaucanson/xml/XML.hh>
#include <vaucanson/xml/session.hh>
#include <vaucanson/tools/dot_dump.hh>


int main(int argc, char** argv)
{
  using namespace vcsn;
  using namespace vcsn::boolean_automaton;
  using namespace vcsn::xml;

  alphabet_t alpha; alpha.insert('a'); alpha.insert('b');
  automaton_t a = new_automaton(alpha);

  hstate_t s0 = a.add_state();
  hstate_t s1 = a.add_state();
  hstate_t s2 = a.add_state();

  a.add_letter_transition(s0, s1, 'a');
  a.add_letter_transition(s1, s2, 'b');

  xml_session s;

  if (argc > 1 && ! strcmp(argv[1], "output"))
  {
    s << a;
    s << a;

    std::cout << s;
  }
  else
  {
    std::cin >> s;
    s << a;
    s >> a;
    vcsn::tools::dot_dump(std::cout, a, "A");
  }
}

