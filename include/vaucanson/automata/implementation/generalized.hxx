// generalized.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_GENERALIZED_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_GENERALIZED_HXX

# include <vaucanson/automata/implementation/generalized.hh>

namespace vcsn {

  template <class Auto_>
  typename generalized_traits<Auto_>::automaton_t
  generalized(const Auto_& from)
  {
    typename generalized_traits<Auto_>::automaton_t to(from.structure());
    auto_copy(to, from);
    return to;
  }
  

} // vcsn

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_GENERALIZED_HXX
