// translate.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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
#ifndef AUTOMATA_CONCEPT_TRANSLATE_HH
# define AUTOMATA_CONCEPT_TRANSLATE_HH

# include <vaucanson/automata/concept/handlers.hh>
# include <map>

namespace vcsn
{

  template <typename lhs_t, typename rhs_t, typename F>
  void auto_translate_edges(lhs_t&          dst,
			    const rhs_t&    from,
			    const F&        translate_fun);

  template <typename auto_t, typename F>
  auto_t auto_translate_edges(const auto_t& from, 
			      const F&      translate_fun);

}

# include <vaucanson/automata/concept/translate.hxx>

#endif // AUTOMATA_CONCEPT_TRANSLATE_HH
