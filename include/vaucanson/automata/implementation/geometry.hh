// geometry.hh: this file is part of the Vaucanson project.
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
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_GEOMETRY_HH
# define VCSN_AUTOMATA_IMPLEMENTATION_GEOMETRY_HH

# include <map>
# include <string>
# include <vaucanson/automata/concept/handlers.hh>


namespace vcsn
{
  /**
   * @brief Store 4 maps for geometry properties of the automaton.
   * states_ map is used to store states coordinates.
   * edges_ map is used to store the label position for edges.
   * initials_ map is used to store the label position for initial transitions.
   * finals_ map is used to store the label position for final transitions.
   *
   */
  struct geometry
  {
    // Store in this map state coordinates.
    typedef std::map<hstate_t, std::pair<double, double> >
    states_geometry_map_t;

    // Store in this map label coordinates for edges.
    typedef std::map<hedge_t, std::pair<double, double> >
    edges_geometry_map_t;

    // Store in this map label coordinates for initial transitions.
    typedef std::map<hstate_t, std::pair<double, double> >
    initials_geometry_map_t;

    // Store in this map label coordinates for final transitions.
    typedef std::map<hstate_t, std::pair<double, double> >
    finals_geometry_map_t;

    geometry();
    geometry(const geometry& obj);
    ~geometry();

    /**
     * @brief Retrieve the map of state coordinates.
     *
     **/
    inline states_geometry_map_t& states();
    inline const states_geometry_map_t& states() const;

    /**
     * @brief Retrieve the map of label coordinates for edges.
     *
     **/
    inline edges_geometry_map_t& edges();
    inline const edges_geometry_map_t& edges() const;

    /**
     * @brief Retrieve the map of label coordinates for initial transitions.
     *
     **/
    inline initials_geometry_map_t& initials();
    inline const initials_geometry_map_t& initials() const;

    /**
     * @brief Retrieve the map of label coordinates for final transitions.
     *
     **/
    inline finals_geometry_map_t& finals();
    inline const finals_geometry_map_t& finals() const;

    /**
     * @brief Retrieve the name of the automaton.
     *
     **/
    inline std::string& name();
    inline const std::string& name() const;


  private:
    mutable states_geometry_map_t*	states_;
    mutable edges_geometry_map_t*	edges_;
    mutable initials_geometry_map_t*	initials_;
    mutable finals_geometry_map_t*	finals_;
    mutable std::string*		name_;
  };

} // !vcsn



# ifndef VCSN_USE_INTERFACE_ONLY
#  include <vaucanson/automata/implementation/geometry.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_GEOMETRY_HH