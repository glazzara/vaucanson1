// kinds.hh
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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

#ifndef AUTOMATA_KINDS_HH
# define AUTOMATA_KINDS_HH

# include <vaucanson/config/system.hh>
# include <iterator>
# include <cassert>
# include <algorithm>

#include <vaucanson/fundamental/fundamental.hh>
#include <vaucanson/automata/concept/handlers.hh>

namespace vcsn
{
  
  template<typename Kind, typename Self, typename Series, typename SeriesT, typename LabelT>
  class AutoKind {};

  namespace delta_kind
  {
    struct edges {};
    struct states {};
  }



  /*-----------------------------------.
  | Automaton labels are series values |
  `-----------------------------------*/


  struct labels_are_series {};

  template<typename Series, typename MonoidElt, typename Weight, typename L>
  struct ls_delta_letter_query
  {
    ls_delta_letter_query(const Series& s, const L& l);

    template<typename Label>
    bool operator()(const Label& label) const;

  protected:
    SetSlot<Series>			s_;
    typename MonoidElt::value_t		l_;
  };


  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  class AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>
  {
  protected:
    typedef Element<Series, SeriesT>			series_elt_t;
    typedef typename Series::monoid_t			monoid_t;
    typedef typename series_elt_t::monoid_elt_t		monoid_elt_t;
    typedef typename Series::weights_t			weights_t;
    typedef typename series_elt_t::weight_t		weight_t;

  public:

    series_elt_t serie_of(hedge_t e) const;

    const SeriesT& serie_value_of(hedge_t e) const;

    bool is_spontaneous(hedge_t e) const;

    template<typename L>
    L letter_of(SELECTOR(L), hedge_t e) const;

    monoid_elt_t word_of(hedge_t e) const;

    const typename monoid_elt_t::value_t& word_value_of(hedge_t e) const;

    template<typename S>
    hedge_t add_serie_edge(hstate_t from, hstate_t to, 
			   const S& e);

    hedge_t add_spontaneous(hstate_t from, hstate_t to);

    template<typename L>
    hedge_t add_letter_edge(hstate_t from, hstate_t to,
			    const L& l);

#define DELTA_IMPL(Name, Kind_type, Init)								\
    template<typename OutputIterator, typename L>							\
    void letter_ ## Name (OutputIterator res, hstate_t from, const L& l, Kind_type k Init) const;	\
                                                                                                        \
    template<typename Container, typename L>								\
    void letter_ ## Name ## c (Container &dst, hstate_t from, const L& l, Kind_type k Init) const;	


    DELTA_IMPL(delta, delta_kind::edges, = delta_kind::edges());
    DELTA_IMPL(rdelta, delta_kind::edges, = delta_kind::edges());

    DELTA_IMPL(delta, delta_kind::states, );
    DELTA_IMPL(rdelta, delta_kind::states, );
#undef DELTA_IMPL

  protected:

    Self& auto_self();
    const Self& auto_self() const;
  };




  /*-----------------------------------------------------------.
  | Automaton labels are pairs (weight value, monoidelt value) |
  `-----------------------------------------------------------*/

  struct labels_are_couples {};

  template<typename Monoid, typename L>
  struct lc_delta_letter_query
  {
    lc_delta_letter_query(const Monoid& m, const L& l);

    template<typename Label>
    bool operator()(const Label& label) const;

  protected:
    SetSlot<Monoid>		m_;
    L				l_;
  };



  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  class AutoKind<labels_are_couples, Self, Series, SeriesT, LabelT>
  {
  protected:
    typedef Element<Series, SeriesT> series_elt_t;
    typedef typename Series::monoid_t monoid_t;
    typedef typename series_elt_t::monoid_elt_t monoid_elt_t;
    typedef typename Series::weights_t weights_t;
    typedef typename series_elt_t::weight_t weight_t;

  public:

    series_elt_t serie_of(hedge_t e) const;

    const SeriesT serie_value_of(hedge_t e) const;

    bool is_spontaneous(hedge_t e) const;

    template<typename L>
    L letter_of(SELECTOR(L), hedge_t e) const;

    monoid_elt_t word_of(hedge_t e) const;

    const typename monoid_elt_t::value_t& word_value_of(hedge_t e) const;

    template<typename S>
    hedge_t add_serie_edge(hstate_t from, hstate_t to, 
			   const S& e);

    hedge_t add_spontaneous(hstate_t from, hstate_t to);

    template<typename L>
    hedge_t add_letter_edge(hstate_t from, hstate_t to,
			    const L& l);

#define DELTA_IMPL(Name, Kind_type, Init)								\
    template<typename OutputIterator, typename L>							\
    void letter_ ## Name (OutputIterator res, hstate_t from, const L& l, Kind_type k Init) const;	\
                                                                                                        \
    template<typename Container, typename L>								\
    void letter_ ## Name (Container &dst, hstate_t from, const L& l, Kind_type k Init) const;		

    DELTA_IMPL(delta, delta_kind::edges, = delta_kind::edges());
    DELTA_IMPL(rdelta, delta_kind::edges, = delta_kind::edges());

    DELTA_IMPL(delta, delta_kind::states, );
    DELTA_IMPL(rdelta, delta_kind::states, );
#undef DELTA_IMPL

  protected:

    Self& auto_self();
    const Self& auto_self() const;
  };

}
 
# include <vaucanson/automata/concept/kinds.hxx>

#endif
