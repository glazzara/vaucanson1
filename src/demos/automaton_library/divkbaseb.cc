// divkbaseb.cc: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2004, 2005 The Vaucanson Group.
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
#include <sstream>

#include <vaucanson/boolean_automaton.hh>
using namespace vcsn::boolean_automaton;
#include "dumper.hcc"

int
main(int argc, char** argv)
{
  if (argc < 3)
    {
      std::cerr << "Usage:" << std::endl
		<< "\t" << argv[0] << " <divisor> <base> [<fmt>]" << std::endl;
      return 1;
    }

  int			divisor;
  {
    std::istringstream	is (argv[1]);
    is >> divisor;
  }

  int			base;
  {
    std::istringstream	is (argv[2]);
    is >> base;
  }

  std::string div (argv[1]);
  std::string b (argv[2]);

  alphabet_t	alpha;
  for (int i = 0; i < base; ++i)
    alpha.insert(i < 10 ? '0' + i : 'A' + i);

  automaton_t	a = new_automaton(alpha);

  for (int i = 0; i < divisor; ++i)
    a.add_state();
  a.set_initial(0);
  a.set_final(0);

  int d = 0;
  for (int i = 0; i < divisor; ++i)
    for_each_letter(l, alpha)
    {
      a.add_letter_edge(i, d, *l);
      d = (d + 1) % divisor;
    }

  dumper dump(argc, argv, 3);

  std::string name = "div" + div + "base" + b + "." + dump.get_fmt();
  std::ofstream file(name.c_str());
  dump(file, a, name);

  std::cout << "File " << name << " has been created." << std::endl;
}

