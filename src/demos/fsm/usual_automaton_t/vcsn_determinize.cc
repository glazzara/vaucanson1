   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/misc/fsm_dump.hh> 
   #include <vaucanson/algorithms/determinize.hh>

   int main(int argc, char **argv)
   {
     srand(time(0));
     automaton_t automaton;
     misc::fsm_load(std::cin, automaton);
     automaton_t auto_d = determinize(automaton);
     misc::fsm_dump(std::cout, auto_d);
     return EXIT_SUCCESS;
   }
