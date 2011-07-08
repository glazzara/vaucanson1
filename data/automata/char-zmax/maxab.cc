// c1.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2009 The Vaucanson Group.
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
#include <vaucanson/z_max_plus_automaton.hh>

using namespace vcsn;
using namespace vcsn::z_max_plus_automaton;
#include <vaucanson/tools/dumper.hh>

// This automaton comes from ETA p. 435, example 2.5.  With {a,b}
// changed into {0,1}.

int
main(int argc, char **argv)
{
  alphabet_t  A;
  A.insert('a');
  A.insert('b');
  monoid_t  Astar (A);
  monoid_elt_t  a (Astar, "a");
  monoid_elt_t  b (Astar, "b");

//
//
//

  automaton_t maxab = make_automaton(A);

  hstate_t p = maxab.add_state();
  hstate_t q = maxab.add_state();


  series_set_elt_t sp (maxab.structure().series());
  sp.assoc(a, 1);
  sp.assoc(b, 0);
  maxab.add_series_transition(p, p, sp);


  series_set_elt_t sq (maxab.structure().series());
  sq.assoc(a, 0);
  sq.assoc(b, 1);
  maxab.add_series_transition(q, q, sq);

  maxab.set_initial(p); maxab.set_initial(q);
  maxab.set_final(p); maxab.set_final(q);

  tools::dumper(argc, argv)(std::cout, maxab, "maxab");
}
