// edit_automaton.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006 The Vaucanson Group.
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

#ifndef EDIT_AUTOMATON_HH
# define EDIT_AUTOMATON_HH

/**
 * @file edit_automaton.hh
 * @author Micha�l Cadilhac <michael.cadilhac@lrde.org>
 *
 * This file contains the declarations of @c edit_automaton_automaton
 * and @c define_automaton_command .
 */

# include "common.hh"

static int edit_automaton_command (const arguments_t& args);
static int define_automaton_command (const arguments_t& args);

# include "edit_automaton.hxx"

#endif /* !EDIT_AUTOMATON_HH */
