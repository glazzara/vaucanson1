// pipe_writers.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007, 2008, 2010 The Vaucanson Group.
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

#ifndef PIPE_WRITERS_HH
# define PIPE_WRITERS_HH

/**
 * @file pipe_writers.hh
 *
 * This file contains boost variant visitors and
 * is to be included within main.cc
 */

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

class pipe_stream_writer
  : public boost::static_visitor<>
{
public:
  pipe_stream_writer (std::ostream&, output_format_t, output_format_t);

  void operator() (command_output_status& i) const;

  void operator() (std::string& str) const;

  void operator() (automaton_t& a) const;

  void operator() (rat_exp_t& a) const;

# ifdef IOAUT_CONTEXT
  void operator() (IOAUT_CONTEXT::automaton_t& a) const;
  void operator() (mute_ltl_to_pair<automaton_t::set_t,
		   automaton_t::value_t>::ret& a) const;
# endif
# ifdef RW_CONTEXT
  void operator() (RW_CONTEXT::automaton_t& a) const;
# endif

# ifdef FMP_CONTEXT
  void operator() (FMP_CONTEXT::automaton_t& a) const;
# endif
# ifdef FMPI_CONTEXT
  void operator() (FMPI_CONTEXT::automaton_t& a) const;
# endif

# ifdef FIRST_PROJECTION_CONTEXT
  void operator() (FIRST_PROJECTION_CONTEXT::automaton_t& a) const;
# endif
# ifdef SECOND_PROJECTION_CONTEXT
#  ifndef NO_SECOND_OPERATOR
   void operator() (SECOND_PROJECTION_CONTEXT::automaton_t& a) const;
#  endif
# endif

  template<typename T>
  void operator() (T&) const;

  std::ostream& o;
  output_format_t aut_f;
  output_format_t exp_f;
};

#endif /* !PIPE_WRITERS_HH */
