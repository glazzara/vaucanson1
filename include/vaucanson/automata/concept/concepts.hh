// concepts.hh
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
#ifndef AUTOMATA_CONCEPTS_HH
# define AUTOMATA_CONCEPTS_HH

# include <vaucanson/algebra/concept/concepts.hh>
# include <vaucanson/automata/concept/automata_base.hh>

namespace vcsn
{
  
  template<typename S, typename T>
  struct AutomataConcept
  {
    S s;
    typedef Element<S, T> auto_t;
    auto_t a;

    typedef typename auto_t::label_t label_t;
    typedef typename auto_t::series_t series_t;
    typedef typename auto_t::series_value_t series_value_t;
    typedef typename auto_t::monoid_t monoid_t;
    typedef typename auto_t::weights_t weights_t;

    void constraints();

    AutomataBase<S>&			check_inheritance();
    MetaElement<AutomataBase<S>, T>&	check_elt_inheritance();


    hstate_t check_add_state();

    bool check_ref_ops(const auto_t& ac);

    Element<series_t, series_value_t> check_get_initial(const auto_t& a);

    Element<series_t, series_value_t> check_get_final(const auto_t& a);

    bool check_has(const auto_t& a);

    typename auto_t::series_t& check_series();

    const typename auto_t::series_t& check_const_series(const auto_t& a);

  };
    
}

# include <vaucanson/automata/concept/concepts.hxx>

#endif

