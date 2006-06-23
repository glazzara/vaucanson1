// vcsn_dotdump.cc: this file is part of the Vaucanson project.
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
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/tools/fsm_dump.hh> 
   #include <vaucanson/tools/dot_dump.hh> 

    using namespace vcsn;

   int main(int argc, char **argv)
   {
     srand(time(0));
     automaton_t automaton;
     tools::fsm_load(std::cin, automaton);
     tools::dot_dump(std::cout, automaton, "automaton");
     return EXIT_SUCCESS;
   }

