// pipe_command_sequence.hxx: this file is part of the Vaucanson project.
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

#ifndef PIPE_COMMAND_SEQUENCE_HXX
# define PIPE_COMMAND_SEQUENCE_HXX

/**
 * @file pipe_command_sequence.hxx
 *
 * This file contains class declarations that allow sequences of commands.
 */

pipe_command::pipe_command (char*  argv[],
			    int    start,
			    int    end)
  : args   (argv[0]),
    length (end - start),
    status (0),
    arg    (& (argv[start]))
{
}


#endif /* !PIPE_COMMAND_SEQUENCE_HXX */
