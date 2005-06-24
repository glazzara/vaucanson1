// tdc_algorithms.cc: this file is part of the Vaucanson project.
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

/**
 * @file tdc_algorithms.cc
 *
 * Run various algorithms on fmp transducers.  Results are dumped
 * in a XML format on stdout.
 *
 * Valid invocations are:
 *
 * closure <file>
 * sub-normalize <file>
 * is-sub-normalized <file>
 * compose <file> <file>
 * evaluation <file> <file>
 * evaluation_aut <file> <file>
 * domain <file>
 * image <file>
 * composition-cover <file>
 * composition-co-cover <file>
 * b-compose <file> <file>
 * to-rt-tdc <file>
 * intersection <file>
 * display <file>
 * trim <file>
 * transpose <file>
 * info <file>
 *
 */

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <list>

#include CONTEXT_HEADER
#include <vaucanson/xml/XML.hh>

#include <vaucanson/algorithms/closure.hh>
#include <vaucanson/algorithms/normalized_composition.hh>
#include <vaucanson/algorithms/sub_normalize.hh>
#include <vaucanson/algorithms/evaluation_fmp.hh>
#include <vaucanson/algorithms/projections_fmp.hh>
#include <vaucanson/algorithms/outsplitting.hh>
#include <vaucanson/algorithms/transpose.hh>
#include <vaucanson/algorithms/fmp_to_realtime.hh>
#include <vaucanson/tools/dot_display.hh>
#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/boolean_transducer.hh>

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
first_alphabet_t
first_alphabet()
{
  first_alphabet_t	a;
  a.insert('a');
  a.insert('b');
  return a;
}

static
second_alphabet_t
second_alphabet()
{
  second_alphabet_t	a;
  a.insert('a');
  a.insert('b');
  return a;
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

      automaton_t a = new_automaton(first_alphabet(), second_alphabet());
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
boolean_automaton::automaton_t
get_boolean_aut(std::string s)
{
  std::istream* is (s == "-" ? &std::cin : new std::ifstream (s.c_str()));
  if (not is->fail())
    {
      using namespace vcsn::io;
      using namespace vcsn::xml;

      boolean_automaton::automaton_t a =
	boolean_automaton::new_automaton(first_alphabet());
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
compose_command(int argc, char** argv)
{
  if (argc != 4)
    usage(argc, argv);

  automaton_t a = get_aut(argv[2]);
  automaton_t b = get_aut(argv[3]);

  if (!is_sub_normalized(a))
    a = sub_normalize(a);

  if (!is_sub_normalized(b))
    b = sub_normalize(b);

  std::cout << automaton_saver(normalized_composition(a,b),
			       string_out (),
			       XML ());
}


static
void
evaluation_command(int argc, char** argv)
{
  if (argc != 4)
    usage(argc, argv);

  std::cout << evaluation(get_aut(argv[2]),
			  boolean_automaton::new_rat_exp(first_alphabet(),
							 argv[3]))
	    << std::endl;
}

static
void
evaluation_aut_command(int argc, char** argv)
{
  if (argc != 4)
    usage(argc, argv);

  boolean_automaton::automaton_t a = get_boolean_aut(argv[3]);
  boolean_automaton::automaton_t res =
    boolean_automaton::new_automaton(second_alphabet());

  evaluation_fmp(get_aut(argv[2]), a, res);

  std::cout << automaton_saver(res, string_out (), XML ());
}

static
void
b_compose_command(int argc, char** argv)
{
  if (argc != 4)
    usage(argc, argv);

  automaton_t a = get_aut(argv[2]);
  automaton_t b = get_aut(argv[3]);

  if (!is_sub_normalized(a))
    a = sub_normalize(a);

  if (!is_sub_normalized(b))
    b = sub_normalize(b);

  std::cout << automaton_saver(b_composition(a,b),
			       string_out (),
			       XML ());
}

static
void
is_subnormalized_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  std::cout << is_sub_normalized(get_aut(argv[2])) << std::endl;
}

static
void
domain_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  boolean_automaton::automaton_t a =
    boolean_automaton::new_automaton(first_alphabet());

  domain(get_aut(argv[2]), a);

  std::cout << automaton_saver(a, string_out (), XML ());
}

static
void
image_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  boolean_automaton::automaton_t a =
    boolean_automaton::new_automaton(second_alphabet());

  image(get_aut(argv[2]), a);

  std::cout << automaton_saver(a, string_out (), XML ());
}


static
void
identity_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  boolean_automaton::automaton_t a = get_boolean_aut(argv[2]);

  automaton_t fmp = new_automaton(first_alphabet(), second_alphabet());

  identity(a, fmp);

  std::cout << automaton_saver(fmp, string_out (), XML ());
}


static
void
fmp_to_realtime_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  boolean_transducer::automaton_t a =
    boolean_transducer::new_automaton(first_alphabet(), second_alphabet());

  fmp_to_realtime(get_aut(argv[2]), a);
  std::cout << automaton_saver(a, string_out (), XML ());
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
closure_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

   std::cout << automaton_saver(accessible(closure(get_aut(argv[2]))),
				string_out (), XML ())
	     << std::endl;
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

DEFINE_ONE_ARG_COMMAND(get_aut, sub_normalize)
DEFINE_ONE_ARG_COMMAND(get_aut, outsplitting)
DEFINE_ONE_ARG_COMMAND(get_aut, insplitting)
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
    { "sub-normalize",		ONE_ARG_COMMAND(get_aut, sub_normalize)	},
    { "is-sub-normalized",	is_subnormalized_command		},
    { "compose",		compose_command				},
    { "evaluation",		evaluation_command			},
    { "evaluation_aut",		evaluation_aut_command			},
    { "domain",			domain_command				},
    { "image",			image_command				},
    { "intersection",		identity_command			},
    { "composition-cover",	ONE_ARG_COMMAND(get_aut, outsplitting)	},
    { "composition-co-cover",	ONE_ARG_COMMAND(get_aut, insplitting)  	},
    { "to-rt-tdc",		fmp_to_realtime_command			},
    { "closure",		closure_command				},
    { "trim",			ONE_ARG_COMMAND(get_aut, trim)		},
    { "b-compose",		b_compose_command			},
    { "transpose",		ONE_ARG_COMMAND(get_aut, transpose)	},
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
      std::cerr << " * sub-normalize"  << std::endl;
      std::cerr << " * is-sub-normalized"  << std::endl;
      std::cerr << " * compose"  << std::endl;
      std::cerr << " * b-compose"  << std::endl;
      std::cerr << " * composition-cover"  << std::endl;
      std::cerr << " * composition-co-cover"  << std::endl;
      std::cerr << " * evaluation"  << std::endl;
      std::cerr << " * evaluation_aut"  << std::endl;
      std::cerr << " * domain"  << std::endl;
      std::cerr << " * image"  << std::endl;
      std::cerr << " * intersection"  << std::endl;
      std::cerr << " * to-rt-tdc"  << std::endl;
      std::cerr << " * closure"  << std::endl;
      std::cerr << " * display"  << std::endl;
      std::cerr << " * trim" << std::endl;
      std::cerr << " * transpose" << std::endl;
      std::cerr << " * info" << std::endl;
      exit(1);
    }
}

