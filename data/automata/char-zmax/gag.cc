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

  automaton_t gag = make_automaton(A);

  hstate_t i = gag.add_state();
  hstate_t p = gag.add_state();
  hstate_t f = gag.add_state();

  series_set_elt_t si (gag.structure().series());
  si.assoc(a,0);
  si.assoc(b,0);
  gag.add_series_transition(i,i,si);
  gag.add_series_transition(f,f,si);


  series_set_elt_t sip (gag.structure().series());
  sip.assoc(b,0);
  gag.add_series_transition(i,p,sip);

  series_set_elt_t spf (gag.structure().series());
  spf.assoc(b,0);
  gag.add_series_transition(p,f,spf);

  series_set_elt_t sp (gag.structure().series());
  sp.assoc(a,1);
  gag.add_series_transition(p,p,sp);




  gag.set_initial(i);
  gag.set_final(f);
  gag.set_initial(p);
  gag.set_final(p);
  //gag.set_final(p);
  tools::dumper(argc, argv)(std::cout, gag, "gag");
}
