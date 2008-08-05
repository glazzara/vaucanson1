// pipe_writers.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007, 2008 The Vaucanson Group.
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

#ifndef PIPE_WRITERS_HXX
# define PIPE_WRITERS_HXX

/**
 * @file pipe_writers.hxx
 *
 * This file contains boost variant visitors and
 * is to be included within main.cc
 */

# include <vaucanson/tools/fsm_dump.hh>
# include <vaucanson/tools/dot_dump.hh>

# include "pipe_writers.hh"

using namespace CONTEXT_NAMESPACE;
using namespace vcsn;
using namespace vcsn::tools;
using namespace vcsn::tools;

pipe_stream_writer::pipe_stream_writer (std::ostream& os, output_format_t fmt)
  : o (os),
    f (fmt)
{
}

void
pipe_stream_writer::operator() (command_output_status&) const
{
}

void
pipe_stream_writer::operator() (std::string& str) const
{
  o << str;
}

void
pipe_stream_writer::operator() (automaton_t& a) const
{
  switch (f)
    {
    case OUTPUT_TYPE_XML:
      o << automaton_saver (a, string_out (), XML ());
      break;
    case OUTPUT_TYPE_FSM:
      fsm_dump (o, a);
      break;
    case OUTPUT_TYPE_DOT:
      dot_dump (o, a, "");
      break;
    default:
      std::cerr << "Could not save automaton." << std::endl;
    }
}

# ifndef WITH_TWO_ALPHABETS
void
pipe_stream_writer::operator() (rat_exp_t& a) const
{
  o << a << std::endl;
}
# endif // !WITH_TWO_ALPHABETS

# ifdef RW_CONTEXT
void
pipe_stream_writer::operator()
  (RW_CONTEXT::automaton_t& a) const
{
  switch (f)
    {
    case OUTPUT_TYPE_XML:
      o << automaton_saver (a, string_out (), XML ());
      break;
    case OUTPUT_TYPE_FSM:
      fsm_dump (o, a);
      break;
    case OUTPUT_TYPE_DOT:
      dot_dump (o, a, "");
      break;
    default:
      std::cerr << "Could not save automaton." << std::endl;
    }
}
# endif // RW_CONTEXT

# ifdef IOAUT_CONTEXT
void
pipe_stream_writer::operator()
  (IOAUT_CONTEXT::automaton_t& a) const
{
  switch (f)
    {
    case OUTPUT_TYPE_XML:
      o << automaton_saver (a, string_out (), XML ());
      break;
    case OUTPUT_TYPE_FSM:
      fsm_dump (o, a);
      break;
    case OUTPUT_TYPE_DOT:
      dot_dump (o, a, "");
      break;
    default:
      std::cerr << "Could not save automaton." << std::endl;
    }
}
# endif // IOAUT_CONTEXT

template<typename T>
void
pipe_stream_writer::operator() (T&) const
{
  o << "Last command output is not a printable type" << std::endl;
}


#endif /* !PIPE_WRITERS_HXX */
