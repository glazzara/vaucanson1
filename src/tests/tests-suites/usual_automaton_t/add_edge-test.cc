/*  Vaucanson, a generic library for finite state machines.
Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include <vaucanson/tools/usual.hh>
  #include <check/tests_stuff.hh>
  #include <automata/implementation_check/add_edge_test.hh>

  int main(int argc, char **argv)
  {
  using namespace vcsn;
  using namespace vcsn::tools;

  tests::verbose_level_e verbose = tests::low;
  srand(time(0));

  if (argc > 1) 
    {
      if (argv[1] == std::string("--no-verbose"))
	verbose = tests::none;
      else if (argv[1] == std::string ("--high-verbose"))
	verbose = tests::high;
      else 
	verbose = tests::low;
    };
    tests::Tester t(verbose);
    if (add_edge_test<usual_automaton_t>(t)) 
      return EXIT_SUCCESS;
    else
      return EXIT_FAILURE;
  }
  
