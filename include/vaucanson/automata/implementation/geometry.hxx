// geometry.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.
// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//

/**
 * @file geometry.hxx
 *
 * Store geometric coordinates. Used in graph.hh.
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */


#ifndef VCSN_AUTOMATA_IMPLEMENTATION_GEOMETRY_HXX
# define VCSN_AUTOMATA_IMPLEMENTATION_GEOMETRY_HXX

namespace vcsn
{
  inline
  geometry::geometry()
    : states_(0), edges_(0), initials_(0), finals_(0)
  {}

  inline
  geometry::geometry(const geometry& obj)
    : states_(0), edges_(0), initials_(0), finals_(0)
  {
    if (obj.states_ != 0)
      states_ = new states_geometry_map_t(obj.states());
    if (obj.edges_ != 0)
      edges_ = new edges_geometry_map_t(obj.edges());
    if (obj.initials_ != 0)
      initials_ = new initials_geometry_map_t(obj.initials());
    if (obj.finals_ != 0)
      finals_ = new finals_geometry_map_t(obj.finals());
  }

  inline
  geometry::~geometry()
  {
    if (states_)
      delete states_;
    if (edges_)
      delete edges_;
    if (initials_)
      delete initials_;
    if (finals_)
      delete finals_;
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
  geometry::edges_geometry_map_t& geometry::edges()
  {
    if (! edges_)
      edges_ = new edges_geometry_map_t();
    return *edges_;
  }

  inline
  const geometry::edges_geometry_map_t& geometry::edges() const
  {
    if (! edges_)
      edges_ = new edges_geometry_map_t();
    return *edges_;
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

} // !vcsn


#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_GEOMETRY_HXX
