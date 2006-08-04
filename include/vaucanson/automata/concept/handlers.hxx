// handlers.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2006 The Vaucanson Group.
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

  template<typename Tag>
  handler<Tag>::handler() : v_(0)
  {}

  template<typename Tag>
  handler<Tag>::handler(int h) : v_(h)
  {}

  template<typename Tag>
  handler<Tag>::handler(const handler& h) : v_(h.v_)
  {}

  template<typename Tag>
  handler<Tag>& 
  handler<Tag>::operator=(const handler<Tag>& h)
  {
    v_ = h.v_;
    return *this;
  }

  template<typename Tag>
  handler<Tag>& handler<Tag>::operator=(int h)
  {
    v_ = h;
    return *this;
  }

  template<typename Tag>
  int handler<Tag>::value() const
  {
    return v_;
  }

  template<typename Tag>
  handler<Tag>::operator int () const
  {
    return v_;
  }

} // vcsn

#define HOPERATOR(Op)					\
template<typename kind>					\
bool operator Op (const handler<kind>& h1,	\
                  const handler<kind>& h2)	\
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

  template <typename kind>
  std::ostream&
  operator<<(std::ostream& out, const vcsn::handler<kind>& h)
  {
    out << h.value();
    return out;
  }

} // std

#undef HOPERATOR
#endif // ! VCSN_AUTOMATA_CONCEPT_HANDLERS_HXX
