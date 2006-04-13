// xml_fmp_tester.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/fmp_transducer.hh>
#include <vaucanson/tools/dot_dump.hh>
#include <vaucanson/xml/XML.hh>


int main(int argc, char** argv)
{
  using namespace vcsn;
  using namespace vcsn::xml;

  if (argc > 1 && ! strcmp(argv[1], "output"))
  {
    using namespace vcsn::fmp_transducer;

    first_alphabet_t alpha1; alpha1.insert('a'); alpha1.insert('b');
    second_alphabet_t alpha2; alpha2.insert('x'); alpha2.insert('y');

    automaton_t a = make_automaton(alpha1, alpha2);

    hstate_t s0 = a.add_state();
    hstate_t s1 = a.add_state();
    hstate_t s2 = a.add_state();

    a.set_initial(s0);

    monoid_elt_value_t m = std::make_pair("a", "x");
    monoid_elt_value_t m2 = std::make_pair("b", "x");
    monoid_elt_value_t m3 = std::make_pair("a", "y");
    series_set_elt_t ss(a.structure().series());
    series_set_elt_t ss2(a.structure().series());
    series_set_elt_t ss3(a.structure().series());
    semiring_elt_value_t sem = true;
    ss.assoc(m, sem);
    ss2.assoc(m3, sem);
    ss3.assoc(m2, sem);

    a.add_series_transition(s0, s1, ss);
    a.add_series_transition(s0, s1, ss2);

    a.set_final(s2, ss3);


    std::cout << automaton_saver(a, io::string_out(), xml::XML());
  }
  else
  {
    using namespace vcsn::fmp_transducer;

    first_alphabet_t alpha1;
    second_alphabet_t alpha2;

    automaton_t a = make_automaton(alpha1, alpha2);

    std::cin >> automaton_loader(a, io::string_out(), xml::XML());
    vcsn::tools::dot_dump(std::cout, a, "FMP");
  }
}

