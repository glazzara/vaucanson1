// slots.hxx: this file is part of the Vaucanson project.
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
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_DESIGN_PATTERN_SLOTS_HXX
# define VCSN_DESIGN_PATTERN_SLOTS_HXX

# include <vaucanson/design_pattern/slots.hh>
# include <cstdlib>
# include <vaucanson/misc/unique.hh>
# include <vaucanson/misc/contract.hh>

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
  const S& SetSlotAttribute<S, dynamic>::_structure_get() const
  {
    return *static_cast<const S*>(NULL);
  }

  template<typename S, bool dynamic /* default: false */>
  void SetSlotAttribute<S, dynamic>::_structure_assign(const SetSlotAttribute&)
  {}

  template<typename S, bool dynamic /* default: false */>
  void SetSlotAttribute<S, dynamic>::_structure_attach(const S& )
  {}

  template<typename S, bool dynamic /* default: false */>
  bool SetSlotAttribute<S, dynamic>::_structure_bound() const
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
  const S& SetSlotAttribute<S, true>::_structure_get() const
  {
    return *s_;
  }

  template <class S>
  void SetSlotAttribute<S, true>::_structure_assign(const SetSlotAttribute& other)
  {
    s_ = other.s_;
  }

  template <class S>
  void SetSlotAttribute<S, true>::_structure_attach(const S& s)
  {
    precondition(&s != NULL);
    s_ = & utility::unique::get(s);
  }

  template <class S>
  bool SetSlotAttribute<S, true>::_structure_bound() const
  {
    return s_;
  }

  /*---------------------.
  | SetSlot constructors |
  `---------------------*/


  template <class S, class Tag>
  SetSlot<S,Tag>::SetSlot()
    : SetSlotAttribute<S, dynamic_traits<S>::ret>()
  {}

  template <class S, class Tag>
  SetSlot<S,Tag>::SetSlot(const SetSlot& other)
    : SetSlotAttribute<S, dynamic_traits<S>::ret>(other)
  {}

  template <class S, class Tag>
  SetSlot<S,Tag>::SetSlot(const S& other)
    : SetSlotAttribute<S, dynamic_traits<S>::ret>(other)
  {}


} // vcsn

#endif // ! VCSN_DESIGN_PATTERN_SLOTS_HXX
