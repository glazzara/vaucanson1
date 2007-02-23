// main.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007 The Vaucanson Group.
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

/**
 * @file main.cc
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * Main file, common to all TAF-Kit binaries.
 */

#include <stdlib.h>
#include <argp.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "common.hh"
#include "predefined_alphabets.hh"
#include "commands.hh"
#include "interface.hh"

/**
 * Base info for the program.
 */
const char* argp_program_version =
"VCSN TAF-Kit (" PACKAGE_STRING ")\n"
"\n"
"Copyright (C) 2006, 2007 The Vaucanson Group.\n"
"This is free software; see the source for copying conditions.  There is NO\n"
"warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE,\n"
"to the extent permitted by law.";

const char* argp_program_bug_address = "<" PACKAGE_BUGREPORT ">";

/// A global timer.
vcsn::misc::Timer timer;

/// A global bencher.
vcsn::misc::Bencher bencher;

/**
 * Documentation of the program, of the arguments we accept and the
 * options we understand.
 */
namespace
{
  const char doc[] = "VCSN TAF-Kit -- a toolkit for working with automata";
  const char args_doc[] = "<command> <args...>";
  const argp_option options[] = {
    {"list-commands",	'l', 0, 0,
     "List the commands handled by the program", 0 },
    { "verbose",		'v', 0, 0,
      "Be more verbose (print boolean results)", 0 },
    { "report-time",	'T', 0, 0,
      "Report time statistics", 0 },
    { "bench",	'B', "NB_ITERATIONS", 0,
      "Bench", 0 },
    { "bench-plot-output", 'O', "OUTPUT_FILENAME", 0,
      "Bench output filename", 0 },

#ifdef WITH_TWO_ALPHABETS
    { "alphabet1",	'a', "ALPHABET", 0,
      "Set the first alphabet for rational expressions", 0 },
    { "alphabet2",	'A', "ALPHABET", 0,
      "Set the second alphabet for rational expressions", 0 },
#else /* ! WITH_TWO_ALPHABETS */
    { "alphabet",		'a', "ALPHABET", 0,
      "Set the working alphabet for rational expressions", 0 },
#endif /* ! WITH_TWO_ALPHABETS */

#if 0 /* @bug Epsilon is written in hard in VCSN */
    { "epsilon",		'e', "EPSILON", 0,
      "Set the letter which represents the empty word", 0 },
#endif /* 0 */

    { 0, 0, 0, 0, "The following alphabets are predefined:\n"
      "	 `ascii': Use all the ascii table as the alphabet, " DEFAULT_EPSILON " as epsilon\n"
      "	 `a-z': Use [a-z] as the alphabet, " DEFAULT_EPSILON " as epsilon\n"
      "	 `a-zA-Z': Use [a-zA-Z] as the alphabet, " DEFAULT_EPSILON " as epsilon\n"
      "	 `ab': Use `ab' as the alphabet, " DEFAULT_EPSILON " as epsilon", 0 },

    { 0, 0, 0, 0, 0, 0 }
  };

  const struct alphabet
  {
    char*	name;
    char*	alphabet;
    char	epsilon;
  } predefined_alphabets[] = { { "ascii", ALPHABET_ASCII, DEFAULT_EPSILON[0] },
			       { "a-z", ALPHABET_AZ, DEFAULT_EPSILON[0] },
			       { "a-zA-Z", ALPHABET_AZAZ, DEFAULT_EPSILON[0] },
			       { "ab", ALPHABET_AB, DEFAULT_EPSILON[0] },
			       { 0, 0, 0 } };

  error_t parse_opt (int key, char* arg, argp_state* state)
  {
    arguments_t& args = *(static_cast <arguments_t*> (state->input));

    switch (key)
    {
      case 'a':
      case 'A':
	if (key == 'a')
	  args.alphabet = arg;
#ifdef WITH_TWO_ALPHABETS
	else
	  args.alphabet2 = arg;
#endif
	for (const alphabet* alpha = predefined_alphabets; alpha->name; ++alpha)
	  if (std::string (alpha->name) == arg)
	  {
	    if (key == 'a')
	    {
	      args.alphabet = alpha->alphabet;
	      args.epsilon = alpha->epsilon;
	    }
#ifdef WITH_TWO_ALPHABETS
	    else
	    {
	      args.alphabet2 = alpha->alphabet;
	      args.epsilon2 = alpha->epsilon;
	    }
#endif /* ! WITH_TWO_ALPHABETS */
	    break;
	  }
	break;
#if 0 /* @bug Not implemented */
      case 'e':
	if (arg[0] and arg[1])
	  argp_usage (state);
	args.epsilon = arg[0];
	break;
#endif /* 0 */
      case 'l':
	list_commands ();
	exit (0);
	break;
      case 'T':
	args.report_time = true;
	break;

      case 'B':
	args.bench = true;
	args.nb_iterations = atoi(arg);
	break;

      case 'O':
	args.plot_output_filename = arg;
	break;

      case 'v':
	args.verbose = true;
	break;
      case ARGP_KEY_ARG:
	if (state->arg_num < 3)
	  args.args[state->arg_num] = arg;
	++args.n_args;
	break;
      case ARGP_KEY_END:
	if (state->arg_num < 1)
	  argp_usage (state);
	break;
      default:
	return ARGP_ERR_UNKNOWN;
    }
    return 0;
  }

  const argp argp_setup = { options, parse_opt, args_doc, doc, 0, 0, 0 };

} // anonymous namespace

# include <vaucanson/misc/bencher.hh>

using namespace vcsn::misc;

int main (int argc, char* argv[])
{
  arguments_t	args (argv[0]);
  argp_parse (&argp_setup, argc, argv, 0, 0, &args);

  int status = 0;

  BENCH_DO(args.nb_iterations)
  {
    TIMER_START ();
    try {
      status = execute_command (args);
    }
    catch (const std::logic_error& err) {
      warn (argv[0] << ": " << err.what ());
      status = -1;
    }
    TIMER_STOP ();

    if (args.report_time)
      TIMER_PRINT(std::cerr);
  }

  if (args.bench)
    BENCH_PRINT(std::cerr);
  if (!args.plot_output_filename.empty())
    BENCH_SAVE_PLOT(args.plot_output_filename.c_str());
  return status;
}
