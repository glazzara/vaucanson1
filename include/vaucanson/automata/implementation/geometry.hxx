// GEOMETRY.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_GEOMETRY_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_GEOMETRY_HXX

namespace vcsn
{
# define GEOMETRY_TPARAM \
  template<typename HState, typename HTransition, typename Coords>

# define GEOMETRY \
  geometry<HState, HTransition, Coords>

  GEOMETRY_TPARAM
  inline
  GEOMETRY::geometry()
    : states_(0), transitions_(0), initials_(0), finals_(0), name_(0)
  {}

  GEOMETRY_TPARAM
  inline
  GEOMETRY& GEOMETRY::operator=(const GEOMETRY& obj)
  {
    return copy_from(obj);
  }

  GEOMETRY_TPARAM
  inline
  GEOMETRY::geometry(const GEOMETRY& obj)
    : states_(0), transitions_(0), initials_(0), finals_(0), name_(0)
  {
    copy_from(obj);
  }

  GEOMETRY_TPARAM
  inline
  GEOMETRY& GEOMETRY::copy_from(const GEOMETRY& obj)
  {
    if (obj.states_ != 0)
    {
      delete states_;
      states_ = new states_geometry_map_t(obj.states());
    }
    if (obj.transitions_ != 0)
    {
      delete transitions_;
      transitions_ = new transitions_geometry_map_t(obj.transitions());
    }
    if (obj.initials_ != 0)
    {
      delete initials_;
      initials_ = new initials_geometry_map_t(obj.initials());
    }
    if (obj.finals_ != 0)
    {
      delete finals_;
      finals_ = new finals_geometry_map_t(obj.finals());
    }
    if (obj.name_ != 0)
    {
      delete name_;
      name_ = new std::string(obj.name());
    }
    return *this;
  }

  GEOMETRY_TPARAM
  inline
  GEOMETRY::~geometry()
  {
    delete states_;
    delete transitions_;
    delete initials_;
    delete finals_;
    delete name_;
  }


  GEOMETRY_TPARAM
  inline
  typename GEOMETRY::states_geometry_map_t&
  GEOMETRY::states()
  {
    if (! states_)
      states_ = new states_geometry_map_t();
    return *states_;
  }

  GEOMETRY_TPARAM
  inline
  const typename GEOMETRY::states_geometry_map_t&
  GEOMETRY::states() const
  {
    if (! states_)
      states_ = new states_geometry_map_t();
    return *states_;
  }


  GEOMETRY_TPARAM
  inline
  typename GEOMETRY::transitions_geometry_map_t&
  GEOMETRY::transitions()
  {
    if (! transitions_)
      transitions_ = new transitions_geometry_map_t();
    return *transitions_;
  }

  GEOMETRY_TPARAM
  inline
  const typename GEOMETRY::transitions_geometry_map_t&
  GEOMETRY::transitions() const
  {
    if (! transitions_)
      transitions_ = new transitions_geometry_map_t();
    return *transitions_;
  }


  GEOMETRY_TPARAM
  inline
  typename GEOMETRY::initials_geometry_map_t&
  GEOMETRY::initials()
  {
    if (! initials_)
      initials_ = new initials_geometry_map_t();
    return *initials_;
  }

  GEOMETRY_TPARAM
  inline
  const typename GEOMETRY::initials_geometry_map_t&
  GEOMETRY::initials() const
  {
    if (! initials_)
      initials_ = new initials_geometry_map_t();
    return *initials_;
  }


  GEOMETRY_TPARAM
  inline
  typename GEOMETRY::finals_geometry_map_t&
  GEOMETRY::finals()
  {
    if (! finals_)
      finals_ = new finals_geometry_map_t();
    return *finals_;
  }

  GEOMETRY_TPARAM
  inline
  const typename GEOMETRY::finals_geometry_map_t&
  GEOMETRY::finals() const
  {
    if (! finals_)
      finals_ = new finals_geometry_map_t();
    return *finals_;
  }


  GEOMETRY_TPARAM
  inline
  std::string&
  GEOMETRY::name()
  {
    if (! name_)
      name_ = new std::string();
    return *name_;
  }

  GEOMETRY_TPARAM
  inline
  const std::string&
  GEOMETRY::name() const
  {
    if (! name_)
      name_ = new std::string();
    return *name_;
  }


} // !vcsn


#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_GEOMETRY_HXX
