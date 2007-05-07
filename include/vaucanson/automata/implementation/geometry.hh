// geometry.hh: this file is part of the Vaucanson project.
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
   * transitions_ map is used to store the label position for transitions.
   * initials_ map is used to store the label position for initial transitions.
   * finals_ map is used to store the label position for final transitions.
   *
   */
  template<typename HState, typename HTransition, typename Coords>
  struct geometry
  {
    typedef HState hstate_t;
    typedef HTransition htransition_t;
    typedef Coords coords_t;

      // Store in this map state coordinates.
      typedef std::map<hstate_t, coords_t>
      states_geometry_map_t;

      // Store in this map label coordinates for transitions.
      typedef std::map<htransition_t, coords_t>
      transitions_geometry_map_t;

      // Store in this map label coordinates for initial transitions.
      typedef std::map<hstate_t, coords_t>
      initials_geometry_map_t;

      // Store in this map label coordinates for final transitions.
      typedef std::map<hstate_t, coords_t>
      finals_geometry_map_t;

      geometry();
      geometry(const geometry& obj);
      ~geometry();
      inline geometry& operator=(const geometry& obj);
      inline geometry& copy_from(const geometry& obj);

      /**
       * @brief Retrieve the map of state coordinates.
       *
       **/
      inline states_geometry_map_t& states();
      inline const states_geometry_map_t& states() const;

      /**
       * @brief Retrieve the map of label coordinates for transitions.
       *
       **/
      inline transitions_geometry_map_t& transitions();
      inline const transitions_geometry_map_t& transitions() const;

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
      mutable transitions_geometry_map_t*	transitions_;
      mutable initials_geometry_map_t*	initials_;
      mutable finals_geometry_map_t*	finals_;
      mutable std::string*		name_;
  };

} // !vcsn



# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  include <vaucanson/automata/implementation/geometry.hxx>
# endif // VCSN_USE_INTERFACE_ONLY

#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_GEOMETRY_HH
