// algorithms.cc: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//

/**
 * @file algorithms.cc
 *
 * Run various algorithms on automata.  Results are dumped in a XML
 * format on stdout.
 *
 * Valid invocations are:
 *
 * closure <file>
 * realtime <file>
 * transpose <file>
 * product <file1> <file2>
 * power <file> <n>
 * quotient <file>
 * accessible <file>
 * coaccessible <file>
 * trim <file>
 * concatenate <file1> <file2>
 * sum <file1> <file2>
 * standardize <file>
 * normalize <file>
 * eval <file> <string>
 * aut_to_exp <file> [state ordering for for eliminations]
 * expand <exp>
 * standard_of <exp>
 * thompson_of <exp>
 * derived_terms <exp>
 * determinize <file>
 * minimize <file> [-m for Moore minimization, -h for Hopcroft minimization]
 * display <file>
 * info <file>
 *
 */

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <list>

#include CONTEXT_HEADER
#include <vaucanson/xml/XML.hh>

#include <vaucanson/algorithms/derived_terms_automaton.hh>
#include <vaucanson/algorithms/product.hh>
#include <vaucanson/algorithms/transpose.hh>
#include <vaucanson/algorithms/eval.hh>
#include <vaucanson/algorithms/determinize.hh>
#include <vaucanson/algorithms/closure.hh>
#include <vaucanson/algorithms/minimization_hopcroft.hh>
#include <vaucanson/algorithms/minimization_moore.hh>
#include <vaucanson/algorithms/trim.hh>
#include <vaucanson/algorithms/concatenate.hh>
#include <vaucanson/algorithms/sum.hh>
#include <vaucanson/algorithms/krat_exp_expand.hh>
#include <vaucanson/algorithms/accessible.hh>
#include <vaucanson/algorithms/realtime.hh>
#include <vaucanson/algorithms/standard.hh>
#include <vaucanson/algorithms/normalized.hh>
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
derived_terms_automaton_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  rat_exp_t	e = get_exp(argv[2]);
  automaton_t	a = new_automaton(alphabet());
  derived_terms_automaton(a, e);
  std::cout << automaton_saver(a, string_out (), XML ());
}

static
void
aut_to_exp_command(int argc, char** argv)
{
  if (argc < 3)
    usage(argc, argv);
  else if (argc == 3)
    std::cout << aut_to_exp(get_aut(argv[2]), DMChooser()) << std::endl;
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

  std::cout << eval(realtime(get_aut(argv[2])), std::string (argv[3]));
}

void
power_command(int argc, char** argv)
{
  if (argc != 4)
    usage(argc, argv);

  int n = atoi(argv[3]);

  automaton_t a = get_aut(argv[2]);
  automaton_t p(a);

  for (int i = 1; i <= n; ++i)
    p = product(p, a);

  std::cout << automaton_saver(p, string_out (), XML ());
}

static
void
display_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  vcsn::tools::dot_display(get_aut(argv[2]), "A", true);
}

static
void
info_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  automaton_t a = get_aut(argv[2]);

  std::cout << "States: " << a.states().size() << std::endl;
  std::cout << "Transitions: " << a.edges().size() << std::endl;
  std::cout << "Initial states: " << a.initial().size() << std::endl;
  std::cout << "Final states: " << a.final().size() << std::endl;
}

static
void
expand_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  std::cout << expand(get_exp(argv[2])) << std::endl;
}

static
void
minimize_command(int argc, char** argv)
{
  if (argc < 3)
    usage(argc, argv);
  else if (argc == 3)
    std::cout <<  automaton_saver(minimization_hopcroft(get_aut(argv[2])),
				  string_out (), XML ())
	      << std::endl;
  else
    {
      std::string	arg (argv[3]);
      automaton_t	a = get_aut(argv[2]);

      if (arg == "-m")
	std::cout <<  automaton_saver(minimization_moore(get_aut(argv[2])),
				      string_out (), XML ())
		  << std::endl;

      else if (arg == "-h")
	std::cout <<  automaton_saver(minimization_hopcroft(get_aut(argv[2])),
				      string_out (), XML ())
		  << std::endl;
    }
}

static
void
concatenate_command(int argc, char** argv)
{
  if (argc != 4)
    usage(argc, argv);

  std::cout << automaton_saver(concatenate(get_aut(argv[2]), get_aut(argv[3])),
			       string_out (), XML ())
	    << std::endl;
}

static
void
sum_command(int argc, char** argv)
{
  if (argc != 4)
    usage(argc, argv);

  std::cout << automaton_saver(sum(get_aut(argv[2]), get_aut(argv[3])),
			       string_out (), XML ())
	    << std::endl;
}

static
void
closure_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

   std::cout << automaton_saver(accessible(closure(get_aut(argv[2]))),
				string_out (), XML ())
	     << std::endl;
}

static
void
determinize_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

   std::cout << automaton_saver(determinize(realtime(get_aut(argv[2]))),
				string_out (), XML ())
	     << std::endl;
}

static
void
quotient_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

   std::cout << automaton_saver(quotient(realtime(get_aut(argv[2]))),
				string_out (), XML ())
	     << std::endl;
}

static
void
standardize_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  automaton_t a = get_aut(argv[2]);
  standardize(a);

  std::cout << automaton_saver(a, string_out (), XML ()) << std::endl;
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
DEFINE_ONE_ARG_COMMAND(get_aut, trim)
DEFINE_ONE_ARG_COMMAND(get_aut, transpose)
DEFINE_ONE_ARG_COMMAND(get_aut, realtime)
DEFINE_ONE_ARG_COMMAND(get_aut, coaccessible)
DEFINE_ONE_ARG_COMMAND(get_aut, accessible)
DEFINE_ONE_ARG_COMMAND(get_aut, normalize)

#undef DEFINE_ONE_ARG_COMMAND

const struct
{
  char*	name;
  void	(*command)(int, char**);
}
command_map[] =
  {
    { "expand",			expand_command				},
    { "standard_of",		ONE_ARG_COMMAND(get_exp, standard_of)	},
    { "thompson_of",		ONE_ARG_COMMAND(get_exp, thompson_of)	},
    { "derived_terms",		derived_terms_automaton_command		},
    { "aut_to_exp",		aut_to_exp_command			},
    { "quotient",		quotient_command			},
    { "product",		product_command				},
    { "closure",		closure_command				},
    //    { "is_empty",		ONE_ARG_COMMAND(get_aut, is_void)	},
    { "determinize",		determinize_command			},
    { "minimize",		minimize_command			},
    { "trim",			ONE_ARG_COMMAND(get_aut, trim)		},
    { "transpose",		ONE_ARG_COMMAND(get_aut, transpose)	},
    { "accessible",		ONE_ARG_COMMAND(get_aut, coaccessible)	},
    { "coaccessible",		ONE_ARG_COMMAND(get_aut, accessible)	},
    { "sum",			sum_command				},
    { "concatenate",		concatenate_command			},
    { "realtime",		ONE_ARG_COMMAND(get_aut, realtime)	},
    { "eval",			eval_command				},
    { "power",			power_command				},
    { "normalize",		ONE_ARG_COMMAND(get_aut, normalize)	},
    { "standardize",		standardize_command			},
    { "display",		display_command				},
    { "info",			info_command				},
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
    {
      std::cerr << "Available algorithms:" << std::endl;
      std::cerr << " * standard_of"  << std::endl;
      std::cerr << " * expand"  << std::endl;
      std::cerr << " * thompson_of"  << std::endl;
      std::cerr << " * derived_terms"  << std::endl;
      std::cerr << " * aut_to_exp"  << std::endl;
      std::cerr << " * quotient"  << std::endl;
      std::cerr << " * product"  << std::endl;
      std::cerr << " * determinize"  << std::endl;
      std::cerr << " * minimize"  << std::endl;
      std::cerr << " * closure"  << std::endl;
      std::cerr << " * is_empty"  << std::endl;
      std::cerr << " * accessible"  << std::endl;
      std::cerr << " * coaccessible"  << std::endl;
      std::cerr << " * realtime"  << std::endl;
      std::cerr << " * power"  << std::endl;
      std::cerr << " * trim"  << std::endl;
      std::cerr << " * eval"  << std::endl;
      std::cerr << " * transpose"  << std::endl;
      std::cerr << " * display"  << std::endl;
      std::cerr << " * info"  << std::endl;
      exit(1);
    }
}
