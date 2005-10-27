// vcsn_random_generator.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003 The Vaucanson Group.
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

