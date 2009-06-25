// minimization_moore.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_MINIMIZATION_MOORE_HXX
# define VCSN_ALGORITHMS_MINIMIZATION_MOORE_HXX

# include <vaucanson/algorithms/minimization_moore.hh>
# include <vaucanson/algorithms/complete.hh>
# include <vaucanson/algorithms/transpose.hh>

# ifndef VCSN_NDEBUG
#  include <vaucanson/algorithms/is_deterministic.hh>
# endif // ! VCSN_NDEBUG

# include <vaucanson/automata/concept/handlers.hh>
# include <vaucanson/automata/concept/delta_kind.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/misc/contract.hh>

# include <map>
# include <set>
# include <vector>

// Useful macros for Moore's minimization.

// Iterator on a list of groups.
# define for_all_groups(I, P)						\
  for (typename groupid_to_group_t::iterator I = ((P).begin()); I != (P).end(); ++I)

// Iterator on state in a group. We don't iterate on the first not
// processed state.
# define for_all_state_in_groups(I, P)					\
  for (typename group_t::iterator I = ++((P).begin()); I != (P).end(); ++I)

namespace vcsn {

  /*-------------------.
  | minimization_moore |
  `-------------------*/
  // precondition : the input automaton is deterministic or
  // co-deterministic according to Transposed
  template<typename A, typename AI, bool Transposed>
  void
  do_minimization_moore(const Element<A, AI>& input, Element<A, AI>& output)
  {
    BENCH_TASK_SCOPED("minimization_moore");
    typedef Element<A, AI> automaton_t;
    AUTOMATON_TYPES(automaton_t);
    AUTOMATON_FREEMONOID_TYPES(automaton_t);
    using std::map;
    using std::vector;
    using std::set;

    // Consts.

    const hstate_t	NullState;
    const hstate_t	NullGroup;
    const alphabet_t&	alphabet (input.series().monoid().alphabet());

    // Typedefs.

    typedef int					letterid_t;
    typedef int					groupid_t;

    typedef set<hstate_t>			group_t;
    typedef vector<group_t>			groupid_to_group_t;

    typedef vector<hstate_t>			letterid_to_state_t;

    typedef map<hstate_t, letterid_to_state_t>	state_to_letterid_to_state_t;

    typedef map<hstate_t, groupid_t>		state_to_groupid_t;
    typedef map<letter_t,  letterid_t>		letter_to_letterid_t;

    /*---------------.
    | Initialization |
    `---------------*/

    precondition(input.exists());

    groupid_to_group_t	groupid_to_group(input.states().size());

    state_to_groupid_t state_to_groupid;
    state_to_groupid[NullState] = NullGroup;

    letter_to_letterid_t letter_to_letterid;
    int	letter_count = 0;
    for_all_const_letters(iletter, alphabet)
      letter_to_letterid[*iletter] = letter_count++;

    state_to_letterid_to_state_t aut_view;
    for_all_const_states(istate, input)
    {
      aut_view[*istate] = letterid_to_state_t(letter_count, NullState);
      if ((not Transposed and input.is_final(*istate)) or
	  (Transposed and input.is_initial(*istate)))
      {
	groupid_to_group[0].insert(*istate);
	state_to_groupid[*istate] = 0;
      }
      else
      {
	groupid_to_group[1].insert(*istate);
	state_to_groupid[*istate] = 1;
      }
    }

    for_all_const_states(istate, input)
    {
      for_all_const_(letter_to_letterid_t, iletter, letter_to_letterid)
      {
	bool empty = true;
        hstate_t first;
	if (not Transposed)
        {
          for (delta_iterator t(input.value(), *istate);
               ! t.done() && empty;
               t.next())
          {
            monoid_elt_t w(input.series_of(*t).structure().monoid(), iletter->first);
            if (input.series_of(*t).get(w) != input.series().semiring().wzero_)
            {
              empty = false;
              first = input.dst_of(*t);
              break;
            }
          }
        }
	else
        {
          for (rdelta_iterator t(input.value(), *istate);
               ! t.done() && empty;
               t.next())
          {
            monoid_elt_t w(input.series_of(*t).structure().monoid(), iletter->first);
            if (input.series_of(*t).get(w) != input.series().semiring().wzero_)
            {
              empty = false;
              first = input.src_of(*t);
              break;
            }
          }
        }
	if (not empty)
	  aut_view[*istate][iletter->second] = first;
      }
    }


    /*-----.
    | Loop |
    `-----*/

    int	 last_group = 1;
    for (bool group_modified = true; group_modified;)
    {
      group_modified = false;
      for_all_groups(igroup, groupid_to_group)
      {
	if (igroup->empty())
	  break;

	hstate_t first_state = *(igroup->begin());
	bool	 group_created = false;

	for_all_state_in_groups(istate, *igroup)
	{
	  int i;
	  for (i = 0; i < letter_count; ++i)
	    if (state_to_groupid[aut_view[first_state][i]] !=
		state_to_groupid[aut_view[*istate][i]])
	      break;
	  if (i != letter_count)
	  {
	    typename group_t::iterator istate_save = istate;

	    istate_save--;
	    if (group_created == false)
	    {
	      last_group++;
	      group_created = true;
	      group_modified = true;
	    }
	    groupid_to_group[last_group].insert(*istate);
	    state_to_groupid[*istate] = last_group;
	    igroup->erase(*istate);
	    istate = istate_save;
	  }
	}
      }
    }


    /*-----------------------.
    | Automaton construction |
    `-----------------------*/

    std::vector<hstate_t> new_states(last_group + 1);

    // Create all states.
    for (int i = 0; i <= last_group; ++i)
      new_states[i] = output.add_state();

    // Create all transitions.
    for (int i = 0; i <= last_group; ++i)
    {
      hstate_t repres = *(groupid_to_group[i].begin());

      for_all_const_(letter_to_letterid_t, iletter, letter_to_letterid)
	if (aut_view[repres][iletter->second] != NullState)
	{
	  if (not Transposed)
	    output.add_letter_transition(new_states[i],
					 new_states[state_to_groupid
						    [aut_view[repres]
						     [iletter->second]]],
					 iletter->first);
	  else
	    output.add_letter_transition(new_states[state_to_groupid
						    [aut_view[repres]
						     [iletter->second]]],
					 new_states[i],
					 iletter->first);
	}
    }

    // Setting initial and final states.
    if (not Transposed)
    {
      output.set_final(new_states[0]);
      output.set_initial(new_states[state_to_groupid[*input.initial().begin()]]);
    }
    else
    {
      output.set_initial(new_states[0]);
      output.set_final(new_states[state_to_groupid[*input.final().begin()]]);
    }

  }


  template<typename A, typename AI>
  void
  minimization_moore_here(Element<A, AI>& a)
  {
    precondition(is_deterministic(a));
    precondition(is_complete(a));
    Element<A, AI> output(a.structure());
    do_minimization_moore<A, AI, false>(a, output);
    a = output;
  }


  template<typename A, typename AI>
  Element<A, AI>
  minimization_moore(const Element<A, AI>& a)
  {
    precondition(is_deterministic(a));
    precondition(is_complete(a));
    Element<A, AI> output(a.structure());
    do_minimization_moore<A, AI, false>(a, output);
    return output;
  }

  template<typename A, typename AI>
  void
  co_minimization_moore_here(Element<A, AI>& a)
  {
    precondition(is_deterministic(transpose(a)));
    precondition(is_complete(transpose(a)));
    Element<A, AI> output(a.structure());
    do_minimization_moore<A, AI, true>(a, output);
    a = output;
  }


  template<typename A, typename AI>
  Element<A, AI>
  co_minimization_moore(const Element<A, AI>& a)
  {
    precondition(is_deterministic(transpose(a)));
    precondition(is_complete(transpose(a)));
    Element<A, AI> output(a.structure());
    do_minimization_moore<A, AI, true>(a, output);
    return output;
  }

} // vcsn

// Prevent potential conflicts.
# undef for_all_groups
# undef for_all_state_in_groups


#endif // ! VCSN_ALGORITHMS_MINIMIZATION_MOORE_HXX
