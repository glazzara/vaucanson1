// slowbig.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2009, 2011 The Vaucanson Group.
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
#include <vaucanson/z_min_plus_automaton.hh>

using namespace vcsn;
using namespace vcsn::z_min_plus_automaton;
#include <vaucanson/tools/dumper.hh>

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

  automaton_t slowbig = make_automaton(A);

  hstate_t p = slowbig.add_state();
  hstate_t q = slowbig.add_state();
  hstate_t r = slowbig.add_state();


  series_set_elt_t pp (slowbig.structure().series());
  pp.assoc(a, 0);
  pp.assoc(b, 0);
  slowbig.add_series_transition(p, p, pp);

  series_set_elt_t pq (slowbig.structure().series());
  pq.assoc(b, 0);
  slowbig.add_series_transition(p, q, pq);

  series_set_elt_t qq (slowbig.structure().series());
  qq.assoc(a, 1);
  slowbig.add_series_transition(q, q, qq);

  series_set_elt_t qr (slowbig.structure().series());
  qr.assoc(b, 0);
  slowbig.add_series_transition(q, r, qr);

  series_set_elt_t rr (slowbig.structure().series());
  rr.assoc(a, 0);
  slowbig.add_series_transition(r, r, rr);

  series_set_elt_t rq (slowbig.structure().series());
  rq.assoc(a, 1);
  slowbig.add_series_transition(r, q, rq);

  slowbig.set_initial(p);
	slowbig.set_initial(q);
	slowbig.set_initial(r);
  slowbig.set_final(r);

  tools::dumper(argc, argv)(std::cout, slowbig, "slowbig");
}
