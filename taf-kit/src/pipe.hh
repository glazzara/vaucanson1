// pipe.hh: this file is part of the Vaucanson project.
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

#ifndef PIPE_HH
# define PIPE_HH

/**
 * @file pipe.hh
 *
 * This file contains class declarations that allow sequences of
 * commands.
 *
 * In taf-kit binaries, commands can sequenced using "\|".
 * Command-line options are specific to their command except
 * Timer & Bencher manipulation options (--report-time, --bench,
 * --export-time-dot, --export-time-xml), which are global to
 * the whole sequence.
 * i.e.: --bench will benchmark the whole sequence.
 *
 * When possible, the internal representation of the object being
 * manipulated (e.g. automaton or rational expression) is kept
 * between commands.
 */

# include "common.hh"

# include CONTEXT_HEADER
# include <vaucanson/tools/io.hh>

# include <boost/variant.hpp>

# ifdef WITH_TWO_ALPHABETS
// For boolean_transducer namespace.
// Make sure this is not supposed to be included from somewhere else
// (e.g. CONTEXT_HEADER).
#  include <vaucanson/boolean_transducer.hh>
# endif // !WITH_TWO_ALPHABETS

using namespace CONTEXT_NAMESPACE;
using namespace vcsn;
using namespace vcsn::tools;

enum command_output_status
{
  PIPE_GET_FROM_STDIN,
  PIPE_BENCH
};

typedef boost::variant<command_output_status,
		       automaton_t,
# ifndef WITH_TWO_ALPHABETS
		       rat_exp_t,
# endif // !WITH_TWO_ALPHABETS
# ifdef WITH_TWO_ALPHABETS
		       boolean_automaton::automaton_t,
		       boolean_transducer::automaton_t,
# endif // !WITH_TWO_ALPHABETS
		       std::string> command_output_variant;

// i/o types for automaton_loader and automaton_saver.
enum input_format_t
{
  INPUT_TYPE_FSM,
  INPUT_TYPE_XML
};

enum output_format_t
{
  OUTPUT_TYPE_FSM,
  OUTPUT_TYPE_XML,
  OUTPUT_TYPE_DOT
};

class command_output
{
public:
  command_output ();

  void input ();
  void clear ();

  void set_state (command_output_status);
  void set_name  (std::string&);
  void set_name  (char*&);

  void init ();

  void finalize ();

  template<typename Content>
  void keep (const Content& content);

  std::ostringstream     stream;
  command_output_variant output;
  int                    status;
  std::string		 name;
  bool			 empty;
  input_format_t	 input_type;
  output_format_t	 output_type;
};

#endif /* !PIPE_HH */