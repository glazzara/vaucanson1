// minimization_bench_hopcroft.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.
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
#include <vaucanson/tools/usual_macros.hh>
#include <minimization_stroppa/usual_ana_predefs.hh>

#include <minimization_stroppa/tools.hh>

#include <vaucanson/tools/bencher.hh>
#include <minimization_stroppa/init.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <vaucanson/algorithms/determinize.hh>
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

  std::cout << "Automaton has " << a.states().size() << " states "
	    << " and " << a.edges().size() << " edges." << std::endl;

  VCSN_BENCH_START;
  a = minimization_hopcroft(a);
  VCSN_BENCH_STOP_AND_PRINT;
}

