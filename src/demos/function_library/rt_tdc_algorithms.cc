// rt_tdc_algorithms.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <list>

#include CONTEXT_HEADER
#include <vaucanson/xml/XML.hh>
#include <vaucanson/tools/io.hh>
#include <vaucanson/tools/dot_dump.hh>
#include <vaucanson/tools/dot_display.hh>
#include <vaucanson/tools/xml_dump.hh>
#include <vaucanson/boolean_automaton.hh>
#include <vaucanson/fmp_transducer.hh>

using namespace CONTEXT_NAMESPACE;

using namespace vcsn;
using namespace vcsn::tools;
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
automaton_t
get_aut(std::string s)
{
  std::istream* is (s == "-" ? &std::cin : new std::ifstream (s.c_str()));
  if (not is->fail())
  {
    using namespace vcsn::tools;
    using namespace vcsn::xml;

    automaton_t a = make_automaton(alphabet(), alphabet());
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

boolean_automaton::automaton_t
get_bool_aut(std::string s)
{
  std::istream* is (s == "-" ? &std::cin : new std::ifstream (s.c_str()));
  if (not is->fail())
  {
    using namespace vcsn::tools;
    using namespace vcsn::xml;

    boolean_automaton::automaton_t a =
      boolean_automaton::make_automaton(alphabet());
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
are_isomorphic_command(int argc, char** argv)
{
  if (argc != 4)
    usage(argc, argv);

  std::cout << are_isomorphic(get_aut(argv[2]), get_aut(argv[3])) << std::endl;
}


static
void
compose_command(int argc, char** argv)
{
  if (argc != 4)
    usage(argc, argv);

  automaton_t a = get_aut(argv[2]);
  automaton_t b = get_aut(argv[3]);

  if (!is_realtime(a))
    a = realtime(a);

  if (!is_realtime(b))
    b = realtime(b);

  std::cout << automaton_saver(realtime_composition(a,b),
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
			  boolean_automaton::make_rat_exp(alphabet(),
							  argv[3]))
	    << std::endl;
}


void
is_empty_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  automaton_t a = coaccessible(accessible(get_aut(argv[2])));

  if (a.states().size() > 0)
    std::cout << false << std::endl;
  else
    std::cout << true << std::endl;
}


static
void
evaluation_aut_command(int argc, char** argv)
{
  if (argc != 4)
    usage(argc, argv);

  boolean_automaton::automaton_t a = get_bool_aut(argv[3]);
  boolean_automaton::gen_automaton_t res(a.structure());
  automaton_t t = get_aut(argv[2]);
  evaluation(a, t, res);

  std::cout << automaton_saver(res, string_out (), XML ()) << std::endl;
}



static
void
is_realtime_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  std::cout << is_realtime(get_aut(argv[2])) << std::endl;
}


static
void
realtime_to_fmp_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  fmp_transducer::automaton_t fmp_a =
    fmp_transducer::make_automaton(alphabet(), alphabet());

  realtime_to_fmp(get_aut(argv[2]), fmp_a);

  std::cout << automaton_saver(fmp_a, string_out (), XML ());
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
  std::cout << "Transitions: " << a.transitions().size() << std::endl;
  std::cout << "Initial states: " << a.initial().size() << std::endl;
  std::cout << "Final states: " << a.final().size() << std::endl;
}

static
void
eps_removal_command(int argc, char** argv)
{
  if (argc != 3)
    usage(argc, argv);

  std::cout << automaton_saver(accessible(eps_removal(get_aut(argv[2]))),
			       string_out (), XML ())
	    << std::endl;
}

#define ONE_ARG_COMMAND(GetArg, Algo) one_arg_command_ ## Algo ## _ ## GetArg

#define DEFINE_ONE_ARG_COMMAND(GetArg, Algo)		\
  static						\
  void							\
  ONE_ARG_COMMAND(GetArg, Algo)(int argc, char** argv)	\
  {							\
    if (argc != 3)					\
      usage(argc, argv);				\
    std::cout << automaton_saver(Algo(GetArg(argv[2])),	\
				 string_out (),		\
				 XML ());		\
  }

DEFINE_ONE_ARG_COMMAND(get_aut, realtime)
DEFINE_ONE_ARG_COMMAND(get_aut, input_projection)
DEFINE_ONE_ARG_COMMAND(get_aut, output_projection)
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
  { "realtime",		ONE_ARG_COMMAND(get_aut, realtime)	},
  { "is-realtime",		is_realtime_command			},
  { "compose",		compose_command				},
  { "evaluation",		evaluation_command			},
  { "evaluation_aut",		evaluation_aut_command			},
  { "domain",			ONE_ARG_COMMAND(get_aut, input_projection)},
  { "is-empty",		is_empty_command			},
  { "are-isomorphic",		are_isomorphic_command			},
  { "image",			ONE_ARG_COMMAND(get_aut, output_projection)},
  { "to-tdc",			realtime_to_fmp_command			},
  { "eps_removal",		eps_removal_command				},
  { "trim",			ONE_ARG_COMMAND(get_aut, trim)		},
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
    std::cerr << " * domain"  << std::endl;
    std::cerr << " * image"  << std::endl;
    std::cerr << " * eps_removal"  << std::endl;
    std::cerr << " * trim"  << std::endl;
    std::cerr << " * realtime"	<< std::endl;
    std::cerr << " * are-isomorphic"  << std::endl;
    std::cerr << " * is-realtime"  << std::endl;
    std::cerr << " * transpose"	 << std::endl;
    std::cerr << " * is-empty"	<< std::endl;
    std::cerr << " * to-tdc"  << std::endl;
    std::cerr << " * compose"  << std::endl;
    std::cerr << " * evaluation"  << std::endl;
    std::cerr << " * evaluation_aut"  << std::endl;
    std::cerr << " * display"  << std::endl;
    std::cerr << " * info"  << std::endl;
    exit(1);
  }
}

