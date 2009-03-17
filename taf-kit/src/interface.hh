// interface.hh: this file is part of Vaucanson.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2009 The Vaucanson Group.
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
#ifndef INTERFACE_HH
# define INTERFACE_HH

/**
 * @file interface.hh
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * Interface for TAF-Kit.
 */

# include "common.hh"

int execute_command(const arguments_t&);
void list_commands(bool all = false);

#endif /* !INTERFACE_HH */
