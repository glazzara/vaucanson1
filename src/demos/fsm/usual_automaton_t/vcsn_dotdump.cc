   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/misc/fsm_dump.hh> 
   #include <vaucanson/misc/dot_dump.hh> 

    using namespace vcsn;

   int main(int argc, char **argv)
   {
     srand(time(0));
     automaton_t automaton;
     misc::fsm_load(std::cin, automaton);
     misc::dot_dump(std::cout, automaton, "automaton");
     return EXIT_SUCCESS;
   }
