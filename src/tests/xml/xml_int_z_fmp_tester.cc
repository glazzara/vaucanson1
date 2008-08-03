// xml_int_z_fmp_tester.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/int_z_fmp_transducer.hh>
#include <vaucanson/tools/dot_dump.hh>
#include <vaucanson/xml/contexts/fmp.hh>
#include <vaucanson/xml/XML.hh>


int main(int argc, char** argv)
{
  using namespace vcsn;
  using namespace vcsn::tools;
  using namespace vcsn::xml;

  if (argc > 1 && ! strcmp(argv[1], "output"))
  {
    using namespace vcsn::int_z_fmp_transducer;

    first_alphabet_t alpha1; alpha1.insert(1); alpha1.insert(10);
    second_alphabet_t alpha2; alpha2.insert("2"); alpha2.insert("20");

    automaton_t a = make_automaton(alpha1, alpha2);

    hstate_t s0 = a.add_state();
    hstate_t s1 = a.add_state();
    hstate_t s2 = a.add_state();

    a.set_initial(s0);

    std::basic_string<first_monoid_t::letter_t> x1;
    x1 += 1;
    std::basic_string<first_monoid_t::letter_t> x10;
    x10 += 10;
    x10 += 10;
    std::basic_string<second_monoid_t::letter_t> x2;
    x2 += 2;
    std::basic_string<second_monoid_t::letter_t> x20;
    x20 += 20;

    monoid_elt_value_t m = std::make_pair(x1, x2);
    monoid_elt_value_t m2 = std::make_pair(x10, x2);
    monoid_elt_value_t m3 = std::make_pair(x1, x20);
    series_set_elt_t ss(a.structure().series());
    series_set_elt_t ss2(a.structure().series());
    series_set_elt_t ss3(a.structure().series());
    series_set_elt_t ss4(a.structure().series());
    semiring_elt_value_t sem = 10;
    ss.assoc(m, sem);
    ss2.assoc(m3, sem);
    ss3.assoc(m2, sem);

    a.add_series_transition(s0, s1, ss);
    a.add_series_transition(s0, s1, ss2);
    a.add_series_transition(s0, s2, ss4);

    a.set_final(s2, ss3);


    std::cout << automaton_saver(a, string_out(), xml::XML());
  }
  else
  {
    using namespace vcsn::int_z_fmp_transducer;

    first_alphabet_t alpha1;
    second_alphabet_t alpha2;

    automaton_t a = make_automaton(alpha1, alpha2);

    std::cin >> automaton_loader(a, string_out(), xml::XML());
    vcsn::tools::dot_dump(std::cout, a, "FMP");
  }
}

