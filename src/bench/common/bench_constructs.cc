// bench_constructs.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2007, 2008, 2009 The Vaucanson Group.
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

#include <iostream>
#include <sstream>

#include <common/bench_macros.hh>

#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/tools/dot_dump.hh>

using namespace vcsn;
using namespace vcsn::boolean_automaton;
using namespace vcsn::tools;

#include <common/bench_constructs.hh>

#define DUMP(Name, N)				\
do {						\
  std::stringstream str;			\
  str << Name;					\
  if (N)					\
    str << "_" << N;				\
  str << ".dot";				\
  std::ofstream file(str.str().c_str());	\
  dot_dump(file, aut, "");			\
  file.close();					\
} while(0)

int main(int argc, char* argv[])
{
  automaton_t aut;
  for (int n = 1; n < 11; ++n)
  {
    aut = aut_ladybird(n);
    DUMP("aut_ladybird", n);
    aut = aut_2n(n);
    DUMP("aut_2n", n);
    aut = aut_debruijn(n);
    DUMP("aut_debruijn", n);
    aut = aut_linear_eps(n);
    DUMP("aut_linear_eps", n);
    aut = aut_complete(n);
    DUMP("aut_complete", n);
  }
  aut = aut_b();
  DUMP("aut_b", 0);
}
