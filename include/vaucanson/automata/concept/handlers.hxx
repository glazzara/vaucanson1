// handlers.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

#ifndef AUTOMATA_HANDLERS_HXX
# define AUTOMATA_HANDLERS_HXX

# include <iostream>

namespace vcsn
{
  
  template<typename Tag>
  handler<Tag>::handler() : v_(0) 
  {}

  template<typename Tag>
  handler<Tag>::handler(unsigned h) : v_(h) 
  {}

  template<typename Tag>
  handler<Tag>::handler(const handler& h) : v_(h.v_) 
  {}
    
  template<typename Tag>
  handler<Tag>& handler<Tag>::operator=(const handler<Tag>& h)
  { 
    v_ = h.v_; 
    return *this; 
  }

  template<typename Tag>
  handler<Tag>& handler<Tag>::operator=(unsigned h)
  { 
    v_ = h; 
    return *this; 
  }
    
  template<typename Tag>
  unsigned handler<Tag>::value() const 
  { 
    return v_; 
  }
    
  template<typename Tag>
  handler<Tag>::operator unsigned int () const 
  { 
    return v_; 
  }


} // vcsn

#define HOPERATOR(Op)								\
template<typename kind>								\
bool operator Op (const vcsn::handler<kind>& h1, const vcsn::handler<kind>& h2)	\
{ return h1.value() Op h2.value(); }

HOPERATOR(==);
HOPERATOR(!=);
HOPERATOR(<);
HOPERATOR(>);
HOPERATOR(<=);
HOPERATOR(>=);

namespace std {

  template <typename kind>
  std::ostream&	
  operator<<(std::ostream& out, const vcsn::handler<kind>& h)
  {
    out << h.value();
    return out;
  }

} // std

#undef HOPERATOR
#endif
