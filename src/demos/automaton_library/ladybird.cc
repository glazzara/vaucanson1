// ladybird.cc: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//

/*
 * @file ladybird.cc
 *
 * Build an automaton "An" with  "n" states whose determinized has 2^n
 * states.
 */

#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/tools/xml_dump.hh>

#include <ostream>
#include <sstream>

int main(int argc, char** argv)
{
  if (argc != 2)
    {
      std::cerr << "Usage: " << argv[0] << " <n>" << std::endl;
      return 1;
    }

  unsigned n;
  {
    std::istringstream is (argv[1]);
    is >> n;
  }

  std::string nstates (argv[1]);

  using vcsn::boolean_automaton::alphabet_t;
  using vcsn::boolean_automaton::automaton_t;

  alphabet_t	alpha;
  alpha.insert('a');
  alpha.insert('b');
  alpha.insert('c');

  automaton_t an = vcsn::boolean_automaton::new_automaton(alpha);

  vcsn::hstate_t p = an.add_state();
  vcsn::hstate_t x = p;
  for(unsigned i = 1; i < n; ++i)
    {
      vcsn::hstate_t y = an.add_state();
      an.add_letter_edge(x, y, 'a');an.add_letter_edge(y, y, 'b');
      an.add_letter_edge(y, y, 'c');an.add_letter_edge(y, p, 'c');
      x = y;
    }
  an.add_letter_edge(x, p, 'a');
  an.set_initial(p); an.set_final(p);

  std::string name = "ladybird" + nstates + ".xml";
  std::ofstream file(name.c_str());
  vcsn::tools::xml_dump(file, an, "ladybird");

  std::cout << "File " << name << " has been created." << std::endl;
}

