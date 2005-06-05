//////////////////
//
// $Id: compute_lexicon_consistency_old.cc 3 2004-02-03 17:14:25Z nico $
//
//////////////////



#include <vaucanson/tools/usual_macros.hh>
#include <minimization_stroppa/usual_ana_predefs.hh>

#include <minimization_stroppa/tools.hh>

#include <minimization_stroppa/init.hh>
#include <minimization_stroppa/fsm_minimize.hh>
#include <vaucanson/algorithms/standard.hh>
#include <vaucanson/algorithms/closure.hh>

#include <iostream>
#include <cstring>
#include <vector>


int main(unsigned int argc, char **argv) {

  using namespace vcsn;
  using namespace vcsn::tools;


  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " lexicon_file\n";
    exit(1);
  }

  usual_char_automaton_t a = new_automaton<usual_char_automaton_t>(*ascii_alphabet::instance());
  AUTOMATON_TYPES_EXACT(usual_char_automaton_t);

  std::vector<std::string> language = ana::misc::file_to_vector<std::string>(argv[1]);

  init_with_language(a, language);

  star_of_standard_here(a);
  backward_closure_here(a);

  fsm_minimize(a);
}
