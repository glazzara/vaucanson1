// xml_int_z_trans_tester.cc: this file is part of the Vaucanson project.
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
#include <iostream>
#include <string.h>
#include <vaucanson/int_z_transducer.hh>
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
    using namespace vcsn::int_z_transducer;

    alphabet_t alpha1; alpha1.insert(1); alpha1.insert(10);
    alphabet_t alpha2; alpha2.insert("2"); alpha2.insert("20");

    automaton_t a = make_automaton(alpha1, alpha2);

    hstate_t s0 = a.add_state();
    hstate_t s1 = a.add_state();
    hstate_t s2 = a.add_state();

    // Predeclarations.
    monoid_elt_t input_word(a.structure().series().monoid());
    monoid_elt_t output_word(a.structure().series().semiring().monoid());

    a.set_initial(s0);
    output_word = monoid_elt_t(a.structure().series().semiring().monoid());
    parse_word(output_word, "2");
    a.set_o_final(s1, output_word);

    series_set_elt_t ss4(a.structure().series());
    a.add_series_transition (s0, s0, ss4);
    input_word = monoid_elt_t(a.structure().series().monoid());
    parse_word(input_word, "1");
    a.add_io_transition(s0, s1, input_word, 20);
    output_word = monoid_elt_t(a.structure().series().semiring().monoid());
    parse_word(output_word, "2#2");
    a.add_io_transition(s1, s2, 10, output_word);

    std::cout << automaton_saver(a, string_out(), xml::XML());
  }
  else
  {
    using namespace vcsn::int_z_transducer;

    alphabet_t alpha1;
    alphabet_t alpha2;

    automaton_t a = make_automaton(alpha1, alpha2);

    std::cin >> automaton_loader(a, string_out(), xml::XML());
    dot_dump(std::cout, a, "T");
  }
}

