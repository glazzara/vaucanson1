// d1.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2009 The Vaucanson Group.
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
#include <vaucanson/z_automaton.hh>

using namespace vcsn;
using namespace vcsn::z_automaton;
#include <vaucanson/tools/dumper.hh>

// This automaton comes from ETA: exercise 2.15, p. 437.

int
main(int argc, char **argv)
{
  alphabet_t	A;
  A.insert('a');
  A.insert('b');
  monoid_t	Astar (A);
  monoid_elt_t	a (Astar, "a");
  monoid_elt_t	b (Astar, "b");

  automaton_t d1 = make_automaton(A);

  hstate_t p = d1.add_state();
  hstate_t q = d1.add_state();

  series_set_elt_t sp (d1.structure().series());
  sp.assoc(a, 1);
  sp.assoc(b, 1);

  series_set_elt_t sq (d1.structure().series());
  sq.assoc(a, 1);
  sq.assoc(b, -1);

  d1.set_initial(p);
  d1.add_series_transition(p, p, sp);
  d1.add_series_transition(p, q, sq);
  d1.add_series_transition(q, q, sp);
  d1.set_final(q);

  tools::dumper(argc, argv)(std::cout, d1, "d1");
}
