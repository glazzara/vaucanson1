// transpose.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef ALGEBRA_CONCRETE_SERIES_TRANSPOSE_HXX
# define ALGEBRA_CONCRETE_SERIES_TRANSPOSE_HXX

namespace vcsn {

  namespace algebra {

    template <class S, class T>
    T 
    DefaultTransposeFun<S, T>::operator()(const S&, const T& label) const
    {
      assert(!"Default transposition is not defined.");
    }

  } // algebra

} // vcsn

# include <vaucanson/algebra/concrete/series/transpose.hxx>

#endif // ALGEBRA_SERIES_CONCRETE_TRANSPOSE_HH
