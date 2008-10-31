// kinds.hh: this file is part of the Vaucanson project.
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

    struct transitions
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
      typedef typename Self::hstate_t			      hstate_t;
      typedef typename Self::htransition_t		      htransition_t;
      typedef Element<Series, SeriesT>			      series_set_elt_t;
      typedef typename Series::monoid_t			      monoid_t;
      typedef typename series_set_elt_t::monoid_elt_t	      monoid_elt_t;
      typedef typename Series::semiring_t		      semiring_t;
      typedef typename series_set_elt_t::semiring_elt_t	      semiring_elt_t;

    public:

      series_set_elt_t series_of(htransition_t e) const;

      const SeriesT& series_value_of(htransition_t e) const;

      bool is_spontaneous(htransition_t e) const;

      template<typename L>
      L letter_of(SELECTOR(L), htransition_t e) const;

      monoid_elt_t word_of(htransition_t e) const;

      const typename monoid_elt_t::value_t& word_value_of(htransition_t e) const;

      template<typename S>
      htransition_t add_series_transition(hstate_t from, hstate_t to,
					  const S& e);

      htransition_t add_spontaneous(hstate_t from, hstate_t to);

      template<typename L>
      htransition_t add_letter_transition(hstate_t from, hstate_t to,
					  const L& l);

      template <typename Container, typename L>
      void letter_deltac(Container&	 dst,
			 hstate_t		 from,
			 const L&		 l,
			 delta_kind::transitions k = delta_kind::transitions()) const;

      template <typename Container, typename L>
      void letter_rdeltac(Container&	 dst,
			  hstate_t		 from,
			  const L&		 l,
			  delta_kind::transitions k = delta_kind::transitions()) const;

      template <typename Container, typename L>
      void letter_deltac(Container&	  dst,
			 hstate_t		  from,
			 const L&		  l,
			 delta_kind::states k) const;

      template <typename Container, typename L>
      void letter_rdeltac(Container&	   dst,
			  hstate_t	   from,
			  const L&	   l,
			  delta_kind::states k) const;

    protected:
      Self&	  auto_self();
      const Self& auto_self() const;
  };

}

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
# include <vaucanson/automata/concept/kinds.hxx>
#endif // VCSN_USE_INTERFACE_ONLY


#endif // ! VCSN_AUTOMATA_CONCEPT_KINDS_HH
