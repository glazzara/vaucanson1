// minimization_moore.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
# include <vaucanson/algorithms/trim.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/automata/concept/history.hh>

namespace vcsn {

  /*-------------------.
  | minimization_moore |
  `-------------------*/
  // preconditions : 
  //  - the input automaton is deterministic ;
  //  - the output automaton is well initialized with good sets ;
  //
  template <typename A, typename input_t, typename output_t>
  void
  do_minimization_moore(const AutomataBase<A>&	a_set,
			output_t&		output,
			const input_t&		input)
  {
    typedef typename input_t::series_t			series_t;
    typedef typename series_t::monoid_t			monoid_t;
    typedef typename input_t::series_elt_t		series_elt_t;
    typedef typename series_elt_t::monoid_elt_t		monoid_elt_t;
    typedef typename input_t::serie_value_t		serie_value_t;
    typedef typename series_elt_t::semiring_elt_t		semiring_elt_t;
    // FIXME : here we assume monoid is a free monoid -> concept checking ?
    typedef typename monoid_t::alphabet_t		alphabet_t;
    typedef typename alphabet_t::letter_t		letter_t;

    typedef std::set<hedge_t>				delta_ret_t;
    typedef std::set<hstate_t>				subset_t;
    typedef std::map<letter_t, std::pair<semiring_elt_t, unsigned> >		map_t;
    typedef std::map<serie_value_t, unsigned>		final_map_t;
    typedef std::list<hstate_t>				hstate_list_t;
    typedef std::vector<hstate_list_t>  	       	partitions_t;;
    typedef std::pair<unsigned, hstate_list_t::iterator> class_pair_t;
    typedef std::vector<class_pair_t>			class_t;
    typedef std::map<letter_t, std::vector<series_elt_t> > succ_t;
    typedef std::vector<succ_t>				current_succ_t;
    typedef std::map<letter_t, current_succ_t>		letter_succ_t;
    typedef std::map<unsigned, hstate_t>		conv_map_t;

    const alphabet_t	&alphabet = input.set().series().monoid().alphabet();
    unsigned		max_partitions = 0;
    class_t		classes(input.states().size());
    current_succ_t	csucc(input.states().size());
    delta_ret_t		delta_ret;
    partitions_t	part;
    std::stack<hstate_list_t> new_parts;

    /*-------------------------.
    | Initialize the partition |
    `-------------------------*/
    for (typename current_succ_t::iterator s = csucc.begin();
	 s != csucc.end(); ++s)
      for (typename alphabet_t::const_iterator a = alphabet.begin();
	   a != alphabet.end(); ++a)
	(*s)[*a] = std::vector<series_elt_t>(input.states().size());

    final_map_t	fmap_;
    
    for (typename input_t::state_iterator s = input.states().begin();
	 s != input.states().end();
	 ++s)
      {
	typename final_map_t::const_iterator fm = 
	  fmap_.find(input.get_final(*s).value());
	if (fm == fmap_.end())
	  {
	    fmap_[input.get_final(*s).value()] = max_partitions;
	    part.push_back(std::list<hstate_t>());
	    part[max_partitions].push_front(*s);
	    classes[*s] = std::make_pair(max_partitions, 
					 part[max_partitions].begin());
	    ++max_partitions;
	  }
	else
	  {
	    part[fm->second].push_front(*s);
	    classes[*s] = std::make_pair(fm->second, part[fm->second].begin());
	  }
      }
    
    /*----------.
    | Main loop |
    `----------*/
    bool	stable_point;
    class_t	classes_;

    do
      {
	classes_ = classes;
	stable_point = true;

	for (typename input_t::state_iterator s = input.states().begin();
	     s != input.states().end(); ++s)
	  for (typename alphabet_t::const_iterator a = alphabet.begin();
	       a != alphabet.end(); ++a)
	    {
	      std::fill(csucc[*s][*a].begin(), 
			csucc[*s][*a].end(), 
			series_elt_t(a_set.series()));
	      delta_ret.clear();
	      // FIXME : use another version of delta !
	      input.letter_deltac(delta_ret, *s, *a, delta_kind::edges());
	      for (delta_ret_t::const_iterator d = delta_ret.begin();
		   d != delta_ret.end(); ++d)
		{
		  csucc[*s][*a][classes_[input.aim_of(*d)].first] 
		    = input.serie_of(*d);
		}
	    }

	for (unsigned P = 0; P < max_partitions; ++P)
	  {
	    typename hstate_list_t::iterator p = part[P].begin();
	    hstate_list_t new_p;
	    while (p != part[P].end())
	      {
		new_p.clear();
		for (typename hstate_list_t::const_iterator p_ = 
		       part[P].begin();
		     p_ != part[P].end(); 
		     ++p_)
		  if ((csucc[*p_] == csucc[*p])
		      &&
		      (*p != *p_))
		      new_p.push_back(*p_);
		new_p.push_back(*p);
		if (new_p.size() != part[P].size())
		  {
		    new_parts.push(new_p);
		    for (typename hstate_list_t::const_iterator p_ =
			   new_p.begin();
			 p_ != new_p.end(); 
			 ++p_)
		      part[P].remove(*p_);
		    part[P].remove(*p);
		    p = part[P].begin();		    
		  }
		else
		  ++p;
	      }
	  }
	
	while (!new_parts.empty())
	  {
	    stable_point = false;
	    part.push_back(hstate_list_t());
	    for (typename hstate_list_t::const_iterator p_ = 
		   new_parts.top().begin();
		 p_ != new_parts.top().end();
		 ++p_)
	      {
		part[max_partitions].push_front(*p_);
		classes[*p_].first = max_partitions;
		classes[*p_].second = part[max_partitions].begin();
	      }
	    max_partitions++;
	    new_parts.pop();
	  }
      }
    while (!stable_point);

    /*-------------.
    | Construction |
    `-------------*/
    conv_map_t	conv;

    for (unsigned c = 0; c < max_partitions; ++c)
      if (part[c].size() != 0)
	{
	  hstate_t q = output.add_state();
	  hstate_t s = *part[c].begin();
	  for (typename hstate_list_t::const_iterator h = part[c].begin();
	       h != part[c].end(); ++h)
	    {
	      if (input.is_initial(*h))
		{
		  output.set_initial(q);
		  break;
		}
	    }
	  if (input.is_final(s))
	    output.set_final(q);	
	  conv[c] = q;
	}

    for (typename conv_map_t::const_iterator c_ = conv.begin(); 
	 c_ != conv.end(); ++c_)
	{
	  hstate_t q = c_->second;
	  unsigned c = c_->first;

	  if (part[c].size() == 0)
	    continue;
	  
	  hstate_t s = *part[c].begin();
	  series_elt_t zero;

	  for (typename alphabet_t::const_iterator a = alphabet.begin();
	       a != alphabet.end(); ++a)
	    for (unsigned aim = 0; aim < csucc[s][*a].size(); ++aim)
	      if (csucc[s][*a][aim] != zero)
		output.add_serie_edge(q, conv[aim], csucc[s][*a][aim]);
	}
  }
  
  template<typename A, typename T>
  Element<A, T>
  minimization_moore(const Element<A, T>& a)
  {
    Element<A, T> output(a.set());
    do_minimization_moore(a.set(), output, a);
    return trim(output);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_MINIMIZATION_MOORE_HXX
