// automata.hh
//
// $Id$
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

#ifndef AUTOMATA_AUTOMATA_HH
# define AUTOMATA_AUTOMATA_HH

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/ref.hh>

namespace vcsn {

  struct Automata;
  
  template<>
  struct MetaSet<Automata>
  {
    static const bool dynamic_set = false;    
  };
  
  template<typename T>
  struct MetaElement<Automata, T>
    : MetaElement<AutomataBase<Automata>, T>
  { };
  
  template<typename T>
  bool op_contains(const Automata& a, const utility::ref<T>& r);
  
  struct Automata
    : AutomataBase<Automata>
  { };

  template<typename T>
  struct automaton_traits<utility::ref<T> >
   : automaton_traits<T>
  { };
  
}


# include <vaucanson/automata/concept/automata.hxx>
# include <vaucanson/automata/concept/automaton_impl.hh>

#endif

