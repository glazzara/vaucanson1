// main.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007, 2008, 2009 The Vaucanson Group.
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
 *         Jerome Galtier <jerome.galtier@lrde.epita.fr>
 *
 * Main file, common to all TAF-Kit binaries.
 */

// Include common.hh first, because it includes config.h which might
// define macros (such as restrict) that are used in gnulib's
// replacements for standard header files.

#include "common.hh"

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>

#include "argp.h"
#include "progname.h"

#include "predefined_alphabets.hh"

#include "commands.hh"
#include "interface.hh"
#include "parser_options.hh"


/**
 * Base info for the program.
 */
const char* argp_program_version =
"VCSN TAF-Kit (" PACKAGE_STRING ")\n"
"\n"
"Copyright (C) 2006, 2007, 2008 The Vaucanson Group.\n"
"This is free software; see the source for copying conditions.  There is NO\n"
"warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE,\n"
"to the extent permitted by law.";

const char* argp_program_bug_address = "<" PACKAGE_BUGREPORT ">";

/// A global timer.
vcsn::misc::Timer global_timer;

/// A global bencher.
vcsn::misc::Bencher bencher;

// A global command output;
command_output global_result;
#include "pipe_command_sequence.hh"

// Writer for final output
#include "pipe_writers.hh"

/**
 * Documentation of the program, of the arguments we accept and the
 * options we understand.
 */
namespace
{
  const char doc[] = "VCSN TAF-Kit -- a toolkit for working with automata";
  const char args_doc[] = "<command> <args...>";
#ifndef NO_PREDEF_ALPHABETS
  const char* predefined_string = build_predefined_string();
#endif
  const argp_option options[] = {
    {"list-commands",	'l', 0, 0,
     "List the commands handled by the program", 0 },
    { "verbose",		'v', 0, 0,
      "Be more verbose (print boolean results)", 0 },
    { "report-time",	'T', "VERBOSE_DEGREE", OPTION_ARG_OPTIONAL,
      "Report time statistics", 0 },
    { "export-time-dot", 'D', "VERBOSE_DEGREE", OPTION_ARG_OPTIONAL,
      "Export time statistics in DOT format", 0 },
    { "export-time-xml", 'X', 0, 0,
      "Export time statistics in XML format", 0 },
    { "bench",	'B', "NB_ITERATIONS", 0,
      "Bench", 0 },
    { "bench-plot-output", 'O', "OUTPUT_FILENAME", 0,
      "Bench output filename", 0 },

    { "input-type", 'i', "INPUT_TYPE", 0,
      "Automaton input type (FSM or XML)", 0 },
    { "output-type", 'o', "OUTPUT_TYPE", 0,
      "Automaton output type (FSM, XML or DOT)", 0 },

#ifdef WITH_TWO_ALPHABETS
    { "alphabet1",	'a', "ALPHABET", 0,
      "Set the first alphabet for rational expressions or automata", 0 },
    { "alphabet2",	'A', "ALPHABET", 0,
      "Set the second alphabet for rational expressions or automata", 0 },
    { "parser1",	'P', "OPTIONS", 0,
      "Set the first parsing options for rational expressions", 0 },
    { "parser2",	'Q', "OPTIONS", 0,
      "Set the second parsing options for rational expressions", 0 },
#else /* ! WITH_TWO_ALPHABETS */
    { "alphabet",		'a', "ALPHABET", 0,
      "Set the alphabet for rational expressions or automata", 0 },
#endif /* ! WITH_TWO_ALPHABETS */
    { "parser",			'p', "OPTIONS", 0,
      "Set the parsing options for rational expressions", 0 },

#ifndef NO_PREDEF_ALPHABETS
    { 0, 0, 0, 0, predefined_string, 0},
#endif

    { 0, 0, 0, 0, 0, 0 }
  };

  error_t parse_opt (int key, char* arg, argp_state* state)
  {
    arguments_t& args = *(static_cast <arguments_t*> (state->input));

    switch (key)
    {
      case 'a':
#ifndef WITH_TWO_ALPHABETS
	args.add_parser_option("ALPHABET", alphabet_lookup(arg));
	break;
#else
	args.add_parser1_option("ALPHABET", alphabet_lookup(arg));
	break;
      case 'A':
	args.add_parser2_option("ALPHABET", alphabet_lookup(arg));
	break;
#endif
      case 'p':
	args.add_parser_option(NULL, arg);
	break;
#ifdef WITH_TWO_ALPHABETS
      case 'P':
	args.add_parser1_option(NULL, arg);
	break;
      case 'Q':
	args.add_parser2_option(NULL, arg);
	break;
#endif /* ! WITH_TWO_ALPHABETS */
      case 'l':
	list_commands ();
	exit (0);
	break;
      case 'T':
	args.report_time = true;
	args.report_degree = arg ? atoi(arg) : 2;
	break;
      case 'D':
	args.export_time_dot = true;
	args.export_dot_degree = arg ? atoi(arg) : 2;
	break;
      case 'X':
	args.export_time_xml = true;
	break;

      case 'B':
	args.bench = true;
	args.nb_iterations = atoi(arg);
	break;

      case 'O':
	args.plot_output_filename = arg;
	break;

      case 'i':
	if (strcasecmp(arg, "XML") == 0)
	{
	  args.input_aut_type = INPUT_TYPE_XML;
	  args.input_exp_type = INPUT_TYPE_XML;
	}
	else if (strcasecmp(arg, "FSM") == 0)
	{
	  args.input_aut_type = INPUT_TYPE_FSM;
	  args.input_exp_type = INPUT_TYPE_FSM;
	}
	else if (strcasecmp(arg, "EXP") == 0)
	{
	  args.input_aut_type = INPUT_TYPE_EXP;
	  args.input_exp_type = INPUT_TYPE_EXP;
	}
	else
	{
	  std::cerr << "Unknown input type: " << arg << std::endl;
	  return ARGP_ERR_UNKNOWN;
	}
	break;

      case 'o':
	if (strcasecmp(arg, "XML") == 0)
	{
	  args.output_aut_type = OUTPUT_TYPE_XML;
	  args.output_exp_type = OUTPUT_TYPE_XML;
	}
	else if (strcasecmp(arg, "FSM") == 0)
	{
	  args.output_aut_type = OUTPUT_TYPE_FSM;
	  args.output_exp_type = OUTPUT_TYPE_FSM;
	}
	else if (strcasecmp(arg, "DOT") == 0)
	{
	  args.output_aut_type = OUTPUT_TYPE_DOT;
	  args.output_exp_type = OUTPUT_TYPE_DOT;
	}
	else
	{
	  std::cerr << "Unknown output type: " << arg << std::endl;
	  return ARGP_ERR_UNKNOWN;
	}
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
  set_program_name(argv[0]);
  // Simplify the program name, because argp() uses it to report errors.
  argv[0] = const_cast<char*>(program_name);

  std::list<pipe_command> command_list;

  // Cut the command line
  int i = 0;
  int j = 0;
  for (; i < argc; ++i)
    {
      if (strcmp("|", argv[i]) == 0)
	{
	  // Pretend that each pipe is the start of a vcsn-x-x call.
	  // This is because argp() will use that value to report errors
	  // and we do not want errors to be reported by "|".
	  argv[i] = const_cast<char*>(program_name);

	  command_list.push_back (pipe_command (argv, j, i));
	  j = i;
	}
    }
  command_list.push_back (pipe_command (argv, j, i));

  global_result.set_state (PIPE_GET_FROM_STDIN);

  arguments_t args(program_name);

  // Parse each command
  for (std::list<pipe_command>::iterator li = command_list.begin ();
       li != command_list.end (); ++li)
    {
      argp_parse (&argp_setup, li->length, li->arg, 0, 0, &(li->args));

      try
      {
	parser_options<monoid_rep_t, series_rep_t> p_opts(li->args.parser);

	li->args.alphabet = p_opts.get_letters();
	li->args.srep = p_opts.get_srep();
	li->args.mrep = p_opts.get_mrep();
	li->args.cf = p_opts.get_cmd_flags();

#ifdef WITH_TWO_ALPHABETS
	parser_options<first_monoid_rep_t, first_series_rep_t> p_opts1(li->args.parser1);
	parser_options<second_monoid_rep_t, second_series_rep_t> p_opts2(li->args.parser2);

	li->args.alphabet1 = p_opts1.get_letters();
	li->args.alphabet2 = p_opts2.get_letters();
	li->args.srep.first_representation() = p_opts1.get_srep();
	li->args.mrep1 = p_opts1.get_mrep();
	li->args.cf1 = p_opts1.get_cmd_flags();
	li->args.srep.second_representation() = p_opts2.get_srep();
	li->args.mrep2 = p_opts2.get_mrep();
	li->args.cf2 = p_opts2.get_cmd_flags();
#endif
      }
      catch (const std::logic_error& err)
      {
	warn (program_name << ": " << err.what ());
      }

      if (li->args.bench)
	{
	  args.bench = li->args.bench;
	  args.nb_iterations = li->args.nb_iterations;
	}
      if (li->args.report_time)
	{
	  args.report_time = li->args.report_time;
	  args.report_degree = li->args.report_degree;
	}
      if (li->args.export_time_dot)
	{
	  args.export_time_dot = li->args.export_time_dot;
	  args.export_dot_degree = li->args.export_dot_degree;
	}
      args.export_time_xml = args.export_time_xml || li->args.export_time_xml;
      if (!li->args.plot_output_filename.empty ())
	args.plot_output_filename = li->args.plot_output_filename;
    }

  BENCH_DO(args.nb_iterations)
    {
      int task_number = 0;

      TIMER_START ();

      // Execute commands
      for (std::list<pipe_command>::iterator li = command_list.begin ();
	   li != command_list.end (); ++li, ++task_number)
	{
	  arguments_t& args = li->args;

	  int& status = li->status;

	  try
	    {
	      global_result.clear ();
	      global_result.set_name (args.args[0]);
	      global_result.output_aut_type = args.output_aut_type;
	      global_result.output_exp_type = args.output_exp_type;
	      global_result.input_aut_type = args.input_aut_type;
	      global_result.input_exp_type = args.input_exp_type;
	      std::ostringstream os;
	      os << "CMD[" << task_number << "]: ";
	      TIMER_SCOPED(os.str () + std::string (args.args[0]));
	      status = execute_command (args);
	    }
	  catch (const std::logic_error& err) {
	    warn (program_name << ": " << err.what ());
	    status = -1;
	  }

	  global_result.status = status;
	  // Break upon error
	  if (status != 0)
	    break;
	}

      if (!global_result.empty)
	boost::apply_visitor (pipe_stream_writer (std::cout,
						  global_result.output_aut_type,
						  global_result.output_exp_type),
			      global_result.output);

      TIMER_STOP ();

      if (args.report_time)
	TIMER_PRINT_VD(std::cerr,
		       timer::get_verbose_degree (args.report_degree));
      if (args.export_time_dot)
	TIMER_EXPORT_DOT_VD(std::cerr,
			    timer::get_verbose_degree
			(args.export_dot_degree));
      if (args.export_time_xml)
	TIMER_DUMP(std::cerr);

      global_result.set_state (PIPE_BENCH);
    }

  if (args.bench)
    BENCH_PRINT(std::cerr);
  if (!args.plot_output_filename.empty())
    BENCH_SAVE_PLOT(args.plot_output_filename.c_str());

  return global_result.status;
}
