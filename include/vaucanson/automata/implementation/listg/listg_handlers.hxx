// listg_handlers.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_LISTG_LISTG_HANDLERS_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_LISTG_LISTG_HANDLERS_HXX

# include <limits.h>
# include <vaucanson/misc/contract.hh>
# include <vaucanson/automata/implementation/listg/listg_handlers.hh>

namespace vcsn
{

  template<typename Tag>
  handler<Tag, unsigned>::handler() : v_(UINT_MAX)
  {}

  template<typename Tag>
  handler<Tag, unsigned>::handler(unsigned h) : v_(h)
  {}

  template<typename Tag>
  handler<Tag, unsigned>::handler(const handler<Tag, unsigned>& h) : v_(h.v_)
  {}

  template<typename Tag>
  handler<Tag, unsigned>&
  handler<Tag, unsigned>::operator=(const handler<Tag, unsigned>& h)
  {
    v_ = h.v_;
    return *this;
  }

  template<typename Tag>
  unsigned handler<Tag, unsigned>::value() const
  {
    return v_;
  }

  template<typename Tag>
  handler<Tag, unsigned>::operator unsigned() const
  {
    return v_;
  }

  template<typename Tag>
  bool
  handler<Tag, unsigned>::is_valid() const
  {
    return v_ != UINT_MAX;
  }

} // vcsn

#endif

