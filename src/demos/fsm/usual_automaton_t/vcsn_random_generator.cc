// vcsn_random_generator.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#include <iostream>
   #include "toolbox.hh"
   #include "arg.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh>   

   using namespace toolbox;
    using namespace vcsn;

   int main(int argc, const char **argv)
   {
     Options  options[2] =
     {
       { "-s", o_int, "number of states. [default is 10]", true },
       { "-e", o_int, "number of edges.  [default is 20]" , true }
     };
     OptionsValues values(std::vector<Options>(options, options+2),argc,argv);
     int nb_states = 10;
     int nb_edges  = 20;
     if (values.get_int("-s") != 0)
       nb_states = *values.get_int("-s");
     if (values.get_int("-e") != 0)
       nb_edges = *values.get_int("-e");
     srand(time(0));
     GenRandomAutomata<automaton_t> gen;
     automaton_t automaton = gen.generate(nb_states, nb_edges);
     tools::fsm_dump(std::cout, automaton);
     return EXIT_SUCCESS;
   }

