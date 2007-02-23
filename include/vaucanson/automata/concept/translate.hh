// translate.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_CONCEPT_TRANSLATE_HH
# define VCSN_AUTOMATA_CONCEPT_TRANSLATE_HH

# include <vaucanson/automata/concept/handlers.hh>
# include <map>

namespace vcsn
{

  /// @bug Write documentation and tests.
  template <typename lhs_t, typename rhs_t, typename F>
  void auto_translate_transitions(lhs_t&	  dst,
				  const rhs_t&	  from,
				  const F&	  translate_fun);

  template <typename auto_t, typename F>
  auto_t auto_translate_transitions(const auto_t& from,
				    const F&	  translate_fun);

}


#  include <vaucanson/automata/concept/translate.hxx>


#endif // ! VCSN_AUTOMATA_CONCEPT_TRANSLATE_HH
