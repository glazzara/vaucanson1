// structure.hh
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

#ifndef FUNDAMENTAL_STRUCTURE_HH
# define FUNDAMENTAL_STRUCTURE_HH

# include <vaucanson/misc/selectors.hh>
# include <vaucanson/fundamental/predefs.hh>
# include <vaucanson/fundamental/element.hh>
# include <vaucanson/internal/traits.hh>

namespace vcsn {

    /*----------------.
    | Structure<Self> |
    `----------------*/

    template<typename Self>
    struct Structure
    {
      typedef Self		self_t;

      template<typename T>
      bool 
      contains(const Element<Self, T>& elt) const;

      template<typename S, typename T>
      bool 
      contains(const Element<S, T>& other) const;

      template<typename T>
      bool 
      contains(const T& elt_value) const;

      template <class T>
      Element<Self, T> choose(SELECTOR(T)) const;

      // static inheritance stuff below
      self_t&        
      self();

      const self_t&  
      self() const;

    protected:
      Structure();
      Structure(const Structure& other);
    };

} // vcsn

/*--------------------.
| default comparisons |
`--------------------*/
template<typename S>
bool operator==(const vcsn::Structure<S>& a,
		const vcsn::Structure<S>& b);

template<typename S>
bool operator!=(const vcsn::Structure<S>& a,
		const vcsn::Structure<S>& b);

# include <vaucanson/fundamental/structure.hxx>

#endif // FUNDAMENTAL_STRUCTURE_HH
