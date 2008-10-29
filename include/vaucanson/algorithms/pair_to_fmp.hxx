// pair_to_fmp.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_PAIR_TO_FMP_HXX
# define VCSN_ALGORITHMS_PAIR_TO_FMP_HXX

# include <vaucanson/algorithms/pair_to_fmp.hh>

namespace vcsn
{
// Helper to write lighter code.
# define MUTE_TRAITS mute_pair_to_fmp<S, T>

  template <typename S, typename T>
  inline typename MUTE_TRAITS::ret
  MUTE_TRAITS::
  make_automaton(const typename MUTE_TRAITS::ret_first_alphabet_t& A,
		 const typename MUTE_TRAITS::ret_second_alphabet_t& B)
  {
    semiring_t semiring;
    first_monoid_t fM(A);
    second_monoid_t sM(B);
    ret_monoid_t freemonoidproduct(fM, sM);
    typename ret::series_set_t series(semiring, freemonoidproduct);

    return ret(Automata<typename ret::series_set_t>(series));
  }

  template <typename S, typename T>
  inline typename MUTE_TRAITS::ret
  MUTE_TRAITS::
  make_automaton(const Element<S, T>& aut)
  {
    ret_first_alphabet_t fA = alphabet_traits_t::first_projection(aut.
	series().monoid().alphabet());
    ret_second_alphabet_t sA = alphabet_traits_t::second_projection(aut.
	series().monoid().alphabet());

    return make_automaton(fA, sA);
  }

  template <typename S, typename T>
  inline typename MUTE_TRAITS::ret::series_set_elt_t
  MUTE_TRAITS::
  series_convert(const typename MUTE_TRAITS::ret_series_set_t& series,
		 const typename MUTE_TRAITS::automaton_t::
		 series_set_elt_t& ss)
  {
    typedef typename MUTE_TRAITS::automaton_t::series_set_elt_t
	series_set_elt_t;

    typename ret::series_set_elt_t R(series);

    for_all_const_(series_set_elt_t::support_t, it, ss.supp())
    {
      R.assoc(std::make_pair(word_traits_t::first_projection(*it),
			     word_traits_t::second_projection(*it)),
	      ss.get(*it));
    }

    return R;
  }

  template <typename S, typename T>
  void
  do_pair_to_fmp(const Element<S, T>& src,
		 typename MUTE_TRAITS::ret& res)
  {
    TIMER_SCOPED("pair_to_fmp");

    // Type helpers.
    typedef typename MUTE_TRAITS::automaton_t automaton_t;
    typedef MUTE_TRAITS fmp_traits_t;
    typedef typename fmp_traits_t::ret res_t;
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
		      fmp_traits_t::
		      series_convert(res.structure().series(),
				     src.get_initial(*i)));
    }

    // Setup normal transitions.
    for_all_const_transitions(e, src)
    {
      res.add_series_transition(m[src.src_of(*e)],
				m[src.dst_of(*e)],
				fmp_traits_t::
				series_convert(res.structure().series(),
					       src.series_of(*e)));
    }

    // Setup final transitions.
    for_all_const_final_states(f, src)
    {
      res.set_final(m[*f],
		    fmp_traits_t::
		    series_convert(res.structure().series(),
				   src.get_final(*f)));
    }
  }

  //
  // Facade Functions
  //

  template <typename S, typename T>
  void
  pair_to_fmp(const Element<S, T>& aut,
	      typename MUTE_TRAITS::ret& res)
  {
    do_pair_to_fmp(aut, res);
  }

  template <typename S, typename T>
  typename MUTE_TRAITS::ret
  pair_to_fmp(const Element<S, T>& aut)
  {
    typename MUTE_TRAITS::ret res = MUTE_TRAITS::make_automaton(aut);

    do_pair_to_fmp(aut, res);

    return res;
  }

# undef MUTE_TRAITS

} // ! vcsn

#endif // ! VCSN_ALGORITHMS_PAIR_TO_FMP_HXX
