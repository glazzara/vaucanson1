// pipe_writers.hxx: this file is part of the Vaucanson project.
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

#ifndef PIPE_WRITERS_HXX
# define PIPE_WRITERS_HXX

/**
 * @file pipe_writers.hxx
 *
 * This file contains boost variant visitors and
 * is to be included within main.cc
 */

# include "pipe_writers.hh"

using namespace CONTEXT_NAMESPACE;
using namespace vcsn;
using namespace vcsn::io;


pipe_stream_writer::pipe_stream_writer (std::ostream& os)
  : o (os)
{
}

void
pipe_stream_writer::operator() (int&) const
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
  o << automaton_saver (a, string_out (), XML ());
}

# ifndef WITH_TWO_ALPHABETS
void
pipe_stream_writer::operator() (rat_exp_t& a) const
{
  o << a << std::endl;
}
# endif // !WITH_TWO_ALPHABETS

# ifdef WITH_TWO_ALPHABETS
void
pipe_stream_writer::operator()
  (boolean_transducer::automaton_t& a) const
{
  o << automaton_saver (a, string_out (), XML ());
}

void
pipe_stream_writer::operator()
  (boolean_automaton::automaton_t& a) const
{
  o << automaton_saver (a, string_out (), XML ());
}
# endif // !WITH_TWO_ALPHABETS

template<typename T>
void
pipe_stream_writer::operator() (T&) const
{
  o << "Last command output is not a printable type" << std::endl;
}


#endif /* !PIPE_WRITERS_HXX */
