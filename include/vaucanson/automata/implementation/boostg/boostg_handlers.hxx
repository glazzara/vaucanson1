// boostg_handlers.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_HANDLERS_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_BOOSTG_BOOSTG_HANDLERS_HXX

# include <vaucanson/misc/contract.hh>
# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/implementation/boostg/boostg_handlers.hh>

namespace vcsn
{

  inline
  handler<state_h, boost::shared_ptr<std::size_t> >::handler()
  {
    static boost::shared_ptr<std::size_t> uint_max(new std::size_t(UINT_MAX));
    v_ = uint_max;
  }

  inline
  handler<state_h, boost::shared_ptr<std::size_t> >::handler(boost::shared_ptr<std::size_t> h) : v_(h)
  {}

  inline
  handler<state_h, boost::shared_ptr<std::size_t> >::handler(const handler<state_h, boost::shared_ptr<std::size_t> >& h) : v_(h.v_)
  {}

  inline
  handler<state_h, boost::shared_ptr<std::size_t> >&
  handler<state_h, boost::shared_ptr<std::size_t> >::operator=(const handler<state_h, boost::shared_ptr<std::size_t> >& h)
  {
    v_ = h.v_;
    return *this;
  }

  inline
  boost::shared_ptr<std::size_t>
  handler<state_h, boost::shared_ptr<std::size_t> >::value() const
  {
    return v_;
  }

  inline
  handler<state_h, boost::shared_ptr<std::size_t> >::operator unsigned() const
  {
    return *v_;
  }

  inline
  bool
  handler<state_h, boost::shared_ptr<std::size_t> >::is_valid() const
  {
    return *v_ != UINT_MAX;
  }

} // vcsn
#endif

