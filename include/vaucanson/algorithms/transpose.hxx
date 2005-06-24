// transpose.hxx: this file is part of the Vaucanson project.
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
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_ALGORITHMS_TRANSPOSE_HXX
# define VCSN_ALGORITHMS_TRANSPOSE_HXX

#include <vaucanson/algorithms/transpose.hh>
#include <vaucanson/automata/implementation/transpose_view.hh>
#include <vaucanson/automata/concept/copy.hh>

namespace vcsn
{
  template<typename lhs_t, typename rhs_t>
  void transpose(lhs_t& dst_,
		      const rhs_t& from)
  {
    auto_copy(dst_, transpose_view(from));
  }

  template<typename auto_t>
  auto_t transpose(const auto_t& from)
  {
    auto_t dst(from.structure());
    transpose(dst, from);
    return dst;
  }

} //vcsn

#endif // ! VCSN_ALGORITHMS_TRANSPOSE_HXX
