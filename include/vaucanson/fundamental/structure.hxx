// structure.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_FUNDAMENTAL_STRUCTURE_HXX
# define VCSN_FUNDAMENTAL_STRUCTURE_HXX

# include <vaucanson/fundamental/structure.hh>

namespace vcsn {
    
  /*-----------------------------------.
  | Delegations for Structure::contain |
  `-----------------------------------*/

  template <typename S>
  template <typename T>
  bool 
  Structure<S>::contains(const Element<S, T>& elt) const
  { 
    return op_contains(self(), elt.value()); 
  }

  template <typename S>
  template <typename T>
  bool 
  Structure<S>::contains(const T& elt_value) const
  { 
    return op_contains(self(), elt_value); 
  }
    
  template <typename S>
  template <typename OtherS, typename T>
  bool 
  Structure<S>::contains(const Element<OtherS, T>& other) const
  { 
    return false; 
  }

  /*---------------------------------.
  | Delegation for Structure::choose |
  `---------------------------------*/

  template <class S>
  template <class T>
  Element<S, T>
  Structure<S>::choose(SELECTOR(T)) const
  {
    return op_choose(self(), SELECT(T));
  }
    
  /*-------------------------.
  | Static inheritance stuff |
  `-------------------------*/

  template <typename S>
  S&        
  Structure<S>::self()
  { 
    return static_cast<self_t&>(*this); 
  }
    
  template <typename S>
  const S&  
  Structure<S>::self() const 
  { 
    return static_cast<const self_t&>(*this); 
  }
    

  /*-----------------------.
  | Protected constructors |
  `-----------------------*/

  template <typename S>
  Structure<S>::Structure()
    : utility::unique::unifiable()
  {}

  template <typename S>
  Structure<S>::Structure(const Structure& other)
    : utility::unique::unifiable(other)
  {}


  /*--------------------.
  | Default Comparison  |
  `--------------------*/
  template<typename S>
  bool operator==(const vcsn::Structure<S>& ,
		  const vcsn::Structure<S>& )
  { 
    return true; 
  }

  template<typename S>
  bool operator!=(const vcsn::Structure<S>& a,
		  const vcsn::Structure<S>& b)
  { return !(a == b); }

} // vcsn

#endif // VCSN_FUNDAMENTAL_STRUCTURE_HXX
