// kinds.hh: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The Vaucanson Group represents the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@iafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//
#ifndef VCSN_AUTOMATA_CONCEPT_KINDS_HH
# define VCSN_AUTOMATA_CONCEPT_KINDS_HH

# include <vaucanson/config/system.hh>
# include <iterator>
# include <vaucanson/misc/contract.hh>
# include <algorithm>

# include <vaucanson/algebra/concept/series_base.hh>
# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/handlers.hh>

namespace vcsn {
  
  template <
    typename Kind, 
    typename Self, 
    typename Series, 
    typename SeriesT, 
    typename LabelT
    >
  class AutoKind {};

  namespace delta_kind {

    struct edges 
    {};

    struct states 
    {};

  } // delta_kind


  struct labels_are_series 
  {};

  template <
    typename Series, 
    typename MonoidElt, 
    typename SemiringElt, 
    typename L
    >
  struct ls_delta_letter_query
  {
    ls_delta_letter_query(const Series& s, const L& l);
    
    template<typename Label>
    bool operator()(const Label& label) const;

  protected:
    SetSlot<Series>			s_;
    typename MonoidElt::value_t		l_;
  };

  /*--------------------------------.
  | AutoKind<labels_are_series ...> |
  `--------------------------------*/
  /// Add adapted accessors in function of the automaton kind.
  /** AutoKind adds methods to automaton adapted to the kind of label
    that are held by the internal data structure. Indeed, label can be
    either series element or things from which series elements can be
    build. In the latter case, we have to insert a series construction
    in each accessor.
  */
 template <
    typename Self, 
    typename Series, 
    typename SeriesT, 
    typename LabelT
    >
  class AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>
  {
  protected:
    typedef Element<Series, SeriesT>			series_set_elt_t;
    typedef typename Series::monoid_t			monoid_t;
    typedef typename series_set_elt_t::monoid_elt_t		monoid_elt_t;
    typedef typename Series::semiring_t			semiring_t;
    typedef typename series_set_elt_t::semiring_elt_t		semiring_elt_t;

  public:

    series_set_elt_t series_of(hedge_t e) const;

    const SeriesT& series_value_of(hedge_t e) const;

    bool is_spontaneous(hedge_t e) const;

    template<typename L>
    L letter_of(SELECTOR(L), hedge_t e) const;

    monoid_elt_t word_of(hedge_t e) const;

    const typename monoid_elt_t::value_t& word_value_of(hedge_t e) const;

    template<typename S>
    hedge_t add_series_edge(hstate_t from, hstate_t to, 
			   const S& e);

    hedge_t add_spontaneous(hstate_t from, hstate_t to);

    template<typename L>
    hedge_t add_letter_edge(hstate_t from, hstate_t to,
			    const L& l);

    template <typename OutputIterator, typename L>   
    void letter_delta(OutputIterator	res, 
		      hstate_t		from, 
		      const L&		l, 
		      delta_kind::edges k = delta_kind::edges()) const;

    template <typename Container, typename L>
    void letter_deltac(Container&	 dst, 
		       hstate_t		 from, 
		       const L&		 l, 
		       delta_kind::edges k = delta_kind::edges()) const;

    template <typename OutputIterator, typename L>   
    void letter_rdelta(OutputIterator	res, 
		      hstate_t		from, 
		      const L&		l, 
		      delta_kind::edges k = delta_kind::edges()) const;

    template <typename Container, typename L>
    void letter_rdeltac(Container&	 dst, 
		       hstate_t		 from, 
		       const L&		 l, 
		       delta_kind::edges k = delta_kind::edges()) const;

    template <typename OutputIterator, typename L>   
    void letter_delta(OutputIterator 	 res, 
		      hstate_t		 from, 
		      const L&		 l, 
		      delta_kind::states k) const;

    template <typename Container, typename L>
    void letter_deltac(Container&	  dst, 
		       hstate_t		  from, 
		       const L&		  l, 
		       delta_kind::states k) const;

    template <typename OutputIterator, typename L>   
    void letter_rdelta(OutputIterator	  res, 
		       hstate_t		  from, 
		       const L&		  l, 
		       delta_kind::states k) const;
    
    template <typename Container, typename L>
    void letter_rdeltac(Container&	   dst, 
			hstate_t	   from, 
			const L&	   l, 
			delta_kind::states k) const;

  protected:
    Self&       auto_self();
    const Self& auto_self() const;
  };


  struct labels_are_couples 
  {};

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
    typedef Element<Series, SeriesT>			series_set_elt_t;
    typedef typename Series::monoid_t			monoid_t;
    typedef typename series_set_elt_t::monoid_elt_t		monoid_elt_t;
    typedef typename Series::semiring_t			semiring_t;
    typedef typename series_set_elt_t::semiring_elt_t		semiring_elt_t;

  public:

    series_set_elt_t  series_of(hedge_t e) const;

    const SeriesT series_value_of(hedge_t e) const;

    bool is_spontaneous(hedge_t e) const;

    template<typename L>
    L letter_of(SELECTOR(L), hedge_t e) const;

    monoid_elt_t word_of(hedge_t e) const;

    const typename monoid_elt_t::value_t& word_value_of(hedge_t e) const;

    template<typename S>
    hedge_t add_series_edge(hstate_t from, hstate_t to, 
			   const S& e);

    hedge_t add_spontaneous(hstate_t from, hstate_t to);

    template<typename L>
    hedge_t add_letter_edge(hstate_t from, hstate_t to,
			    const L& l);

    template <typename OutputIterator, typename L>   
    void letter_delta(OutputIterator	res, 
		      hstate_t		from, 
		      const L&		l, 
		      delta_kind::edges k = delta_kind::edges()) const;

    template <typename Container, typename L>
    void letter_deltac(Container&	 dst, 
		       hstate_t		 from, 
		       const L&		 l, 
		       delta_kind::edges k = delta_kind::edges()) const;

    template <typename OutputIterator, typename L>   
    void letter_rdelta(OutputIterator	res, 
		      hstate_t		from, 
		      const L&		l, 
		      delta_kind::edges k = delta_kind::edges()) const;

    template <typename Container, typename L>
    void letter_rdeltac(Container&	 dst, 
			hstate_t		 from, 
			const L&		 l, 
			delta_kind::edges k = delta_kind::edges()) const;

    template <typename OutputIterator, typename L>   
    void letter_delta(OutputIterator 	 res, 
		      hstate_t		 from, 
		      const L&		 l, 
		      delta_kind::states k) const;

    template <typename Container, typename L>
    void letter_deltac(Container&	  dst, 
		       hstate_t		  from, 
		       const L&		  l, 
		       delta_kind::states k) const;

    template <typename OutputIterator, typename L>   
    void letter_rdelta(OutputIterator	  res, 
		       hstate_t		  from, 
		       const L&		  l, 
		       delta_kind::states k) const;
    
    template <typename Container, typename L>
    void letter_rdeltac(Container&	   dst, 
			hstate_t	   from, 
			const L&	   l, 
			delta_kind::states k) const;

  protected:
    Self&       auto_self();
    const Self& auto_self() const;
  };

}
 

#ifndef VCSN_USE_INTERFACE_ONLY
    # include <vaucanson/automata/concept/kinds.hxx>
#endif // VCSN_USE_INTERFACE_ONLY
    

#endif // VCSN_AUTOMATA_CONCEPT_KINDS_HH
