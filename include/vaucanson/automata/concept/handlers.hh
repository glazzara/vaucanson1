// handlers.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_AUTOMATA_CONCEPT_HANDLERS_HH
# define VCSN_AUTOMATA_CONCEPT_HANDLERS_HH

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

    handler(int h);

    handler(const handler& h);
    
    handler& operator=(const handler& h);

    handler& operator=(int h);
    
    int value() const;

    operator int () const;

  protected:
    int v_;
  };

  typedef handler<state_h> hstate_t;
  typedef handler<edge_h> hedge_t;

  template<typename kind>					
  bool operator==(const handler<kind>& h1, 
		  const handler<kind>& h2);      

  template<typename kind>					
  bool operator!=(const handler<kind>& h1, 
		  const handler<kind>& h2);      

  template<typename kind>					
  bool operator<(const handler<kind>& h1, 
		 const handler<kind>& h2);      

  template<typename kind>					
  bool operator>(const handler<kind>& h1, 
		 const handler<kind>& h2);      

  template<typename kind>					
  bool operator<=(const handler<kind>& h1, 
		  const handler<kind>& h2);      

  template<typename kind>					
  bool operator>=(const handler<kind>& h1, 
		  const handler<kind>& h2);      

} // vcsn

namespace std {

  template <typename kind>
  std::ostream&	
  operator<<(std::ostream& out, const vcsn::handler<kind>& h);

} // std


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/automata/concept/handlers.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_AUTOMATA_CONCEPT_HANDLERS_HH
