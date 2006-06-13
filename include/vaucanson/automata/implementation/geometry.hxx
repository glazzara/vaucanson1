// geometry.hxx: this file is part of the Vaucanson project.
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
  inline
  geometry::geometry()
    : states_(0), transitions_(0), initials_(0), finals_(0), name_(0)
  {}

  inline
  geometry& geometry::operator=(const geometry& obj)
  {
    return copy_from(obj);
  }

  inline
  geometry::geometry(const geometry& obj)
    : states_(0), transitions_(0), initials_(0), finals_(0), name_(0)
  {
    copy_from(obj);
  }

  inline
  geometry& geometry::copy_from(const geometry& obj)
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

  inline
  geometry::~geometry()
  {
    delete states_;
    delete transitions_;
    delete initials_;
    delete finals_;
    delete name_;
  }


  inline
  geometry::states_geometry_map_t& geometry::states()
  {
    if (! states_)
      states_ = new states_geometry_map_t();
    return *states_;
  }

  inline
  const geometry::states_geometry_map_t& geometry::states() const
  {
    if (! states_)
      states_ = new states_geometry_map_t();
    return *states_;
  }


  inline
  geometry::transitions_geometry_map_t& geometry::transitions()
  {
    if (! transitions_)
      transitions_ = new transitions_geometry_map_t();
    return *transitions_;
  }

  inline
  const geometry::transitions_geometry_map_t& geometry::transitions() const
  {
    if (! transitions_)
      transitions_ = new transitions_geometry_map_t();
    return *transitions_;
  }


  inline
  geometry::initials_geometry_map_t& geometry::initials()
  {
    if (! initials_)
      initials_ = new initials_geometry_map_t();
    return *initials_;
  }

  inline
  const geometry::initials_geometry_map_t& geometry::initials() const
  {
    if (! initials_)
      initials_ = new initials_geometry_map_t();
    return *initials_;
  }


  inline
  geometry::finals_geometry_map_t& geometry::finals()
  {
    if (! finals_)
      finals_ = new finals_geometry_map_t();
    return *finals_;
  }

  inline
  const geometry::finals_geometry_map_t& geometry::finals() const
  {
    if (! finals_)
      finals_ = new finals_geometry_map_t();
    return *finals_;
  }


  inline
  std::string& geometry::name()
  {
    if (! name_)
      name_ = new std::string();
    return *name_;
  }

  inline
  const std::string& geometry::name() const
  {
    if (! name_)
      name_ = new std::string();
    return *name_;
  }


} // !vcsn


#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_GEOMETRY_HXX
