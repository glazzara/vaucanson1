// minimization_moore.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003,2004 The Vaucanson Group.
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
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

#ifndef VCSN_ALGORITHMS_MINIMIZATION_MOORE_HXX
# define VCSN_ALGORITHMS_MINIMIZATION_MOORE_HXX


# include <vaucanson/config/system.hh>
# include <map>
# include <set>
# include <queue>
# include <vector>
# include <list>
# include <utility>
# include <stack>
# include <algorithm>
# include <vaucanson/algorithms/trim.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/misc/contract.hh>

// Usefull macros for Moore's minimization algorithm.

// Iterator on partitions (begin + 1 because we dont interate on final state
// partition).
# define for_each_partition(I, P) \
  PARTITIONS_END = P.end(); \
  for (partitions_t::iterator I = P.begin() + 1; I != PARTITIONS_END; ++I)

// Iterator on state in partitions.
# define for_each_state_in_partition(I, P) \
  PARTITION_END = P.end(); \
  for (partition_t::iterator I = P.begin(); I != PARTITION_END; ++I)


namespace vcsn {

  /*-------------------.
  | minimization_moore |
  `-------------------*/
  // preconditions :
  //  - the input automaton is deterministic ;
  //  - the output automaton is well initialized with good sets ;
  //

  template<typename A, typename T>
  void
  do_minimization_moore(const Element<A, T>& input, Element<A, T>& output)
  {
    typedef Element<A, T> automata_type;
    AUTOMATON_TYPES(automata_type);

    // Used const.

    const int						NO_EDGE = -1;

    // Used typedefs.

    typedef std::set<hstate_t>				partition_t;
    typedef std::vector<partition_t>			partitions_t;

    typedef std::vector<hstate_t>			state_vect_t;
    typedef std::vector<int>				int_vect_t;
    typedef std::map<hstate_t, state_vect_t>		full_map_t;
    typedef std::map<hstate_t, int_vect_t>		state_to_group_map_t;
    typedef std::map<label_t, int>			letter_map_t;

    // Used iterators.

    partition_t::iterator		PARTITION_END;
    partitions_t::iterator		PARTITIONS_END;
    typename letter_map_t::iterator	current_letter;
    partition_t::iterator		ref;
    partition_t::iterator		elt;

    // Used structures.

    //Map to count letters used in alphabet.
    letter_map_t			letter_map;
    //Map a state to a group index.
    std::map<hstate_t, int>		group_map;

    // Full array of the input automaton.
    full_map_t				full_map;
    // Local group array for the automaton.
    state_to_group_map_t		local_map;

    // Partitions.
    partitions_t			partitions(input.states().size());

    // Used globals.
    unsigned				letter_count = 0;
    unsigned				partition_count = 1;
    bool				partition_created = false;
    bool				partition_modified;
    hstate_t				initial_state;

    // Used counting variables.
    int					current_partition;
    int					i, j;
    int					iter;

    // Special state used for map initialization.
    hstate_t				NullState = -1;


    /*---------------.
    | Initialization |
    `---------------*/

    precondition(input.exists());
    
    for_each_edge(e, input)
      {
	if (letter_map.find(input.label_of(*e)) == letter_map.end())
	  letter_map[input.label_of(*e)] = letter_count++;
      }

    letter_count = letter_map.size();
    for_each_state(s, input)
      {
	if (input.is_initial(*s))
	  initial_state = *s;
	full_map[*s] = state_vect_t(letter_count, NullState);
	local_map[*s] = int_vect_t(letter_count, NO_EDGE);
	if (input.is_final(*s))
	  {
	    partitions[0].insert(*s);
	    group_map[*s] = 0;
	  }
	else
	  {
	    partitions[1].insert(*s);
	    group_map[*s] = 1;
	  }
      }

    for_each_edge(ee, input)
      {
	full_map[input.origin_of(*ee)][letter_map[input.label_of(*ee)]]
	  = input.aim_of(*ee);
      }

    /*-----.
    | Loop |
    `-----*/

    do
      {
	partition_modified = false;
 	current_partition = 0;
   	for_each_partition(p, partitions)
	  {
	    // Quit iteration when all used partitions were computed.
	    if (current_partition++ > partition_count)
	      break;
	    for_each_state_in_partition(sp, (*p))
	      {
		for (i = 0; i < letter_count; ++i)
		  if (full_map[*sp][i] == NullState)
		    local_map[*sp][i] = NO_EDGE;
		  else
		    local_map[*sp][i] = group_map[full_map[*sp][i]];
	      }

	    partition_created = false;

	    iter = 0;
  	    for_each_state_in_partition(li, (*p))
	      {
		if (!iter++)
		  ref = li;
   		if (local_map[*ref] != local_map[*li])
		  {
		    if (partition_created == false)
		      {
			partition_count++;
			partition_created = true;
			partition_modified = true;
		      }
		    partitions[partition_count].insert(*li);
		    group_map[*li] = partition_count;
		    (*p).erase(*li);
		  }
	      }
	  }
      }
    while (partition_modified);


    /*-----------------------.
    | Automaton construction |
    `-----------------------*/

    std::vector<hstate_t> sv(partition_count + 1);

    // Create all states.
     for (i = 0; i <= partition_count; ++i)
       sv[i] = output.add_state();
    output.set_final(sv[0]);
    output.set_initial(sv[group_map[initial_state]]);

    // Create all edges.
    for (i = 0; i <= partition_count; ++i)
      {
 	elt = partitions[i].begin();
	letter_count = 0;
	current_letter = letter_map.begin();
	for (j = 0; j < letter_map.size(); ++j)
	  {
 	    if (full_map[*elt][j] != NullState)
	      {
		// Little trick to go to the correct iterator on letter map.
		while (j > letter_count)
		  {
		    current_letter++;
		    letter_count++;
		  }
		output.add_edge(sv[i],
				sv[group_map[full_map[*elt][j]]],
				current_letter->first);
	      }
	  }
      }
  }

  
  template<typename A, typename T>
  void
  minimization_moore_here(Element<A, T>& a)
  {
    Element<A, T> output(a.set());
    do_minimization_moore(a, output);
    a = output;
  }


  template<typename A, typename T>
  Element<A, T>
  minimization_moore(const Element<A, T>& a)
  {
    Element<A, T> output(a.set());
    do_minimization_moore(a, output);
    return output;
  }

} // vcsn

// Prevent potential conflicts.
# undef for_each_partition
# undef for_each_state_in_partition


#endif // VCSN_ALGORITHMS_MINIMIZATION_MOORE_HXX
