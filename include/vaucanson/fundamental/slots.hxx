// fundamental/slots.hxx
//
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

#ifndef VCSN_FUNDAMENTAL_SLOTS_HXX
# define VCSN_FUNDAMENTAL_SLOTS_HXX

# include <vaucanson/fundamental/slots.hh>
# include <cstdlib>
# include <vaucanson/misc/unique.hh>

namespace vcsn {

  /*------------------------------------------.
  | SetSlotAttribute constructors and methods |
  `------------------------------------------*/

  template<typename S, bool dynamic /* default: false */>
  SetSlotAttribute<S, dynamic>::SetSlotAttribute() 
  {}

  template<typename S, bool dynamic /* default: false */>  
  SetSlotAttribute<S, dynamic>::SetSlotAttribute(const SetSlotAttribute&) 
  {}

  template<typename S, bool dynamic /* default: false */>  
  SetSlotAttribute<S, dynamic>::SetSlotAttribute(const S&) 
  {}

  template<typename S, bool dynamic /* default: false */>   
  const S& SetSlotAttribute<S, dynamic>::get() const
  {	
    return *static_cast<const S*>(NULL); 
  }

  template<typename S, bool dynamic /* default: false */>    
  void SetSlotAttribute<S, dynamic>::assign(const SetSlotAttribute&)
  {}

  template<typename S, bool dynamic /* default: false */>
  void SetSlotAttribute<S, dynamic>::attach(const S& )
  {}

  template<typename S, bool dynamic /* default: false */>
  bool SetSlotAttribute<S, dynamic>::bound() const
  { 
    return true; 
  }

  /*--------------------------------------------------.
  | Specialization when structural element is dynamic |
  `--------------------------------------------------*/

  template <class S>
  SetSlotAttribute<S, true>::SetSlotAttribute() 
    : s_(NULL) 
  {}

  template <class S>  
  SetSlotAttribute<S, true>::SetSlotAttribute(const SetSlotAttribute& other) 
    : s_(other.s_)
  {}

  template <class S>  
  SetSlotAttribute<S, true>::SetSlotAttribute(const S& other) 
    : s_(& other ? & utility::unique::get(other) : NULL)
  {}

  template <class S> 
  const S& SetSlotAttribute<S, true>::get() const
  { 
    return *s_; 
  }

  template <class S>
  void SetSlotAttribute<S, true>::assign(const SetSlotAttribute& other)
  { 
    s_ = other.s_; 
  }

  template <class S>
  void SetSlotAttribute<S, true>::attach(const S& s)
  { 
    assert(&s != NULL);
    s_ = & utility::unique::get(s); 
  }

  template <class S>
  bool SetSlotAttribute<S, true>::bound() const
  { 
    return s_; 
  }

  /*---------------------.
  | SetSlot constructors |
  `---------------------*/


  template <class S>
  SetSlot<S>::SetSlot()
    : SetSlotAttribute<S, dynamic_traits<S>::ret>()
  {}
  
  template <class S>
  SetSlot<S>::SetSlot(const SetSlot& other)
    : SetSlotAttribute<S, dynamic_traits<S>::ret>(other)
  {}

  template <class S>
  SetSlot<S>::SetSlot(const S& other)
    : SetSlotAttribute<S, dynamic_traits<S>::ret>(other)
  {}


} // vcsn

#endif // VCSN_FUNDAMENTAL_SLOTS_HXX
