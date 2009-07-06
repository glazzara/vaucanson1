// ltl_to_pair.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008, 2009 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_LTL_TO_PAIR_HXX
# define VCSN_ALGORITHMS_LTL_TO_PAIR_HXX

# include <vaucanson/algorithms/ltl_to_pair.hh>
# include <vaucanson/algorithms/is_ltl.hh>

namespace vcsn
{
// Helper to write lighter code.
# define MUTE_TRAITS mute_ltl_to_pair<S, T>

  template <typename S, typename T>
  inline typename MUTE_TRAITS::ret_alphabet_t
  MUTE_TRAITS::
  cartesian_product(const typename MUTE_TRAITS::first_alphabet_t& A,
		    const typename MUTE_TRAITS::second_alphabet_t& B)
  {
    ret_alphabet_t E;

    for_all_const_(first_alphabet_t, i, A)
    {
      for_all_const_(second_alphabet_t, j, B)
      {
	E.insert(std::make_pair(*i, *j));
      }
    }

    return E;
  }

  template <typename S, typename T>
  inline typename MUTE_TRAITS::ret
  MUTE_TRAITS::
  make_automaton(const Element<S, T>& A)
  {
    ret_alphabet_t E = cartesian_product(A.structure().series().monoid().
					 first_monoid().alphabet(),
					 A.structure().series().monoid().
					 second_monoid().alphabet());

    return make_automaton(E);
  }

  template <typename S, typename T>
  inline typename MUTE_TRAITS::ret::series_set_elt_t
  MUTE_TRAITS::
  series_convert(const typename MUTE_TRAITS::ret_series_set_t& series,
		 const typename MUTE_TRAITS::automaton_t::
		 series_set_elt_t& ss)
  {
    typename ret::series_set_elt_t R(series);

    // We assume that the src automaton is an ltl.
    std::basic_string<ret_letter_t> m;
    if (!(*(ss.supp().begin())).first.empty())
      m += std::make_pair(((*(ss.supp().begin())).first)[0],
			  ((*(ss.supp().begin())).second)[0]);
    R.assoc(m, ss.get(*(ss.supp().begin())));

    return R;
  }

  template <typename S, typename T>
  void
  do_ltl_to_pair(const Element<S, T>& src,
		 typename MUTE_TRAITS::ret& res)
  {
    BENCH_TASK_SCOPED("ltl_to_pair");

    // The input FMP transducer must be `letter-to-letter'.
    precondition(is_ltl(src));

    // Type helpers.
    typedef typename MUTE_TRAITS::automaton_t automaton_t;
    typedef MUTE_TRAITS pair_automaton_traits_t;
    typedef typename pair_automaton_traits_t::ret res_t;
    AUTOMATON_TYPES(automaton_t);
    AUTOMATON_TYPES_(res_t, res_);

    // Helper map.
    std::map<hstate_t, res_hstate_t> m;

    for_all_const_states(p, src)
      m[*p] = res.add_state();

    // Setup initial transitions.
    for_all_const_initial_states(i, src)
    {
      res.set_initial(m[*i],
		      pair_automaton_traits_t::
		      series_convert(res.structure().series(),
				     src.get_initial(*i)));
    }

    // Setup normal transitions.
    for_all_const_transitions(e, src)
    {
      res.add_series_transition(m[src.src_of(*e)],
				m[src.dst_of(*e)],
				pair_automaton_traits_t::
				series_convert(res.structure().series(),
					       src.series_of(*e)));
    }

    // Setup final transitions.
    for_all_const_final_states(f, src)
    {
      res.set_final(m[*f],
		    pair_automaton_traits_t::
		    series_convert(res.structure().series(),
				   src.get_final(*f)));
    }
  }

  //
  // Facade Functions
  //

  template <typename S, typename T>
  void
  ltl_to_pair(const Element<S, T>& ltl,
	      typename MUTE_TRAITS::ret& res)
  {
    do_ltl_to_pair(ltl, res);
  }

  template <typename S, typename T>
  typename MUTE_TRAITS::ret
  ltl_to_pair(const Element<S, T>& ltl)
  {
    typename MUTE_TRAITS::ret res = MUTE_TRAITS::make_automaton(ltl);

    do_ltl_to_pair(ltl, res);

    return res;
  }

# undef MUTE_TRAITS

} // ! vcsn

#endif // ! VCSN_ALGORITHMS_LTL_TO_PAIR_HXX
