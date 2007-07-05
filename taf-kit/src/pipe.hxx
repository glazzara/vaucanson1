// pipe.hxx: this file is part of the Vaucanson project.
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

#ifndef PIPE_HXX
# define PIPE_HXX

/**
 * @file pipe.hxx
 *
 * This file contains implementation for pipe.hh.
 */

void command_output::input ()
{
  output = int (PIPE_GET_FROM_STDIN);
}

void command_output::set_state (int s)
{
  output = s;
}

void command_output::init ()
{
  stream.str ("");
}

void command_output::finalize ()
{
  output = stream.str ();
  stream.str ("");
}

template<typename Content>
void command_output::keep (const Content& content)
{
  output = content;
}

#endif /* !PIPE_HXX */
