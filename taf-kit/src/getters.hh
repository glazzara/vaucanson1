// getters.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008 The Vaucanson Group.
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
 * @author Michaël Cadilhac <michael.cadilhac@lrde.org>
 *
 * This file contains the declaration of the getters.
 */

# include "common.hh"

# include CONTEXT_HEADER
# ifdef WITH_TWO_ALPHABETS
#  include <vaucanson/xml/contexts/fmp.hh>
# endif
# include <vaucanson/xml/XML.hh>
# include <vaucanson/tools/io.hh>
# include <string>

# include "pipe.hh"

using namespace CONTEXT_NAMESPACE;
using namespace vcsn;

# ifndef WITH_TWO_ALPHABETS
static alphabet_t get_alphabet (const std::vector<std::string>&);
# else
static first_alphabet_t get_first_alphabet (const std::vector<std::string>&);
static second_alphabet_t get_second_alphabet (const std::vector<std::string>&);
# endif // !WITH_TWO_ALPHABETS

# ifndef WITH_TWO_ALPHABETS
static rat_exp_t get_exp_complete (const std::string& exp,
				   const std::vector<std::string>& alphabet,
				   const vcsn::algebra::token_representation_t& tok_rep);

#  define get_exp(S) (get_exp_complete ((S), args.alphabet, args.tok_rep))

template <class S, class T>
static std::basic_string<letter_t>
get_word(Element<S, T>& aut, const std::string& s);
# endif // !WITH_TWO_ALPHABETS

static automaton_t get_aut (const std::string& s);

# include "getters.hxx"

#endif /* !GETTERS_HH */
