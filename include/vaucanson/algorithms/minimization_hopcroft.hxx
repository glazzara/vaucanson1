// minimization_hopcroft.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_MINIMIZATION_HOPCROFT_HXX
# define VCSN_ALGORITHMS_MINIMIZATION_HOPCROFT_HXX

# include <vaucanson/algorithms/minimization_hopcroft.hh>
# include <vaucanson/algebra/implementation/semiring/numerical_semiring.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <algorithm>
# include <vector>
# include <queue>
# include <list>
# include <set>

namespace vcsn {

  // preconditions :
  //  - the input automaton is deterministic ;
  //  - the output automaton is well initialized with good sets ;
  //
  template <typename A, typename input_t, typename output_t>
  void
  do_hopcroft_minimization_det(const AutomataBase<A>&	,
			       output_t&		output,
			       const input_t&		input)
  {
    AUTOMATON_TYPES(input_t);
    typedef std::set<hstate_t>			delta_ret_t;

    int			max_states = 0;
    for_each_state(i, input)
      max_states = std::max(int(*i), max_states);
    ++max_states;

    // to avoid special case problem (one state initial and final ...)
    max_states = std::max(max_states, 2);

    const alphabet_t&
      alphabet_ (input.structure().series().monoid().alphabet());

    std::vector<letter_t>	alphabet(alphabet_.begin(),
					 alphabet_.end());
    unsigned			max_letters = alphabet.size();

    /*--------------------------.
    | To label the subsets of Q |
    `--------------------------*/
    unsigned max_partitions = 2;

    /*-----------------------------------------.
    | To manage efficiently the partition of Q |
    `-----------------------------------------*/
    std::vector<unsigned>				class_(max_states);
    std::vector<std::list<hstate_t> >			part(max_states);
    std::vector<typename std::list<hstate_t>::iterator>  place(max_states);

    /*------------------------.
    | To manage the splitting |
    `------------------------*/
    std::vector<unsigned>			split(max_states);
    std::vector<unsigned>			twin(max_states);

    /*-------------------------.
    | To have a list of (P, a) |
    `-------------------------*/
    typedef std::pair<unsigned, unsigned> pair_t;
    std::list<pair_t>   list;
    bool		**list_mat = new bool*[max_states];

    for (int p = 0; p < max_states; ++p)
      list_mat[p] = new bool[max_letters];

    /*-------------------------.
    | Initialize the partition |
    `-------------------------*/
    int nb_final = 0;

    for_each_state(p, input)
      {
	unsigned c = input.is_final(*p) ? 1 : 0;
	nb_final += c;
	class_[*p] = c;
	place[*p] = part[c].insert(part[c].end(), *p);
      }

    /*------------------------------.
    | Initialize the list of (P, a) |
    `------------------------------*/
    int source_subset =  (nb_final < max_states / 2) ? 1 : 0;

    for (unsigned e = 0; e < max_letters; ++e)
      {
	list.push_back(pair_t(source_subset, e));
	list_mat[source_subset][e] = true;
      }

    delta_ret_t				delta_ret;

    /*-------------------.
    | Initialize Inverse |
    `-------------------*/
    typedef std::set<hstate_t>**	mat_element_t;
    std::set<hstate_t>	***inverse = new mat_element_t[max_states];
    for (int i = 0; i < max_states; ++i)
      {
	inverse[i] = new std::set<hstate_t>*[max_letters];
	for (unsigned j = 0; j < max_letters; ++j)
	  inverse[i][j] = 0;
      }

    for_each_state(p, input)
      for (unsigned e = 0; e < max_letters; ++e)
	{
	  delta_ret.clear();
	  input.letter_deltac(delta_ret, *p, alphabet[e],
			      delta_kind::states());
	  for_all_(delta_ret_t, i, delta_ret)
	    {
	      if (inverse[*i][e] == 0)
		inverse[*i][e] = new std::set<hstate_t>();
	      inverse[*i][e]->insert(*p);
	    }
	}

    /*----------.
    | Main loop |
    `----------*/

    while (!list.empty())
      {
	/*----.
	| (a) |
	`----*/
	pair_t c = list.front();
	list.pop_front();
	unsigned p = c.first;
	unsigned a = c.second;
	list_mat[p][a] = false;

	/*----.
	| (b) |
	`----*/
	std::list<unsigned> met_class;
	for_all_(std::list<hstate_t>, b, part[p])
	  if (inverse[*b][a] != 0)
	    for_all_(std::set<hstate_t>, q, *inverse[*b][a])
	      {
		unsigned i = class_[*q];
		if (split[i] == 0)
		  {
		    split[i] = 1;
		    met_class.push_back(i);
		  }
		else
		  split[i]++;
	      }

	/*----.
	| (c) |
	`----*/
	std::queue<typename std::list<hstate_t>::iterator> to_erase;

	for_all_(std::list<hstate_t>, b, part[p])
	  {
	    if (inverse[*b][a] != 0)
	      for_all_(std::set<hstate_t>, q, *inverse[*b][a])
		{
		  unsigned i = class_[*q];
		  if (split[i] < part[i].size())
		    {
		      if (place[*q] == b)
			to_erase.push(b);
		      else
			{
			  if (twin[i] == 0)
			    {
			      twin[i] = max_partitions;
			      max_partitions++;
			    }

			  part[i].erase(place[*q]);
			  --split[i];;

			  place[*q] =
			    part[twin[i]].insert(part[twin[i]].end(), *q);
			  class_[*q] = twin[i];
			}
		    }
		}
	  }
	if (split[p] && split[p] < part[p].size())
	  {
	    while (!to_erase.empty())
	      {
		typename std::list<hstate_t>::iterator b=to_erase.front();
		part[p].erase(b);
		place[*b] =
		  part[max_partitions].insert(part[max_partitions].end(), *b);
		class_[*b] = max_partitions;

		to_erase.pop();
	      }
	    max_partitions++;
	  }

	/*----.
	| (d) |
	`----*/
	for_all_(std::list<unsigned>, b, met_class)
	  if (twin[*b] != 0)
	    {
	      for (unsigned e = 0; e < max_letters; ++e)
		{
		  if (list_mat[*b][e] == true)
		    {
		      list.push_back(pair_t(twin[*b], e));
		      list_mat[twin[*b]][e] = true;
		    }
		  else
		    {
		      if (part[*b].size() <= part[twin[*b]].size())
			{
			  list_mat[*b][e] = true;
			  list.push_back(pair_t(*b, e));
			}
		      else
			{
			  list_mat[twin[*b]][e] = true;
			  list.push_back(pair_t(twin[*b], e));
			}
		    }
		}
	    }
	for_all_(std::list<unsigned>, i, met_class)
	  {
	    split[*i] = 0;
	    twin[*i] = 0;
	  }

      }

    /*------------------------------------.
    | Construction of the ouput automaton |
    `------------------------------------*/
    std::vector<hstate_t>	out_states(max_partitions);

    // Create the states
    for (unsigned i = 0; i < max_partitions; ++i)
      if (part[i].size() != 0)
	{
	  // FIXME : here we can insert the set of states that are at
	  // the origin of it.
	  out_states[i] = output.add_state();
	}

    for (unsigned i = 0; i < max_partitions; ++i)
      if (part[i].size() != 0)
      {
	// Get the first state of the partition => each state has the
	// same behaviour
	hstate_t s = part[i].front();

	if (input.is_final(s))
	  output.set_final(out_states[i]);

	// Create the edges
	for (unsigned e = 0; e < max_letters; ++e)
	  {
	    delta_ret.clear();
	    std::set<unsigned> already_linked;
	    input.letter_deltac(delta_ret, s, alphabet[e],
				delta_kind::states());
	      for_all_(delta_ret_t, out, delta_ret)
	      {
		unsigned c = class_[*out];
		if (already_linked.find(c) == already_linked.end())
		  {
		    already_linked.insert(c);
		    output.add_letter_edge(out_states[i],
					   out_states[c],
					   alphabet[e]);
		  }
	      }
	  }
      }

    for_each_initial_state(i, input)
      output.set_initial(out_states[class_[*i]]);
  }

  template<typename A, typename T>
  Element<A, T>
  minimization_hopcroft(const Element<A, T>& a)
  {
    Element<A, T> output(a.structure());
    do_hopcroft_minimization_det(a.structure(), output, a);
    return output;
  }


  /*----------------------------.
  | hopcroft_minimization_undet |
  `----------------------------*/

  template <typename A, typename input_t, typename output_t>
  void
  do_quotient(const AutomataBase<A>&	a_set,
	      const algebra::NumericalSemiring&,
	      SELECTOR(bool),
	      output_t&			output,
	      const input_t&		input)
  {
    AUTOMATON_TYPES(input_t);
    typedef std::set<hstate_t>			     	      delta_ret_t;

    unsigned			max_states = 0;

    for_each_state(i, input)
      max_states = std::max(unsigned(*i), max_states);
    ++max_states;
    // to avoid special case problem (one state initial and final ...)
    max_states = std::max(max_states, 2u);

    const alphabet_t&	   alphabet_(input.series().monoid().alphabet());

    std::vector<letter_t>	alphabet(alphabet_.begin(),
					 alphabet_.end());
    unsigned			max_letters = alphabet.size();

    /*--------------------------.
    | To label the subsets of Q |
    `--------------------------*/
    unsigned max_partitions = 2;

    /*-----------------------------------------.
    | To manage efficiently the partition of Q |
    `-----------------------------------------*/
    std::vector<unsigned>				class_(max_states);
    std::vector<std::list<hstate_t> >			part(max_states);
    std::vector<typename std::list<hstate_t>::iterator> place(max_states);

    /*------------------------.
    | To manage the splitting |
    `------------------------*/
    std::vector<unsigned>			split(max_states);
    std::vector<unsigned>			twin(max_states);
    std::vector<bool>                           met_set(max_states);

    /*-------------------------.
    | To have a list of (P, a) |
    `-------------------------*/
    typedef std::pair<unsigned, unsigned> pair_t;
    std::list<pair_t>   list;
    bool		**list_mat = new bool*[max_states];

    for (unsigned p = 0; p < max_states; ++p)
      list_mat[p] = new bool[max_letters];

    /*-------------------------.
    | Initialize the partition |
    `-------------------------*/
    unsigned nb_final = 0;

    for (typename input_t::state_iterator p = input.states().begin();
	 p != input.states().end(); ++p)
      {
	unsigned c = input.is_final(*p) ? 1 : 0;
	nb_final += c;
	class_[*p] = c;
	place[*p] = part[c].insert(part[c].end(), *p);
      }

    /*------------------------------.
    | Initialize the list of (P, a) |
    `------------------------------*/
    unsigned source_subset =  (nb_final < max_states / 2) ? 1 : 0;

    for (unsigned e = 0; e < max_letters; ++e)
      {
	list.push_back(pair_t(source_subset, e));
	list_mat[source_subset][e] = true;
      }
    for (unsigned e = 0; e < max_letters; ++e)
      {
	list.push_back(pair_t(1-source_subset, 1));
	list_mat[1 - source_subset][e] = true;
      }

    delta_ret_t				delta_ret;

    /*-------------------.
    | Initialize Inverse |
    `-------------------*/
    typedef std::set<hstate_t>**	mat_element_t;
    std::set<hstate_t>	***inverse = new mat_element_t[max_states];
    for (unsigned i = 0; i < max_states; ++i)
      {
	inverse[i] = new std::set<hstate_t>*[max_letters];
	for (unsigned j = 0; j < max_letters; ++j)
	  inverse[i][j] = 0;
      }

    for (typename input_t::state_iterator p = input.states().begin();
	 p != input.states().end();
	 ++p)
      for (unsigned e = 0; e < max_letters; ++e)
	{
	  delta_ret.clear();
	  input.letter_deltac(delta_ret, *p, alphabet[e], delta_kind::states());
	  for (typename delta_ret_t::iterator i = delta_ret.begin();
	       i != delta_ret.end();
	       ++i)
	    {
	      if (inverse[*i][e] == 0)
		inverse[*i][e] = new std::set<hstate_t>();
	      inverse[*i][e]->insert(*p);
	    }
	}

    /*----------.
    | Main loop |
    `----------*/

    while (!list.empty())
      {
	/*----.
	| (a) |
	`----*/
	pair_t c = list.front();
	list.pop_front();
	unsigned p = c.first;
	unsigned a = c.second;
	list_mat[p][a] = false;
	met_set.clear();

	//	std::cerr << "Part by : " << p << "," << a << std::endl;
	/*----.
	| (b) |
	`----*/
	std::list<unsigned> met_class;
	for (typename std::list<hstate_t>::iterator b = part[p].begin();
	     b != part[p].end(); ++b)
	  if (inverse[*b][a] != 0)
	    for (typename std::set<hstate_t>::iterator q = inverse[*b][a]->begin();
		 q != inverse[*b][a]->end();
		 ++q)
	      {
		if(!met_set[*q])
		  {
		    met_set[*q]=true;
		    unsigned i = class_[*q];
		    if (split[i] == 0)
		      {
			split[i] = 1;
			met_class.push_back(i);
		      }
		    else
		      split[i]++;
		  }
	      }

	/*----.
	| (c) |
	`----*/
	std::queue<typename std::list<hstate_t>::iterator> to_erase;

	for (typename std::list<hstate_t>::iterator b = part[p].begin();
	     b != part[p].end(); ++b)
	  {
	    if (inverse[*b][a] != 0)
	      for (typename std::set<hstate_t>::iterator q = inverse[*b][a]->begin();
		   q != inverse[*b][a]->end();
		   ++q)
		if (met_set[*q])
		  {
		    //		  std::cerr << "predecesseur de " << *b << " : " << *q << std::endl;
		    met_set[*q]=false;
		    unsigned i = class_[*q];
		    if (split[i] < part[i].size())
		      {
			if (place[*q] == b)
			  to_erase.push(b);
			else
			  {
			    if (twin[i] == 0)
			      {
				twin[i] = max_partitions;
				max_partitions++;
			      }

			    part[i].erase(place[*q]);
			    --split[i];;

			    place[*q] = part[twin[i]].insert(part[twin[i]].end(), *q);
			    class_[*q] = twin[i];
			  }
		      }
		  }
	  }
	if (split[p] && split[p] < part[p].size())
	  {
	    while (!to_erase.empty())
	      {
		typename std::list<hstate_t>::iterator b=to_erase.front();
		part[p].erase(b);
		place[*b] = part[max_partitions].insert(part[max_partitions].end(), *b);
		class_[*b] = max_partitions;

		to_erase.pop();
	      }
	    max_partitions++;
	  }

	/*----.
	| (d) |
	`----*/
	for (typename std::list<unsigned>::iterator b = met_class.begin();
	     b != met_class.end();
	     ++b)
	  if (twin[*b] != 0)
	    {
	      for (unsigned e = 0; e < max_letters; ++e)
		{
		  if (list_mat[*b][e] == true)
		    {
		      list.push_back(pair_t(twin[*b], e));
		      list_mat[twin[*b]][e] = true;
		    }
		  else
		    {
		      if (part[*b].size() <= part[twin[*b]].size())
			{
			  list_mat[*b][e] = true;
			  list.push_back(pair_t(*b, e));
			}
		      else
			{
			  list_mat[twin[*b]][e] = true;
			  list.push_back(pair_t(twin[*b], e));
			}
		    }
		}
	    }
	for (typename std::list<unsigned>::iterator i = met_class.begin();
	     i != met_class.end();
	     ++i)
	  {
	    split[*i] = 0;
	    twin[*i] = 0;
	  }

      }

    /*------------------------------------.
    | Construction of the ouput automaton |
    `------------------------------------*/
    std::vector<hstate_t>	out_states(max_partitions);

    // Create the states
    for (unsigned i = 0; i < max_partitions; ++i)
      if (part[i].size() != 0)
	{
	  // FIXME : log history ?
	  out_states[i] = output.add_state();
	}

    for (unsigned i = 0; i < max_partitions; ++i)
      if (part[i].size() != 0)
      {
	// Get the first state of the partition => each state has the
	// same behaviour
	hstate_t s = part[i].front();

// 	for (typename std::list<hstate_t>::const_iterator j = part[i].begin();
// 	     j != part[i].end();
// 	     ++j)
// 	  if (input.is_initial(s))
// 	    {
// 	      output.set_initial(out_states[i]);
// 	      break;
// 	    }
	if (input.is_final(s))
	  output.set_final(out_states[i]);

	// Create the edges
	for (unsigned e = 0; e < max_letters; ++e)
	  {
	    delta_ret.clear();
	    std::set<unsigned> already_linked;
	    input.letter_deltac(delta_ret, s, alphabet[e], delta_kind::states());
	    for (typename delta_ret_t::iterator out = delta_ret.begin();
		 out != delta_ret.end();
		 ++out)
	      {
		unsigned c = class_[*out];
		if (already_linked.find(c) == already_linked.end())
		  {
		    already_linked.insert(c);
		    output.add_letter_edge(out_states[i], out_states[c], alphabet[e]);
		  }
	      }
	  }
      }
    //set initial states

    for (typename input_t::initial_iterator i = input.initial().begin();
	 i != input.initial().end();
	 ++i)
      output.set_initial(out_states[class_[*i]]);
  }

  template <class S, class T,
	    typename A, typename input_t, typename output_t>
  void
  do_quotient(const AutomataBase<A>& a_set,
	      const S&		      ,
	      const T&,
	      output_t&              output,
	      const input_t&         input)
  {
    AUTOMATON_TYPES(input_t);
    using namespace std;

    /*-------------------------------------
      Declare data structures and variables
      -------------------------------------*/
    typedef set<hedge_t>                       set_edges_t;
    typedef set<hstate_t>                      set_states_t;
    typedef set<semiring_elt_t>                set_semiring_elt_t;
    typedef vector<semiring_elt_t>             vector_semiring_elt_t;
    typedef pair<unsigned, letter_t>           pair_class_letter_t;
    typedef pair<hstate_t, semiring_elt_t>     pair_state_semiring_elt_t;
    typedef set<pair_state_semiring_elt_t>     set_pair_state_semiring_elt_t;

    set<unsigned>                              met_classes;
    set_edges_t                                edges_comming, edges_leaving;
    queue<pair_class_letter_t>                 the_queue;
    vector<vector<set_pair_state_semiring_elt_t> >   inverse;
    series_set_elt_t                               series_identity    = input.series().zero_;
    semiring_elt_t                             weight_zero       = input.series().semiring().wzero_;
    monoid_elt_t                               monoid_identity   = input.series().monoid().empty_;
    const alphabet_t&	                       alphabet(input.series().monoid().alphabet());
    unsigned                                   max_partition, max_letters, pos;

    pos              = 0;
    max_partition    = 0;
    max_letters      = alphabet.size();
    map<letter_t, unsigned> pos_of_letter;

    unsigned			max_states = 0;
    for_each_state(q, input)
      {
	max_states = std::max(*q, max_states);
      }
    ++max_states;
    // to avoid special case problem (one state initial and final ...)
    max_states = std::max(max_states, 2u);

    for_each_letter(a, alphabet){
      pos_of_letter[*a] = pos;
      pos++;
    }

    inverse.resize(max_states);

    set_states_t           states_visited;
    set_semiring_elt_t           semiring_had_class;
    vector<set_states_t>   classes(max_states);
    vector<unsigned>       class_of_state(max_states);
    vector_semiring_elt_t        old_weight(max_states), class_of_weight(max_states), val(max_states);

    for(int i = 0; i < max_states; i++)
      inverse[i].resize(max_states);

    for_each_state(q, input)
      {
	for_each_letter(a, alphabet)
	  {
	    for_each_const_(set_states_t, r, states_visited)
	      old_weight[*r] = weight_zero;
	    states_visited.clear();
	    edges_comming.clear();

	    input.letter_rdeltac(edges_comming, *q, *a, delta_kind::edges());

	    for_each_const_(set_edges_t, e, edges_comming)
	      {
		hstate_t p = input.origin_of(*e);
		if (states_visited.find(p) != states_visited.end())
		  inverse[*q][pos_of_letter[*a]].erase(pair_state_semiring_elt_t(p, old_weight[p]));
		else
		  states_visited.insert(p);

		old_weight[p] += input.series_of(*e).get(*a);
		inverse[*q][pos_of_letter[*a]].insert(pair_state_semiring_elt_t(p, old_weight[p]));
	      }
	  }
      }

    /*-------------------------------------------------------------
      Initialize the partition with 2 classes : final and non-final
      -------------------------------------------------------------*/
    bool         empty = true;
    unsigned     class_non_final;

    for_each_state(q, input)
      {
	if (!input.is_final(*q))
	  {
	    if (empty == true)
	      {
		empty = false;
		class_non_final = max_partition;
		max_partition++;
	      }
	    classes[class_non_final].insert(*q);
	    class_of_state[*q] = class_non_final;
	  }
	else
	  {
	    semiring_elt_t w = input.get_final(*q).get(monoid_identity);
	    if (semiring_had_class.find(w) == semiring_had_class.end())
	      {
		semiring_had_class.insert(w);
		classes[max_partition].insert(*q);
		class_of_weight[w] = max_partition;
		class_of_state[*q] = max_partition;
		max_partition++;
	      }
	    else
	      {
		classes[class_of_weight[w]].insert(*q);
		class_of_state[*q] = class_of_weight[w];
	      }
	  }
      }

    /*--------------------------------------------------
      Initialize the queue with pairs <class_id, letter>
      --------------------------------------------------*/
    for (int i = 0; i < max_partition; i++)
	for_each_letter(a, alphabet)
	  the_queue.push(pair_class_letter_t(i, *a));

    /*-------------
      The main loop
      -------------*/
    unsigned old_max_partition = max_partition;

    while(!the_queue.empty())
      {
	pair_class_letter_t pair = the_queue.front();
	the_queue.pop();
	val.clear();
	met_classes.clear();

	for_each_const_(set_states_t, q, classes[pair.first])	// First, calculcate val[state] and note met_classes
	  {
	    for_each_const_(set_pair_state_semiring_elt_t, pair_, inverse[*q][pos_of_letter[pair.second]])
	      {
		unsigned  state = (*pair_).first;
		if (met_classes.find(class_of_state[state]) == met_classes.end())
		  met_classes.insert(class_of_state[state]);
		val[state] += (*pair_).second;
	      }
	  }

	for_each_const_(set<unsigned>, class_id, met_classes) 	// Next,for each met class, do the partition.
	  {
	    if (classes[*class_id].size() == 1)
	      continue;

	    queue<hstate_t>   to_erase;
	    semiring_elt_t          first_val, next_val;
	    first_val = val[*(classes[*class_id].begin())];
	    class_of_weight.clear();
	    semiring_had_class.clear();

	    for_each_const_(set_states_t, p, classes[*class_id])
	      {
		next_val = val[*p];
		if (next_val != first_val) // This state must be moved to another class !
		  {
		    if (semiring_had_class.find(next_val) == semiring_had_class.end()) // Must create a new class
		      {
			classes[max_partition].insert(*p);
			class_of_state[*p] = max_partition;
			semiring_had_class.insert(next_val);
			class_of_weight[next_val] = max_partition;
			max_partition++;
		      }
		    else
		      {
			classes[class_of_weight[next_val]].insert(*p);
			class_of_state[*p] = class_of_weight[next_val];
		      }
		    to_erase.push(*p);
		  }
	      }

       	    while(!to_erase.empty())
	      {
		hstate_t state_to_erase = to_erase.front();
		to_erase.pop();
		classes[*class_id].erase(state_to_erase);
	      }

	    for (int i = old_max_partition; i < max_partition; i++) // Push pairs <new_class_id, letter> into the queue
	      for_each_letter(b, alphabet)
		the_queue.push(pair_class_letter_t(i, *b));

	    old_max_partition = max_partition;
	  }
      }

    /*----------------
      Form the output
      ----------------*/
    typedef map<unsigned, series_set_elt_t> map_class_series_set_elt_t;
    map_class_series_set_elt_t series_of;

    for(int i = 0; i < max_partition; i++) // Add states
      {
	hstate_t p = output.add_state();
	hstate_t a_state = *classes[i].begin();
	series_set_elt_t a_series = series_identity;

	for_each_const_(set_states_t, state, classes[i])
	  if(input.is_initial(*state))
	    a_series += input.get_initial(*state);

	output.set_initial(p, a_series);

	if (input.is_final(a_state))
	  output.set_final(p, input.get_final(a_state));
      }

    for(int i = 0; i < max_partition; i++) // Add edges
      {
	series_of.clear();
	edges_leaving.clear();
	input.deltac(edges_leaving, *classes[i].begin(), delta_kind::edges());

	for_each_const_(set_edges_t, e, edges_leaving)
	    series_of[class_of_state[input.aim_of(*e)]] += input.series_of(*e);

	for_each_const_(map_class_series_set_elt_t, it, series_of)
	    output.add_series_edge(i, (*it).first, (*it).second);
      }
  }

  template<typename A, typename T>
  Element<A, T>
  quotient(const Element<A, T>& a)
  {
    typedef Element<A, T> auto_t;
    AUTOMATON_TYPES(auto_t);
    Element<A, T> output(a.structure());
    do_quotient(a.structure(), a.structure().series().semiring(),
		SELECT(semiring_elt_value_t), output, a);
    return output;
  }

} // vcsn

#endif // VCSN_ALGORITHMS_MINIMIZATION_HOPCROFT_HXX
