// generalized.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
#ifndef VCSN_AUTOMATA_IMPLEMENTATION_GENERALIZED_HH
# define VCSN_AUTOMATA_IMPLEMENTATION_GENERALIZED_HH

# include <map>
# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/automata/concept/copy.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/implementation/series/generalized.hh>
# include <vaucanson/algebra/implementation/series/rat/exp.hh>
# include <vaucanson/algebra/implementation/series/krat.hh>
# include <vaucanson/automata/implementation/graph.hh>


namespace vcsn {

  /*----------------------.
  | Generalized automaton |
  `----------------------*/
  template <class Auto_>
  struct generalized_traits
  {
    // FIXME: static check on the concept of automaton
    typedef typename Auto_::series_set_t		series_set_t;
    typedef typename series_set_t::monoid_t		monoid_t;
    typedef typename Auto_::series_set_elt_t		series_set_elt_t;
    typedef typename series_set_elt_t::monoid_elt_t	monoid_elt_t;
    typedef typename monoid_elt_t::value_t		monoid_elt_value_t;
    typedef typename series_set_elt_t::semiring_elt_t	semiring_elt_t;
    typedef typename semiring_elt_t::value_t		semiring_elt_value_t;
    typedef typename Auto_::value_t::geometry_t		geometry_t;
    
    typedef vcsn::Element
    <vcsn::Automata<series_set_t>,
     Graph<labels_are_series,
	   monoid_elt_value_t,
	   semiring_elt_value_t,
	   rat::exp<monoid_elt_value_t, semiring_elt_value_t>,
	   typename monoid_t::letter_t,
	   NoTag,
	   geometry_t>
    > automaton_t;
  };


  template <class Auto_>
  typename generalized_traits<Auto_>::automaton_t
  generalized(const Auto_& from);

} // vcsn


#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/automata/implementation/generalized.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_IMPLEMENTATION_GENERALIZED_HH
