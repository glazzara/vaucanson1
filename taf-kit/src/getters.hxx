// getters.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2008, 2009, 2010 The Vaucanson Group.
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

#ifndef GETTERS_HXX
# define GETTERS_HXX

# include "common.hh"

# include CONTEXT_HEADER
# include <string>
# include <cstdlib>
# include "getters.hh"

using namespace CONTEXT_NAMESPACE;
using namespace vcsn;
using namespace vcsn::tools;


# ifndef WITH_TWO_ALPHABETS

template <class S, class T>
static std::basic_string<letter_t>
get_word(Element<S, T>& aut, const std::string& s)
{
  Element<monoid_t, std::basic_string<letter_t> > w(aut.structure().series().monoid());

  if (!parse_word(w, s).first)
    {
      std::cerr << "FATAL: Cannot parse " << s << std::endl;
      exit(1);
    }
  return w.value();
}

# endif // !WITH_TWO_ALPHABETS

// Set the representations provided on the command line.
# define SET_TOKEN(name) if (flags. name) { dst . name = src . name; }

template <typename T>
void set_monoid_writing_data_(T& dst, const T& src, const cmd_flags_t& flags)
{
  SET_TOKEN(empty)
  SET_TOKEN(concat)
}

template <typename T>
void set_series_writing_data_(T& dst, const T& src, const cmd_flags_t& flags)
{
  SET_TOKEN(open_par)
  SET_TOKEN(close_par)
  SET_TOKEN(plus)
  SET_TOKEN(times)
  SET_TOKEN(star)
  SET_TOKEN(open_weight)
  SET_TOKEN(close_weight)
  SET_TOKEN(spaces)
  SET_TOKEN(zero)
}

# undef SET_TOKEN

#endif // ! GETTERS_HXX
