// handlers.hh
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
#ifndef AUTOMATA_CONCEPT_HANDLERS_HH
# define AUTOMATA_CONCEPT_HANDLERS_HH

# include <iostream>

namespace vcsn {

  struct state_h 
  {};

  struct edge_h 
  {};

  template<typename Tag>
  class handler
  {
  public:
    typedef Tag kind;
    
    handler();

    handler(unsigned h);

    handler(const handler& h);
    
    handler& operator=(const handler& h);

    handler& operator=(unsigned h);
    
    unsigned value() const;

    operator unsigned int () const;

  protected:
    unsigned v_;
  };

  typedef handler<state_h> hstate_t;
  typedef handler<edge_h> hedge_t;

} // vcsn

template<typename kind>					
bool operator==(const vcsn::handler<kind>& h1, 
		const vcsn::handler<kind>& h2);      

template<typename kind>					
bool operator!=(const vcsn::handler<kind>& h1, 
		const vcsn::handler<kind>& h2);      

template<typename kind>					
bool operator<(const vcsn::handler<kind>& h1, 
		const vcsn::handler<kind>& h2);      

template<typename kind>					
bool operator>(const vcsn::handler<kind>& h1, 
		const vcsn::handler<kind>& h2);      

template<typename kind>					
bool operator<=(const vcsn::handler<kind>& h1, 
		const vcsn::handler<kind>& h2);      

template<typename kind>					
bool operator>=(const vcsn::handler<kind>& h1, 
		const vcsn::handler<kind>& h2);      

namespace std {

  template <typename kind>
  std::ostream&	
  operator<<(std::ostream& out, const vcsn::handler<kind>& h);

} // std

# include <vaucanson/automata/concept/handlers.hxx>

#endif // AUTOMATA_CONCEPT_HANDLERS_HH
