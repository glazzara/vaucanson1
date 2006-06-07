// getters.hh: this file is part of the Vaucanson project.
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


#ifndef GETTERS_HH
# define GETTERS_HH

/**
 * @file getters.hh
 * @author Micha�l Cadilhac <michael.cadilhac@lrde.org>
 *
 * This file contains the declaration of the getters.
 */

# include "common.hh"

# include CONTEXT_HEADER
# include <vaucanson/xml/XML.hh>
# include <string>

using namespace CONTEXT_NAMESPACE;
using namespace vcsn;

static alphabet_t get_alphabet (const char* alphabet);

static rat_exp_t get_exp_complete (const std::string& exp,
				   const char* alphabet,
				   char /* @bug epsilon */);
# define get_exp(S) (get_exp_complete ((S), args.alphabet, args.epsilon))

static automaton_t get_aut (const std::string& s);


# include "getters.hxx"

#endif /* !GETTERS_HH */
