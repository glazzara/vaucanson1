// sub_normalize.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_SUB_NORMALIZE_HXX
# define VCSN_ALGORITHMS_SUB_NORMALIZE_HXX

/**
   * @file sub_normalize.hxx
   *
   * Sub-normalization algorithm for FMP transducers.
   *
   * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
   */


namespace vcsn {

  /*------------------.
  | is_sub_normalized |
  `------------------*/

  template <class M1, class M2, class Auto>
  bool do_is_sub_normalized(const algebra::FreeMonoidProduct<M1, M2>&,
			    const Auto& a)
  {
    AUTOMATON_TYPES(Auto);
    typedef typename series_set_elt_t::support_t support_t;

    for_all_initial_states(i, a)
    {
      series_set_elt_t label = a.get_initial(*i);
      for (typename support_t::const_iterator it = label.supp().begin();
	   it != label.supp().end(); ++it)
	if ((*it).first.size() > 1 || (*it).second.size() > 1)
	  return false;
    }

    for_all_final_states(f, a)
    {
      series_set_elt_t label = a.get_initial(*f);
      for (typename support_t::const_iterator it = label.supp().begin();
	   it != label.supp().end(); ++it)
	if ((*it).first.size() > 1 || (*it).second.size() > 1)
	  return false;
    }

    for_all_transitions(e, a)
    {
      series_set_elt_t label = a.series_of(*e);
      for (typename support_t::const_iterator it = label.supp().begin();
	   it != label.supp().end(); ++it)
	if ((*it).first.size() > 1 || (*it).second.size() > 1)
	  return false;
    }

    return true;
  }


  /*--------------.
  | sub_normalize |
  `--------------*/

  template <class Auto, class Label>
  int do_sub_normalize_transition(Auto& a,
				  hstate_t start, hstate_t stop,
				  const Label& label, bool initial, bool final)
  {
    AUTOMATON_TYPES(Auto);
    hstate_t			s0;
    hstate_t			s1;
    typedef typename monoid_elt_t::first_monoid_elt_t first_monoid_elt_t;
    typedef typename monoid_elt_t::second_monoid_elt_t
      second_monoid_elt_t;
    typedef typename monoid_elt_t::first_monoid_elt_value_t
      first_monoid_elt_value_t;
    typedef typename monoid_elt_t::second_monoid_elt_value_t
      second_monoid_elt_value_t;

    first_monoid_elt_value_t m1_ident =
      algebra::identity_as<first_monoid_elt_value_t>
      ::of(a.structure().series().monoid().first_monoid()).value();
    second_monoid_elt_value_t m2_ident =
      algebra::identity_as<second_monoid_elt_value_t>
      ::of(a.structure().series().monoid().second_monoid()).value();

    semiring_elt_t s_ident =
      algebra::identity_as<semiring_elt_value_t>
      ::of(a.structure().series().semiring());


    monoid_elt_t m1(a.structure().series().monoid(),
		    *(label.supp().begin()));
    first_monoid_elt_value_t w1 = m1.value().first;
    second_monoid_elt_value_t w2 = m1.value().second;

    int size1 = w1.size();
    int size2 = w2.size();
    int cpt1 = 0;
    int cpt2 = 0;

    unsigned int size = std::max(w1.size(), w2.size());

    if (size > 1)
    {
      monoid_elt_t m(a.structure().series().monoid());

      semiring_elt_t s = label.get(m1);
      series_set_elt_t in_series(a.structure().series());

      m = std::make_pair(cpt1 < size1 ? w1.substr(cpt1++, 1) : m1_ident,
			 cpt2 < size2 ? w2.substr(cpt2++, 1) : m2_ident);

      in_series.assoc(m, s);

      if (initial)
      {
	s0 = a.add_state();
	a.set_initial(s0, in_series);
	a.unset_initial(stop);
	s1 = s0;
      }
      else
      {
	s0 = start;
	s1 = a.add_state();
	a.add_series_transition(s0, s1, in_series);
      }

      for (unsigned int i = 1; i < size - 1; ++i)
      {
	m = std::make_pair(cpt1 < size1 ? w1.substr(cpt1++, 1) : m1_ident,
			   cpt2 < size2 ? w2.substr(cpt2++, 1) : m2_ident);
	s0 = s1;
	s1 = a.add_state();
	series_set_elt_t series(a.structure().series());
	series.assoc(m, s_ident);
	a.add_series_transition(s0, s1, series);
      }

      m = std::make_pair(cpt1 < size1 ? w1.substr(cpt1++, 1) : m1_ident,
			 cpt2 < size2 ? w2.substr(cpt2++, 1) : m2_ident);

      series_set_elt_t out_series(a.structure().series());
      out_series.assoc(m, s_ident);

      if (final)
      {
	a.unset_final(start);
	a.set_final(s1, out_series);
      }
      else
	a.add_series_transition(s1, stop, out_series);

      return 1;
    }

    return 0;
  }



  template <class M1, class M2, class Auto, class Ret>
  void do_sub_normalize(const algebra::FreeMonoidProduct<M1, M2>&,
			const Auto& a,
			Ret& res)
  {
    AUTOMATON_TYPES(Ret);
    typedef std::vector<hstate_t> vector_t;

    auto_copy(res, cut_up(a));

    transitions_t transitions = res.transitions();
    vector_t i_states; i_states.reserve(res.initial().size());
    vector_t f_states; f_states.reserve(res.final().size());

    for_all_initial_states(f, res)
      i_states.push_back(*f);
    for_all_final_states(i, res)
      f_states.push_back(*i);

    for_all_(vector_t, i, i_states)
      do_sub_normalize_transition(res, hstate_t(), *i,
				  res.get_initial(*i), true, false);

    for_all_(vector_t, f, f_states)
      do_sub_normalize_transition(res, *f, hstate_t(),
				  res.get_final(*f), false, true);

    for_all_(transitions_t, e, transitions)
      if (do_sub_normalize_transition(res, res.src_of(*e), res.dst_of(*e),
				      res.series_of(*e), false, false))
	res.del_transition(*e);
  }


  /*---------.
  | Wrappers |
  `---------*/

  template <class S, class T>
  Element<S, T>
  sub_normalize(const Element<S, T>& a)
  {
    Element<S, T> res(a.structure());
    do_sub_normalize(a.structure().series().monoid(), a, res);

    return res;
  }


  template <class S, class T>
  void
  sub_normalize(const Element<S, T>& a, Element<S, T>& res)
  {
    do_sub_normalize(a.structure().series().monoid(), a, res);
  }

  template <class S, class T>
  void
  sub_normalize_here(Element<S, T>& a)
  {
    do_sub_normalize (a.structure().series().monoid(), a, a);
  }

  template <class S, class T>
  bool is_sub_normalized(const Element<S, T>& a)
  {
    return do_is_sub_normalized(a.structure().series().monoid(), a);
  }

} // ! vcsn

#endif // ! VCSN_ALGORITHMS_SUB_NORMALIZE_HXX
