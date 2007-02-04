// build_pattern.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_INTERNAL_BUILD_PATTERN_HH
# define VCSN_ALGORITHMS_INTERNAL_BUILD_PATTERN_HH

# include <map>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/standard.hh>
# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {
  namespace algorithm_patterns
  {

    // This is the structure given to the map, which will
    // call the appropriate function
    template <typename Self, typename Etiq>
    struct Comparator
    {
      bool operator()(const Etiq& e1, const Etiq& e2) const;
    };

    /*-----------------------.
    | IncAutomataConstructor |
    `-----------------------*/

    // This is a pattern for algorithm which build automaton in
    // an incremental way :
    // it starts with one state, and with this state, it builds
    // other states. New states are used to build more and
    // more states.
    // It needs the function applied on each state,
    // and the order used by the map (a default one can be used).
    template <typename Self, typename T_auto, typename Etiq>
    class IncAutomataConstructor
    {
    public:
      // Useful types :))
      typedef T_auto*						T_auto_p;
      AUTOMATON_TYPES(T_auto);
      AUTOMATON_FREEMONOID_TYPES(T_auto);
      // Types for the list
      // It uses a map with an ordered function which can be
      // redefined in Self
      typedef
      std::pair<hstate_t, bool>					StateMarked;
      typedef
      std::map<Etiq, StateMarked, Comparator<Self, Etiq> >	StateMap;
      typedef typename StateMap::iterator			iterator;

      // To run the algorithm
      void	run();
      // To get the result
      T_auto_p	get() const;
      // The function which will compare 2 Etiq
      // User may redefine it !
      static bool compare(const Etiq& e1, const Etiq& e2);
    protected:
      // The constructors (protected in order to not instance the class)
      IncAutomataConstructor(const series_set_t& series, const Etiq& etiq);
      IncAutomataConstructor(const series_set_t& series,
			     const std::list<Etiq>& listexp);
      // Add a link from current state to indicated state
      void	link_to(const Etiq& etiq, const letter_t& l);
      void	link_to(const Etiq& etiq, const series_set_elt_t& el);
      // To make the current state final
      void	set_final();
      void	set_final(const series_set_elt_t& el);
    private:
      // Function to apply on each state (call on_state function)
      void on_state_caller(const Etiq& e);
      // Method to add properly a state
      hstate_t	add_state(const Etiq& etiq);
      // Attributes
      int				unvisited;
      T_auto_p				auto_p;
      StateMap				states_map;
      iterator				current_state;
    };

    /*------------------------.
    | MathAutomataConstructor |
    `------------------------*/

    // This  Algorithm builder takes a struture
    // which contains different functions (like IncAutomataConstructor)
    // but the functions needed are mathematical definitions
    // of the automaton, i.e. :
    // function which return the set of final state,
    // etc.
    // FIXME: make it compatible with multiplicity
    template <typename Self, typename T_auto, typename Etiq>
    class MathAutomataConstructor
    {
    public:
      // Types used. The map make link between Etiq and hstate_t.
      AUTOMATON_TYPES(T_auto);
      AUTOMATON_FREEMONOID_TYPES(T_auto);
      typedef T_auto*						T_auto_p;
      typedef std::map<Etiq, hstate_t, Comparator<Self, Etiq> >	StateMap;
      typedef typename StateMap::iterator			iterator;

      // To run the algorithm and build the entire automaton
      void	run();
      // To get the result
      T_auto_p	get() const;
      // The function which will compare 2 Etiq
      // User may redefine it !
      static bool compare(const Etiq& e1, const Etiq& e2);
    protected:
      // The constructor
      template <typename Container>
      MathAutomataConstructor(const series_set_t& series,
			      const Container container);
    private:
      // Function which will call those which are defined by user
      bool is_initial_caller(const Etiq& e) const;
      bool is_final_caller(const Etiq& e) const;
      // Function which will link a state to a set of states
      template <typename Container>
      void link_to(const hstate_t& state,
		   const letter_t& letter,
		   const Container container);
      // Attributes
      T_auto_p				auto_p;
      StateMap				states_map;
    };

  }
}


#ifndef VCSN_USE_INTERFACE_ONLY
#include <vaucanson/algorithms/internal/build_pattern.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_ALGORITHMS_INTERNAL_BUILD_PATTERN_HH
