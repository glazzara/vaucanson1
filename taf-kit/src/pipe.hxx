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

command_output::command_output ()
  : name        (""),
    empty       (true),
    input_aut_type  (INPUT_TYPE_XML),
    input_exp_type  (INPUT_TYPE_EXP),
    output_aut_type (OUTPUT_TYPE_XML),
    output_exp_type (OUTPUT_TYPE_EXP)
{
}

void command_output::clear ()
{
  empty = true;
}

void command_output::input ()
{
  output = PIPE_GET_FROM_STDIN;
  empty = false;
}

void command_output::set_state (command_output_status s)
{
  output = s;
  empty = false;
}

void command_output::set_name (const std::string& str)
{
  name = str;
}

void command_output::set_name (const char*& str)
{
  name = std::string (str);
}


void command_output::init ()
{
  stream.str ("");
}

void command_output::finalize ()
{
  output = stream.str ();
  empty = false;
  stream.str ("");
}

template<typename Content>
void command_output::keep (const Content& content)
{
  output = content;
  empty = false;
}

#endif /* !PIPE_HXX */
