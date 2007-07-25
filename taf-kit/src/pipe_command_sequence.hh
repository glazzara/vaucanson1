// pipe_command_sequence.hh: this file is part of the Vaucanson project.
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

#ifndef PIPE_COMMAND_SEQUENCE_HH
# define PIPE_COMMAND_SEQUENCE_HH

/**
 * @file pipe_command_sequence.hh
 *
 * This file contains class declarations that allow sequences of commands.
 */

# include "common.hh"

# include CONTEXT_HEADER
# include <vaucanson/tools/io.hh>

# include <boost/variant.hpp>

using namespace CONTEXT_NAMESPACE;
using namespace vcsn;
using namespace vcsn::io;

struct pipe_command
{
  pipe_command (char*  argv[],
		int    start,
		int    end);		
  arguments_t args;
  int	      length;
  int	      status;
  char**      arg;
};

# include "pipe_command_sequence.hxx"

#endif /* !PIPE_COMMAND_SEQUENCE_HH */
