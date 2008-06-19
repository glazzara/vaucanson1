// xml_trans_tester.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/boolean_transducer.hh>
#include <vaucanson/tools/dot_dump.hh>
#include <vaucanson/xml/contexts/rw.hh>
#include <vaucanson/xml/XML.hh>


int main(int argc, char** argv)
{
  using namespace vcsn;
  using namespace vcsn::xml;
  using namespace vcsn::tools;

  if (argc > 1 && ! strcmp(argv[1], "output"))
  {
    using namespace vcsn::boolean_transducer;

    alphabet_t alpha1; alpha1.insert('a'); alpha1.insert('b');
    alphabet_t alpha2; alpha2.insert('x'); alpha2.insert('y');

    automaton_t a = make_automaton(alpha1, alpha2);

    hstate_t s0 = a.add_state();
    hstate_t s1 = a.add_state();
    hstate_t s2 = a.add_state();

    a.set_initial(s0);
    a.set_o_final(s1, "x");

    series_set_elt_t ss4(a.structure().series());
    a.add_series_transition (s0, s0, ss4);
    a.add_io_transition(s0, s1, "a", "y");
    a.add_io_transition(s1, s2, "b", "x");

    std::cout << automaton_saver(a, string_out(), xml::XML());
  }
  else
  {
    using namespace vcsn::boolean_transducer;

    alphabet_t alpha1;
    alphabet_t alpha2;

    automaton_t a = make_automaton(alpha1, alpha2);

    std::cin >> automaton_loader(a, string_out(), xml::XML());
    dot_dump(std::cout, a, "T");
  }
}

