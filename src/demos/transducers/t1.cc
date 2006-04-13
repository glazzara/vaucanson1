// t1.cc: this file is part of the Vaucanson project.
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
#include <vaucanson/fmp_transducer.hh>
#include <vaucanson/tools/xml_dump.hh>

int main()
{
  using namespace vcsn;
  using namespace vcsn::fmp_transducer;

  first_alphabet_t A;
  A.insert('a');
  A.insert('b');

  automaton_t t1 = make_automaton(A, A);


  hstate_t p = t1.add_state();
  hstate_t q = t1.add_state();
  hstate_t r = t1.add_state();

  t1.set_initial(q);
  t1.set_final(q);
  t1.set_final(p);

  t1.add_weighted_transition(p, q, true, make_couple(A, A, "1", "b").value());
  t1.add_weighted_transition(q, p, true, make_couple(A, A, "a", "1").value());
  t1.add_weighted_transition(q, r, true, make_couple(A, A, "1", "a").value());
  t1.add_weighted_transition(r, q, true, make_couple(A, A, "b", "1").value());

  tools::xml_dump(std::cout, t1, "t1");
}

