// transpose.hh
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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


#ifndef AUTOMATA_TRANSPOSE_HH
#define AUTOMATA_TRANSPOSE_HH

# include <vaucanson/automata/concept/transpose_impl.hh>
# include <vaucanson/automata/concept/copy.hh>

namespace vcsn
{
  template<typename lhs_t, typename rhs_t>
  void auto_transpose(lhs_t& dst_,
		      const rhs_t& from);

  template<typename auto_t>
  auto_t auto_transpose(const auto_t& from);

} //vcsn

# include <vaucanson/algorithms/transpose.hxx>

#endif
