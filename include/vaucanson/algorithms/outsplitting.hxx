// outsplitting.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2005 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_OUTSPLITTING_HXX
# define VCSN_ALGORITHMS_OUTSPLITTING_HXX


/**
 * @file outsplitting.hxx
 *
 * @brief Outsplitting and insplitting algorithms for normalized and
 * sub-normalized transducers seen as automata over a free monoid
 * product.
 *
 * @author Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
 */

# include <vaucanson/algorithms/outsplitting.hh>
# include <vaucanson/algorithms/accessible.hh>
# include <vaucanson/algebra/implementation/series/series.hh>
# include <vaucanson/algebra/concept/freemonoid_product.hh>

namespace vcsn {

  /// Separate states considering their output:
  /// a|1 on one state,
  /// 1|x and a|x on the other.

  template <typename S, typename M1, typename M2, typename Auto_t>
  Auto_t
  do_outsplitting(const AutomataBase<S>&,
		  const algebra::FreeMonoidProduct<M1, M2>&,
		  const Auto_t& aut,
		  std::set<hstate_t>& m)
  {
    AUTOMATON_TYPES(Auto_t);

    typedef typename series_set_elt_t::support_t	support_t;

    typedef typename monoid_t::second_monoid_t	second_monoid_t;

    typedef typename monoid_elt_value_t::second_type
      second_monoid_elt_value_t;
    typedef Element<second_monoid_t, second_monoid_elt_value_t>
      second_monoid_elt_t;

    typedef std::set<htransition_t>			set_of_transitions_t;



    second_monoid_elt_t second_identity =
      algebra::identity_as<second_monoid_elt_value_t>::
      of(aut.structure().series().monoid().second_monoid());

    Auto_t res(aut);

    const series_set_t&	series	 = res.structure().series();
    const monoid_t&	monoid	 = series.monoid();



    for_each_state(s, res)
    {
      bool eps_out = false;
      bool other_out = false;
      bool diff = false;

      // Test whether there are different types of outgoing transitions.

      set_of_transitions_t transitions;
      res.deltac(transitions, *s, delta_kind::transitions());
      for_each_const_(set_of_transitions_t, e, transitions)
      {
	const series_set_elt_t	series	= res.series_of(*e);
	support_t			supp = series.supp();
	const monoid_elt_t		supp_elt (monoid, *(supp.begin()));

	if (supp_elt.value().second == second_identity.value())
	  eps_out = true;
	else
	  other_out = true;
	if (eps_out and other_out)
	{
	  diff = true;
	  break;
	}
      }

      if (eps_out and not diff)
	m.insert(*s);

      // If there are different types of outgoing transitions.
      if (diff)
      {
	hstate_t s2 = res.add_state();
	if (res.is_initial(*s))
	  res.set_initial(s2, res.get_initial(*s));

	set_of_transitions_t in_transitions;
	res.rdeltac(in_transitions, *s, delta_kind::transitions());

	for_each_(set_of_transitions_t, e, in_transitions)
	  res.add_series_transition(res.origin_of(*e), s2, res.series_of(*e));

	for_each_const_(set_of_transitions_t, e, transitions)
	{
	  const series_set_elt_t	series	= res.series_of(*e);
	  support_t		supp = series.supp();
	  const monoid_elt_t	supp_elt (monoid, *(supp.begin()));

	  if (supp_elt.value().second == second_identity.value())
	  {
	    res.add_series_transition(s2, res.aim_of(*e), res.series_of(*e));
	    res.del_transition(*e);
	  }
	}
	m.insert(s2);
      }
    }
    return coaccessible(res);
  }


  /// Separate states considering their input:
  /// 1|x on one state,
  /// a|1 and a|x on the other.

  template <typename S, typename M1, typename M2, typename Auto_t>
  Auto_t
  do_insplitting(const AutomataBase<S>&,
		 const algebra::FreeMonoidProduct<M1, M2>&,
		 const Auto_t& aut,
		 std::set<hstate_t>& m)
  {
    AUTOMATON_TYPES(Auto_t);

    typedef typename series_set_elt_t::support_t	support_t;

    typedef typename monoid_t::first_monoid_t	first_monoid_t;

    typedef typename monoid_elt_value_t::first_type
      first_monoid_elt_value_t;
    typedef Element<first_monoid_t, first_monoid_elt_value_t>
      first_monoid_elt_t;

    typedef std::set<htransition_t>			set_of_transitions_t;



    first_monoid_elt_t first_identity =
      algebra::identity_as<first_monoid_elt_value_t>::
      of(aut.structure().series().monoid().first_monoid());

    Auto_t res(aut);

    const series_set_t&	series	 = res.structure().series();
    const monoid_t&	monoid	 = series.monoid();



    for_each_state(s, res)
    {
      bool eps_in = false;
      bool other_in = false;
      bool diff = false;

      // Test whether there are different types of incoming transitions.

      set_of_transitions_t transitions;
      res.rdeltac(transitions, *s, delta_kind::transitions());
      for_each_const_(set_of_transitions_t, e, transitions)
      {
	const series_set_elt_t	series	= res.series_of(*e);
	support_t			supp = series.supp();
	const monoid_elt_t		supp_elt (monoid, *(supp.begin()));

	if (supp_elt.value().first == first_identity.value())
	  eps_in = true;
	else
	  other_in = true;
	if (eps_in and other_in)
	{
	  diff = true;
	  break;
	}
      }

      if (eps_in and not diff)
	m.insert(*s);

      // If there are different types of incoming transitions.
      if (diff)
      {
	hstate_t s2 = res.add_state();
	if (res.is_final(*s))
	  res.set_final(s2, res.get_final(*s));

	set_of_transitions_t out_transitions;
	res.deltac(out_transitions, *s, delta_kind::transitions());

	for_each_(set_of_transitions_t, e, out_transitions)
	  res.add_series_transition(s2, res.aim_of(*e), res.series_of(*e));

	for_each_const_(set_of_transitions_t, e, transitions)
	{
	  const series_set_elt_t	series	= res.series_of(*e);
	  support_t		supp = series.supp();
	  const monoid_elt_t	supp_elt (monoid, *(supp.begin()));

	  if (supp_elt.value().first == first_identity.value())
	  {
	    res.add_series_transition(res.origin_of(*e), s2,
				      res.series_of(*e));
	    res.del_transition(*e);
	  }
	}
	m.insert(s2);
      }
    }
    return res;
  }


  template <typename S, typename T>
  Element<S, T>
  outsplitting(const Element<S, T>& aut, std::set<hstate_t>& states)
  {
    return do_outsplitting(aut.structure(),
			   aut.structure().series().monoid(),
			   aut,
			   states);
  }


  template <typename S, typename T>
  Element<S, T>
  insplitting(const Element<S, T>& aut, std::set<hstate_t>& states)
  {
    return do_insplitting(aut.structure(),
			  aut.structure().series().monoid(),
			  aut,
			  states);
  }



  template <typename S, typename T>
  Element<S, T>
  outsplitting(const Element<S, T>& aut)
  {
    std::set<hstate_t>		states;
    return do_outsplitting(aut.structure(),
			   aut.structure().series().monoid(),
			   aut,
			   states);
  }


  template <typename S, typename T>
  Element<S, T>
  insplitting(const Element<S, T>& aut)
  {
    std::set<hstate_t>		states;
    return do_insplitting(aut.structure(),
			  aut.structure().series().monoid(),
			  aut,
			  states);
  }

} // End of namespace vcsn.

#endif // ! VCSN_ALGORITHMS_OUTSPLITTING_HXX
