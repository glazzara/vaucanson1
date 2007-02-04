// copy.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_COPY_HH
# define VCSN_AUTOMATA_CONCEPT_COPY_HH

#include <vaucanson/automata/concept/handlers.hh>
#include <map>

namespace vcsn {

  template<typename lhs_t, typename rhs_t>
  void auto_copy(lhs_t& dst_,
		 const rhs_t& from);

  template<typename auto_t>
  auto_t auto_copy(const auto_t& from);

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
# include <vaucanson/automata/concept/copy.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_CONCEPT_COPY_HH
