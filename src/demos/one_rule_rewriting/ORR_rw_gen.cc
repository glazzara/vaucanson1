// ORR_rw_gen.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006, 2008 The Vaucanson Group.
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
#include "one_rule_rewriting.hh"

#include <vaucanson/boolean_transducer.hh>

#include <vaucanson/xml/contexts/rw.hh>
#include <vaucanson/tools/xml_dump.hh>

static
void
usage(int, char** argv)
{
  std::cerr << "Usage: " << std::endl
	    << "\t" << argv[0] << " <word> <replace_word> <name>" << std::endl;
  exit(1);
}

int main(int argc, char** argv)
{
  using namespace ORR;
  using namespace vcsn;
  using namespace vcsn::boolean_transducer;

  if (argc != 4)
    usage(argc, argv);

  alphabet_t	A;

  A.insert('a');
  A.insert('b');

  std::string	from = argv[1];
  std::string	to = argv[2];
  std::string	name = argv[3];

  automaton_t	left_auto = replace_left(from, to, A, A);

  automaton_t	right_auto = replace_right(from, to, A, A);

  automaton_t	left_right_auto = make_automaton(A, A);
  automaton_t	right_left_auto = make_automaton(A, A);

  rw_composition(left_auto, right_auto, left_right_auto);
  rw_composition(right_auto, left_auto, right_left_auto);

  std::string	left_name = name + "_left.xml";
  std::string	right_name = name + "_right.xml";
  std::string	left_right_name = name + "_left_right.xml";
  std::string	right_left_name = name + "_right_left.xml";

  std::ofstream left(left_name.c_str());
  std::ofstream right(right_name.c_str());
  std::ofstream left_right(left_right_name.c_str());
  std::ofstream right_left(right_left_name.c_str());

  tools::xml_dump(left, left_auto, "left");
  tools::xml_dump(right, right_auto, "right");
  tools::xml_dump(left_right, left_right_auto, "left_right");
  tools::xml_dump(right_left, right_left_auto, "right_left");


  std::cout << "Cautious left sequential transducer: " << left_name
	    << std::endl
	    << "Cautious right sequential transducer: " << right_name
	    << std::endl
	    << "Left transducer composed by right transducer: "
	    << left_right_name
	    << std::endl
	    << "Right transducer composed by left transducer: "
	    << right_left_name
	    << std::endl;

  return 0;
}
