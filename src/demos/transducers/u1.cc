// u1.cc: this file is part of the Vaucanson project.
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

  automaton_t u1 = new_automaton(A, A);

  hstate_t s = u1.add_state();
  hstate_t t = u1.add_state();
  hstate_t u = u1.add_state();

  u1.set_initial(t);
  u1.set_final(s);
  u1.set_final(t);

  u1.add_weighted_edge(s, t, true, make_couple(A, A, "a", "1").value());
  u1.add_weighted_edge(t, s, true, make_couple(A, A, "1", "b").value());
  u1.add_weighted_edge(t, u, true, make_couple(A, A, "b", "1").value());
  u1.add_weighted_edge(u, t, true, make_couple(A, A, "1", "a").value());

  tools::xml_dump(std::cout, u1, "u1");
}

