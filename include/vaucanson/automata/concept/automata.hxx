// automata.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey 
// and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_AUTOMATA_CONCEPT_AUTOMATA_HXX
# define VCSN_AUTOMATA_CONCEPT_AUTOMATA_HXX

#include <vaucanson/automata/concept/automata_base.hh>
#include <vaucanson/misc/ref.hh>

namespace vcsn {

  template <class Series>
  Automata<Series>::Automata(const series_t& s):
    series_(s)
  {}

  template <class Series>
  const typename Automata<Series>::series_t&
  Automata<Series>::series() const
  {
    return series_;
  }

} // vcsn

#endif // VCSN_AUTOMATA_CONCEPT_AUTOMATA_HXX
