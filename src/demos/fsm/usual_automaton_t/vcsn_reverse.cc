   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/misc/fsm_dump.hh> 
   #include <vaucanson/algorithms/transpose.hh>
   using namespace vcsn;

   int main(int argc, char **argv)
   {
     automaton_t automaton;
     misc::fsm_load(std::cin, automaton);
     automaton_t auto_m = auto_transpose(automaton);
     misc::fsm_dump(std::cout, auto_m);
     return EXIT_SUCCESS;
   }
