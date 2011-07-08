// a1.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2007 The Vaucanson Group.
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
#include <vaucanson/boolean_automaton.hh>

using namespace vcsn;
using namespace vcsn::boolean_automaton;

#include <vaucanson/tools/dumper.hh>


int
main(int argc, char **argv)
{

  alphabet_t  A;
  A.insert('a');
  A.insert('b');

  automaton_t oddb = make_automaton(A);

  hstate_t p = oddb.add_state();
  hstate_t q = oddb.add_state();

  oddb.add_letter_transition(p, p, 'a');
  oddb.add_letter_transition(q, q, 'a');

  oddb.add_letter_transition(p, q, 'b');
  oddb.add_letter_transition(q, p, 'b');


  oddb.set_initial(p);
  oddb.set_final(q);

  tools::dumper(argc, argv)(std::cout, oddb, "oddb");
}
