// hopcroft_minimization.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey
// and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_ALGORITHMS_HOPCROFT_MINIMIZATION_HXX
# define VCSN_ALGORITHMS_HOPCROFT_MINIMIZATION_HXX

# include <map>
# include <set>
# include <queue>
# include <list>

# include <vaucanson/algorithms/trim.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/history.hh>

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
    typedef typename input_t::series_t			    series_t;
    typedef typename series_t::monoid_t			    monoid_t;

    // FIXME : here we assume monoid is a free monoid -> concept checking ?
    typedef typename monoid_t::alphabet_t	alphabet_t;
    typedef typename alphabet_t::letter_t	letter_t;
    
    typedef std::set<hstate_t>			delta_ret_t;

    int			max_states = 0;
    for (typename input_t::state_iterator i = input.states().begin();
	 i != input.states().end();
	 ++i)
      max_states = std::max(int(*i), max_states);
    ++max_states;

    // to avoid special case problem (one state initial and final ...)
    max_states = std::max(max_states, 2);

    const alphabet_t&	   alphabet_(input.set().series().monoid().alphabet());

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

	//	std::cerr << "Part by : " << p << "," << a << std::endl;
	/*----.
	| (b) |
	`----*/
	std::list<unsigned> met_class;
	for (typename std::list<hstate_t>::iterator b = part[p].begin();
	     b != part[p].end(); ++b)
	  if (inverse[*b][a] != 0)
	    for (typename std::set<hstate_t>::iterator q = 
		   inverse[*b][a]->begin();
		 q != inverse[*b][a]->end();
		 ++q)
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

	for (typename std::list<hstate_t>::iterator b = part[p].begin();
	     b != part[p].end(); ++b)
	  {
	    if (inverse[*b][a] != 0)
	      for (typename std::set<hstate_t>::iterator q = inverse[*b][a]->begin();
		   q != inverse[*b][a]->end();
		   ++q)
		{
		  //		  std::cerr << "predecesseur de " << *b << " : " << *q << std::endl;

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
	
// 	for (typename std::list<hstate_t>::const_iterator j = part[i].begin();
// 	     j != part[i].end();
// 	     ++j)
// 	  if (input->is_initial(s))
// 	    {
// 	      output->set_initial(out_states[i]);
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

    for (typename input_t::initial_iterator i = input.initial().begin();
	 i != input.initial().end();
	 ++i)
      output.set_initial(out_states[class_[*i]]);
  }
  
  template<typename A, typename T>
  Element<A, T>
  minimization_hopcroft(const Element<A, T>& a)
  {
    Element<A, T> output(a.set());
    do_hopcroft_minimization_det(a.set(), output, a);
    return trim(output);
  }


  /*----------------------------.
  | hopcroft_minimization_undet |
  `----------------------------*/
  // preconditions : 
  //
  //
  template <typename A, typename input_t, typename output_t>
  void 
  do_hopcroft_minimization_undet(const AutomataBase<A>&	a_set,
			      output_t&			output,
			      const input_t&		input)
  {
    typedef std::set<hstate_t>			     	      delta_ret_t;
    typedef typename input_t::label_t		       	      label_t;
    typedef typename input_t::series_t			      series_t;
    typedef typename series_t::monoid_t		       	      monoid_t;
    typedef typename monoid_t::alphabet_t		      alphabet_t;
    typedef typename alphabet_t::letter_t     		      letter_t;

    unsigned			max_states = 0;

    for (typename input_t::state_iterator i = input.states().begin();
	 i != input.states().end();
	 ++i)
      max_states = std::max(*i, max_states);
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
  
  
  template<typename A, typename T>
  Element<A, T>
  quotient(const Element<A, T>& a)
  {
    Element<A, T> output;
    output.create();
    output.series() = a.series();
    do_hopcroft_minimization_undet(a.set(), output, a);
    return output;
  }

} // vcsn

#endif // VCSN_ALGORITHMS_HOPCROFT_MINIMIZATION_HXX
