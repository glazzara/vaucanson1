   #include <iostream>
   #include "toolbox.hh"
   #include "arg.hh"
   #include <vaucanson/tools/gen_random.hh>
   #include <vaucanson/misc/fsm_dump.hh>   

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
     misc::fsm_dump(std::cout, automaton);
     return EXIT_SUCCESS;
   }
