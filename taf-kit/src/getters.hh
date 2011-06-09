// getters.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008, 2009, 2010, 2011 The Vaucanson Group.
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
# include BOOL_CONTEXT_HEADER
# include <vaucanson/tools/io.hh>
# include <string>

# include "pipe.hh"

using namespace CONTEXT_NAMESPACE;
using namespace vcsn;

# ifndef WITH_TWO_ALPHABETS
alphabet_t get_alphabet (const std::vector<std::string>&);
alphabet_t get_alphabet (const rat_exp_t&);
# else
first_alphabet_t get_first_alphabet (const std::vector<std::string>&);
second_alphabet_t get_second_alphabet (const std::vector<std::string>&);
# endif // !WITH_TWO_ALPHABETS

# ifndef WITH_TWO_ALPHABETS
rat_exp_t get_exp(const arguments_t& args, const int& n);

template <class S, class T>
static std::basic_string<letter_t>
get_word(Element<S, T>& aut, const std::string& s);
# endif // !WITH_TWO_ALPHABETS

bool file_exists(const char* name, bool abort_if_empty = true);
std::string locate_file(const arguments_t& args, const std::string& s,
			bool abort_if_empty = true);
# ifdef WITH_TWO_ALPHABETS
std::string locate_fmp_file(const arguments_t& args, const std::string& s,
			bool abort_if_empty = true);
# endif // !WITH_TWO_ALPHABETS
automaton_t get_aut (const arguments_t& args, int n);

BOOL_CONTEXT::automaton_t get_boolean_aut (const arguments_t& args, int n);
std::string locate_boolean_file(const arguments_t& args, const std::string& s,
				bool abort_if_empty = true);

#ifdef WITH_TWO_ALPHABETS
IOAUT_CONTEXT::automaton_t
get_single_band_aut(const arguments_t& args, int n);
#endif

int write_aut(const automaton_t& aut, const arguments_t& args, int n);
int display_aut(const automaton_t& aut, const arguments_t& args, int n);

unsigned get_unsigned (const arguments_t& args, int n);

semiring_elt_value_t get_weight(const arguments_t& args, int n);

template <typename T>
void set_monoid_writing_data_(T& dst, const T& src, const cmd_flags_t& flags);

template <typename T>
void set_series_writing_data_(T& dst, const T& src, const cmd_flags_t& flags);

void set_writing_data(automaton_t&, const arguments_t&);
void set_boolean_writing_data(BOOL_CONTEXT::automaton_t&, const arguments_t&);
# ifdef WITH_TWO_ALPHABETS
void set_single_band_writing_data(IOAUT_CONTEXT::automaton_t&, const arguments_t&);
#else // !WITH_TWO_ALPHABETS
void set_writing_data(rat_exp_t& e, const arguments_t& args);
# endif // !WITH_TWO_ALPHABETS

# include "getters.hxx"

#endif /* !GETTERS_HH */
