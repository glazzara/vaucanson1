// algorithms.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2004 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

/**
 * @file algorithms.cc
 *
 * Run  various algorithms.  Results are  dumped  in a  XML format  on
 * stdout.
 *
 * Valid invocations are:
 *
 * standard_of <exp>
 * thompson_of <exp>
 * derivatives_automaton <exp>
 * aut_to_exp <file> [state ordering for for eliminations]
 * quotient <file>
 * product <file1> <file2>
 * closure <file>
 * determinize <file>
 * trim <file>
 * transpose <file>
 * eval <file> <string>
 * display <file>
 */

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <list>

#include CONTEXT_HEADER
#include <vaucanson/xml/XML.hh>

#include <vaucanson/algorithms/derivatives_automaton.hh>
#include <vaucanson/algorithms/product.hh>
#include <vaucanson/algorithms/transpose.hh>
#include <vaucanson/algorithms/eval.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/closure.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <vaucanson/algorithms/trim.hh>
#include <vaucanson/tools/dot_display.hh>

using namespace CONTEXT_NAMESPACE;

using namespace vcsn;
using namespace vcsn::io;
using vcsn::xml::XML;

static
void
usage(int, char** argv)
{
  std::cerr << "Usage: " << std::endl
	    << "\t" << argv[0] << " <algorithm> <args...>" << std::endl;
  exit(1);
}

static
alphabet_t
alphabet()
{
  alphabet_t	a;
  a.insert('a');
  a.insert('b');
  return a;
}

static
rat_exp_t
get_exp(std::string s)
{
  return new_rat_exp(alphabet(), s);
}

static
automaton_t
get_aut(std::string s)
{
  std::istream* is (s == "-" ? &std::cin : new std::ifstream (s.c_str()));
  if (not is->fail())
    {
      using namespace vcsn::io;
      using namespace vcsn::xml;

      automaton_t a = new_automaton(alphabet());
      *is >> automaton_loader(a, string_out (), XML ());

      if (s != "-")
	delete is;
      return a;
    }
  else
    {
      std::cerr << "FATAL: Could not load automaton." << std::endl;
      exit(1);
    }
}

static
void
derivatives_automaton_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  rat_exp_t	e = get_exp(argv[2]);
  automaton_t	a = new_automaton(alphabet());
  derivatives_automaton(a, e);
  std::cout << automaton_saver(a, string_out (), XML ());
}

static
void
aut_to_exp_command(int argc, char** argv)
{
  if (argc < 3)
    usage(argc, argv);
  else if (argc == 3)
    std::cout << aut_to_exp(get_aut(argv[2])) << std::endl;
  else
    {
      automaton_t		a = get_aut(argv[2]);
      if (a.states().size() != unsigned (argc - 3))
	{
	  std::cerr << "ERROR: Invalid state list." << std::endl;
	  exit(2);
	}

      std::list<hstate_t>	l;
      for (int i = 3; i < argc; ++i)
	{
	  std::istringstream	is (argv[i]);
	  int			s;

	  is >> s;
	  if (s < 0 or unsigned (s) >= a.states().size())
	    {
	      std::cerr << "ERROR: " << s << " is not a valid state."
			<< std::endl;
	      exit(2);
	    }
	  l.push_back(s);
	}

      std::cout << aut_to_exp(a, ListChooser (l)) << std::endl;
    }
}

static
void
product_command(int argc, char** argv)
{
  if (argc != 4)
    usage(argc, argv);

  std::cout << automaton_saver(product(get_aut(argv[2]), get_aut(argv[3])),
			       string_out (),
			       XML ());
}

void
eval_command(int argc, char** argv)
{
  if (argc != 4)
    usage(argc, argv);

  std::cout << eval(get_aut(argv[2]), std::string (argv[3])) << std::endl;
}

static
void
display_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  vcsn::tools::dot_display(get_aut(argv[2]), "A", true);
}

#define ONE_ARG_COMMAND(GetArg, Algo) one_arg_command_ ## Algo ## _ ## GetArg

#define DEFINE_ONE_ARG_COMMAND(GetArg, Algo)		\
static							\
void							\
ONE_ARG_COMMAND(GetArg, Algo)(int argc, char** argv)	\
{							\
  if (argc != 3)					\
    usage(argc, argv);					\
  std::cout << automaton_saver(Algo(GetArg(argv[2])),	\
			       string_out (),		\
			       XML ());			\
}

DEFINE_ONE_ARG_COMMAND(get_exp, standard_of)
DEFINE_ONE_ARG_COMMAND(get_exp, thompson_of)
DEFINE_ONE_ARG_COMMAND(get_aut, quotient)
DEFINE_ONE_ARG_COMMAND(get_aut, closure)
DEFINE_ONE_ARG_COMMAND(get_aut, determinize)
DEFINE_ONE_ARG_COMMAND(get_aut, trim)
DEFINE_ONE_ARG_COMMAND(get_aut, transpose)

#undef DEFINE_ONE_ARG_COMMAND

const struct
{
  char*	name;
  void	(*command)(int, char**);
}
command_map[] =
  {
    { "standard_of",		ONE_ARG_COMMAND(get_exp, standard_of)	},
    { "thompson_of",		ONE_ARG_COMMAND(get_exp, thompson_of)	},
    { "derivatives_automaton",	derivatives_automaton_command		},
    { "aut_to_exp",		aut_to_exp_command			},
    { "quotient",		ONE_ARG_COMMAND(get_aut, quotient)	},
    { "product",		product_command				},
    { "closure",		ONE_ARG_COMMAND(get_aut, closure)	},
    { "determinize",		ONE_ARG_COMMAND(get_aut, determinize)	},
    { "trim",			ONE_ARG_COMMAND(get_aut, trim)		},
    { "transpose",		ONE_ARG_COMMAND(get_aut, transpose)	},
    { "eval",			eval_command				},
    { "display",		display_command				},
    { 0,			0					}
  };

#undef ONE_ARG_COMMAND

int
main(int argc, char** argv)
{
  if (argc < 2)
    usage(argc, argv);

  std::string cmd (argv[1]);
  int i;

  for (i = 0; command_map[i].name != 0; ++i)
    if (cmd == command_map[i].name)
      {
	command_map[i].command(argc, argv);
	break ;
      }
  if (command_map[i].name == 0)
    usage(argc, argv);
}
