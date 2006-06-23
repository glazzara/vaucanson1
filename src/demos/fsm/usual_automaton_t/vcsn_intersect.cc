// vcsn_intersect.cc: this file is part of the Vaucanson project.
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
   #include <fstream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh> 
   #include <vaucanson/algorithms/product.hh>
   using namespace vcsn;

   int main(int argc, char **argv)
   {
    if (argc < 2)
      exit(EXIT_FAILURE);
     std::ifstream lhs(argv[1]);
     std::ifstream rhs(argv[2]);
     automaton_t lhs_a;
     tools::fsm_load(lhs, lhs_a);
     automaton_t rhs_a;
     tools::fsm_load(rhs, rhs_a);  
     automaton_t auto_m = product(lhs_a, rhs_a);
	tools::fsm_dump(std::cout, auto_m);
     return EXIT_SUCCESS;
   }

