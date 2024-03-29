// kinds.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_AUTOMATA_CONCEPT_KINDS_HXX
# define VCSN_AUTOMATA_CONCEPT_KINDS_HXX

# include <iterator>
# include <algorithm>

# include <vaucanson/misc/contract.hh>
# include <vaucanson/misc/container_ops.hh>
# include <vaucanson/automata/concept/handlers.hh>

namespace vcsn {

  template<typename Series,
	   typename MonoidElt,
	   typename SemiringElt,
	   typename L>
  ls_delta_letter_query<Series, MonoidElt, SemiringElt, L>::
  ls_delta_letter_query(const Series& s, const L& l)
    : s_(s),
      l_(op_convert(SELECT(typename MonoidElt::set_t),
		    SELECT(typename MonoidElt::value_t),
		    l))
  {}

  template<typename Series,
	   typename MonoidElt,
	   typename SemiringElt,
	   typename L>
  template<typename Label>
  bool ls_delta_letter_query<Series, MonoidElt, SemiringElt, L>::
  operator()(const Label& label) const
  {
    return (op_series_get(s_.get(), label, l_)
	    != zero_value(SELECT(typename SemiringElt::set_t),
			  SELECT(typename SemiringElt::value_t)));
  }



  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  Element<Series, SeriesT>
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  series_of(htransition_t e) const
  {
    return series_set_elt_t(auto_self().series(),
			    auto_self().label_of(e));
  }

  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  const SeriesT&
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  series_value_of(htransition_t e) const
  {
    return auto_self().label_of(e);
  }

  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  bool
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  is_spontaneous(htransition_t e) const
  {
    const series_set_elt_t& s = auto_self().label_of(e);

    return s == algebra::identity_as<SeriesT>::of(s.set());
  }

  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  template<typename L>
  L
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  letter_of(SELECTOR(L), htransition_t e) const
  {
    return *op_begin(auto_self().series().monoid(),
		     auto_self().label_of(e).begin()->first);
  }

  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  typename Element<Series, SeriesT>::monoid_elt_t
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  word_of(htransition_t e) const
  {
    const LabelT& l = auto_self().label_of(e);

    return monoid_elt_t(auto_self().series().monoid(),
			l.begin()->first);
  }

  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  const typename Element<Series, SeriesT>::monoid_elt_t::value_t&
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  word_value_of(htransition_t e) const
  {
    return auto_self().label_of(e).begin()->first;
  }

  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  template<typename S>
  typename Self::htransition_t
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  add_series_transition(hstate_t from, hstate_t to,
			const S& e)
  {
    return auto_self().add_transition(from, to, e.value());
  }

  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  typename Self::htransition_t
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  add_spontaneous(hstate_t from, hstate_t to)
  {
    return auto_self().add_transition(from, to,
				      identity_value(SELECT(Series),
						     SELECT(SeriesT)));
  }

  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  template<typename L>
  typename Self::htransition_t
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  add_letter_transition(hstate_t from, hstate_t to,
			const L& l)
  {
    return auto_self().add_transition(from, to,
				      series_set_elt_t(auto_self().series(),
						       monoid_elt_t(auto_self().series().monoid(),
								    l)
					).value()
      );
  }

  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  Self&
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  auto_self()
  { return static_cast<Self&>(*this); }

  template<typename Self, typename Series, typename SeriesT, typename LabelT>
  const Self&
  AutoKind<labels_are_series, Self, Series, SeriesT, LabelT>::
  auto_self() const
  { return static_cast<const Self&>(*this); }

}

#endif // ! VCSN_AUTOMATA_CONCEPT_KINDS_HXX
