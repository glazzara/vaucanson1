   #include <iostream>
   #include <fstream>
   #include "toolbox.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/misc/fsm_dump.hh> 
   #include <vaucanson/algorithms/product.hh>
   using namespace vcsn;

   int main(int argc, char **argv)
   {
    if (argc < 2)
      exit(EXIT_FAILURE);
     std::ifstream lhs(argv[1]);
     std::ifstream rhs(argv[2]);
     automaton_t lhs_a;
     misc::fsm_load(lhs, lhs_a);
     automaton_t rhs_a;
     misc::fsm_load(rhs, rhs_a);  
     automaton_t auto_m = product(lhs_a, rhs_a);
	misc::fsm_dump(std::cout, auto_m);
     return EXIT_SUCCESS;
   }
