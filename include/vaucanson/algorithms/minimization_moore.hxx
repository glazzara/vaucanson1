// minimization_moore.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_MINIMIZATION_MOORE_HXX
# define VCSN_ALGORITHMS_MINIMIZATION_MOORE_HXX

# include <vaucanson/algorithms/minimization_moore.hh>

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
  for (groupid_to_group_t::iterator I = ((P).begin()); I != (P).end(); ++I)

// Iterator on state in a group. We don't iterate on the first not
// processed state.
# define for_all_state_in_groups(I, P)					\
  for (group_t::iterator I = ++((P).begin()); I != (P).end(); ++I)

namespace vcsn {

  /*-------------------.
  | minimization_moore |
  `-------------------*/
  // preconditions :
  // - the input automaton is deterministic or co-deterministic
  //   according to Transposed;
  // - the output automaton is well initialized with good sets ;
  //

  template<typename A, typename T, bool Transposed>
  void
  do_minimization_moore(const Element<A, T>& input, Element<A, T>& output)
  {
    TIMER_SCOPED("minimization_moore");
    typedef Element<A, T> automata_type;
    AUTOMATON_TYPES(automata_type);
    AUTOMATON_FREEMONOID_TYPES(automata_type);
    using std::map;
    using std::vector;
    using std::set;

    // Consts.

    const hstate_t	NullState = -1;
    const hstate_t	NullGroup = -1;
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

    // Variables.

    letter_to_letterid_t			letter_to_letterid;
    state_to_groupid_t				state_to_groupid;
    group_t					delta_ret;

    // Store successors if non-inverted, predecessors otherwise.
    state_to_letterid_to_state_t		aut_view;

    groupid_to_group_t	groupid_to_group(input.states().size());

    int						letter_count = 0;
    int						i;

    /*---------------.
    | Initialization |
    `---------------*/

    precondition(input.exists());

    state_to_groupid[NullState] = NullGroup;

    for_all_letters(iletter, alphabet)
      letter_to_letterid[*iletter] = letter_count++;

    for_all_states(istate, input)
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

    for_all_states(istate, input)
    {
      for_all_const_(letter_to_letterid_t, iletter, letter_to_letterid)
      {
	delta_ret.clear();
	if (not Transposed)
	  input.letter_deltac(delta_ret, *istate, iletter->first,
			      delta_kind::states());
	else
	  input.letter_rdeltac(delta_ret, *istate, iletter->first,
			       delta_kind::states());
	if (not delta_ret.empty())
	  aut_view[*istate][iletter->second] = *delta_ret.begin();
      }
    }


    /*-----.
    | Loop |
    `-----*/

    int	 last_group = 1;
    bool group_modified;

    do
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
	  for (i = 0; i < letter_count; ++i)
	    if (state_to_groupid[aut_view[first_state][i]] !=
		state_to_groupid[aut_view[*istate][i]])
	      break;
	  if (i != letter_count)
	  {
	    group_t::iterator istate_save = istate;

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
    while (group_modified);


    /*-----------------------.
    | Automaton construction |
    `-----------------------*/

    std::vector<hstate_t> new_states(last_group + 1);

    // Create all states.
    for (i = 0; i <= last_group; ++i)
      new_states[i] = output.add_state();

    // Create all transitions.
    for (i = 0; i <= last_group; ++i)
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


  template<typename A, typename T>
  void
  minimization_moore_here(Element<A, T>& a)
  {
    Element<A, T> output(a.structure());
    do_minimization_moore<A, T, false>(a, output);
    a = output;
  }


  template<typename A, typename T>
  Element<A, T>
  minimization_moore(const Element<A, T>& a)
  {
    Element<A, T> output(a.structure());
    do_minimization_moore<A, T, false>(a, output);
    return output;
  }

  template<typename A, typename T>
  void
  co_minimization_moore_here(Element<A, T>& a)
  {
    Element<A, T> output(a.structure());
    do_minimization_moore<A, T, true>(a, output);
    a = output;
  }


  template<typename A, typename T>
  Element<A, T>
  co_minimization_moore(const Element<A, T>& a)
  {
    Element<A, T> output(a.structure());
    do_minimization_moore<A, T, true>(a, output);
    return output;
  }

} // vcsn

// Prevent potential conflicts.
# undef for_all_groups
# undef for_all_state_in_groups


#endif // ! VCSN_ALGORITHMS_MINIMIZATION_MOORE_HXX
