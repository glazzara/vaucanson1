   #include <iostream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/misc/fsm_dump.hh>   

   int main(int argc, char **argv)
   {
     srand(time(0));
     GenRandomAutomata<automaton_t> gen;
     automaton_t automaton = gen.generate(10, 20);
     misc::fsm_dump(std::cout, automaton);
     return EXIT_SUCCESS;
   }
