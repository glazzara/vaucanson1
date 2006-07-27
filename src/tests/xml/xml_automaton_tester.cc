// xml_automaton_tester.cc: this file is part of the Vaucanson project.
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

#include <cstring>
#include <iostream>
#define CONTEXT_HEADER <vaucanson/CONTEXT.hh>
#include CONTEXT_HEADER
#include <vaucanson/tools/dot_dump.hh>
#include <vaucanson/xml/XML.hh>


int main(int argc, char** argv)
{
  using namespace vcsn;
  using namespace vcsn::xml;
  using namespace vcsn::CONTEXT;

  if (argc > 1 && ! strcmp(argv[1], "output"))
  {
    alphabet_t alpha; alpha.insert('a'); alpha.insert('b');
    automaton_t a = make_automaton(alpha);

    hstate_t s0 = a.add_state();
    hstate_t s1 = a.add_state();
    hstate_t s2 = a.add_state();

    a.set_initial(s0);
    a.set_final(s1);

    a.add_letter_transition(s0, s1, 'a');
    a.add_letter_transition(s1, s2, 'b');

    std::cout << automaton_saver(a, io::string_out(), xml::XML());
  }
  else
  {
    alphabet_t alpha;
    automaton_t a = make_automaton(alpha);

    std::cin >> automaton_loader(a, io::string_out(), xml::XML());
    vcsn::tools::dot_dump(std::cout, a, "A");
  }
}
