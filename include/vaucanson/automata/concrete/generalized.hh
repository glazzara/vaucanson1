// generalized.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VAUCANSON_AUTOMATA_CONCRETE_GENERALIZED_HH
# define VAUCANSON_AUTOMATA_CONCRETE_GENERALIZED_HH

# include <vaucanson/automata/concept/automata.hh>
# include <vaucanson/automata/concept/kinds.hh>
# include <vaucanson/automata/concept/tags.hh>
# include <vaucanson/automata/concept/automaton_impl.hh>
# include <vaucanson/automata/concrete/manylinks.hh>
# include <vaucanson/automata/concept/copy.hh>
# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/algebra/concrete/series/generalized.hh>
# include <vaucanson/algebra/concrete/series/rat/exp.hh>
# include <vaucanson/algebra/concrete/series/krat.hh>
# include <map>

namespace vcsn {

  /*----------------------.
  | Generalized automaton |
  `----------------------*/
  template <class Auto_>
  struct generalized_traits
  {
    // FIXME: static check on the concept of automaton
    typedef typename Auto_::series_t		series_t;
    typedef typename Auto_::series_elt_t	series_elt_t;
    typedef typename series_elt_t::monoid_elt_t monoid_elt_t;
    typedef typename monoid_elt_t::value_t	monoid_value_t;
    typedef typename series_elt_t::weight_t     weight_t;
    typedef typename weight_t::value_t		weight_value_t;

    // FIXME: such workarounds should not appear in the interface files.
#ifdef __ICC
    template <class F, class T>
    struct map : std::map<F, T>
    {};

    typedef vcsn::Element<vcsn::Automata,
      utility::ref<
      vcsn::AutomatonImpl
    <
      vcsn::labels_are_series,
      series_t,
      rat::exp<monoid_value_t, weight_value_t>,
      vcsn::ManyLinks
      <
      rat::exp<monoid_value_t, weight_value_t>,
      vcsn::NoTag,
      vcsn::NoTag 
      >,
      vcsn::NoTag,
      map 
    > > > automaton_t;
  };
#else
    typedef vcsn::Element<vcsn::Automata,
      utility::ref<
      vcsn::AutomatonImpl
    <
      vcsn::labels_are_series,
      series_t,
      rat::exp<monoid_value_t, weight_value_t>,
      vcsn::ManyLinks
      <
      rat::exp<monoid_value_t, weight_value_t>,
      vcsn::NoTag,
      vcsn::NoTag 
      >,
      vcsn::NoTag,
      std::map 
    > > > automaton_t;
  };
#endif

  template <class Auto_>
  typename generalized_traits<Auto_>::automaton_t
  generalized(const Auto_& from);
  
} // vcsn

# include <vaucanson/automata/concrete/generalized.hxx>

#endif // VAUCANSON_AUTOMATA_GENERALIZED_HH
