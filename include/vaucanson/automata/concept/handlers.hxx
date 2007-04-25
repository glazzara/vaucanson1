// handlers.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_HANDLERS_HXX
# define VCSN_AUTOMATA_CONCEPT_HANDLERS_HXX

# include <vaucanson/automata/concept/handlers.hh>

namespace vcsn
{

  template<typename Tag, typename Type>
  handler<Tag, Type>::handler() : v_(0)
  {}

  template<typename Tag, typename Type>
  handler<Tag, Type>::handler(Type h) : v_(h)
  {}

  template<typename Tag, typename Type>
  handler<Tag, Type>::handler(const handler& h) : v_(h.v_)
  {}

  template<typename Tag, typename Type>
  handler<Tag, Type>& 
  handler<Tag, Type>::operator=(const handler<Tag, Type>& h)
  {
    v_ = h.v_;
    return *this;
  }

  template<typename Tag, typename Type>
  handler<Tag, Type>& handler<Tag, Type>::operator=(Type h)
  {
    v_ = h;
    return *this;
  }

  template<typename Tag, typename Type>
  Type handler<Tag, Type>::value() const
  {
    return v_;
  }

  template<typename Tag, typename Type>
  handler<Tag, Type>::operator Type () const
  {
    return v_;
  }

} // vcsn

#define HOPERATOR(Op)					\
template<typename Tag, typename Type>			\
bool operator Op (const handler<Tag, Type>& h1,		\
                  const handler<Tag, Type>& h2)		\
{ return h1.value() Op h2.value(); }

namespace vcsn {
HOPERATOR(==);
HOPERATOR(!=);
HOPERATOR(<);
HOPERATOR(>);
HOPERATOR(<=);
HOPERATOR(>=);
}

namespace std {

  template <typename Tag, typename Type>
  std::ostream&
  operator<<(std::ostream& out, const vcsn::handler<Tag, Type>& h)
  {
    out << h.value();
    return out;
  }

} // std

#undef HOPERATOR
#endif // ! VCSN_AUTOMATA_CONCEPT_HANDLERS_HXX
