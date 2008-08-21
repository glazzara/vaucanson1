// u1.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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



   /*---------------------------------------------------------.
   | This transducer comes from the article Inside Vaucanson. |
   `--------------------------------------------------------*/



int
main ()
{
  first_alphabet_t	B;
  first_alphabet_t	C;

  B.insert('x');
  B.insert('y');

  C.insert('u');
  C.insert('v');


   /*---------------------------.
   | Creation of transducer U1  |
   `--------------------------*/

   automaton_t u1 = make_automaton(B, C);

   hstate_t s = u1.add_state();
   hstate_t t = u1.add_state();
   hstate_t u = u1.add_state();

   u1.set_initial(s);
   u1.set_initial(t);
   u1.set_final(t);

   u1.add_weighted_transition(s, t, true, make_couple(B, C, "x", "").value());
   u1.add_weighted_transition(t, s, true, make_couple(B, C, "", "v").value());
   u1.add_weighted_transition(t, u, true, make_couple(B, C, "y", "").value());
   u1.add_weighted_transition(u, t, true, make_couple(B, C, "", "u").value());

   tools::xml_dump(std::cout, u1, "u1");
   return 0;
}
