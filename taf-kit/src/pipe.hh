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
using namespace vcsn::io;

typedef boost::variant<int,
		       automaton_t,
# ifndef WITH_TWO_ALPHABETS
		       rat_exp_t,
# endif // !WITH_TWO_ALPHABETS
# ifdef WITH_TWO_ALPHABETS
		       boolean_automaton::automaton_t,
		       boolean_transducer::automaton_t,
# endif // !WITH_TWO_ALPHABETS
		       std::string> command_output_variant;

# define PIPE_GET_FROM_STDIN 42
# define PIPE_BENCH 21

class command_output
{
public:
  void input ();
  void clear ();

  void set_state (int);
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
};

#endif /* !PIPE_HH */
