// t1.cc: this file is part of the Vaucanson project.
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

#include <vaucanson/fmp_transducer.hh>

#include <vaucanson/xml/contexts/fmp.hh>
#include <vaucanson/tools/xml_dump.hh>

using namespace vcsn;
using namespace vcsn::fmp_transducer;



   /*----------------------------------------------------------.
   | This transducer comes from the article Inside Vaucanson.  |
   `----------------------------------------------------------*/



int
main ()
{

  first_alphabet_t	A;
  second_alphabet_t	B;

  A.insert('a');
  A.insert('b');

  B.insert('x');
  B.insert('y');

  /*----------------------------.
  | Creation of transducer T1.  |
  `----------------------------*/

  automaton_t t1 = make_automaton(A, B);

  hstate_t p = t1.add_state();
  hstate_t q = t1.add_state();
  hstate_t r = t1.add_state();

  t1.set_initial(q);
  t1.set_final(q);
  t1.set_final(p);

  t1.add_weighted_transition(p, q, true, make_couple(A, B, "", "y").value());
  t1.add_weighted_transition(q, p, true, make_couple(A, B, "a", "").value());
  t1.add_weighted_transition(q, r, true, make_couple(A, B, "", "x").value());
  t1.add_weighted_transition(r, q, true, make_couple(A, B, "b", "").value());

  tools::xml_dump (std::cout, t1, "t1");
  return 0;
}
