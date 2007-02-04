// structure.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_DESIGN_PATTERN_STRUCTURE_HXX
# define VCSN_DESIGN_PATTERN_STRUCTURE_HXX

# include <vaucanson/design_pattern/structure.hh>

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
    : misc::unique::unifiable()
  {}

  template <typename S>
  Structure<S>::Structure(const Structure& other)
    : misc::unique::unifiable(other)
  {}


  /*--------------------.
  | Default Comparison  |
  `--------------------*/

  template<typename S>
  bool operator != (const vcsn::Structure<S>& a,
		    const vcsn::Structure<S>& b)
  { return not (a.self() == b.self()); }

} // vcsn

#endif // ! VCSN_DESIGN_PATTERN_STRUCTURE_HXX
