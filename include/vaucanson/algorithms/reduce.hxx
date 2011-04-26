// reduce.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008, 2011 The Vaucanson Group.
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

#ifndef VCSN_ALGORITHMS_REDUCE_HXX
# define VCSN_ALGORITHMS_REDUCE_HXX
# include <queue>
# include <vector>
# include <map>
# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {

  template<typename A, typename AI, typename AO>
  class reducer
  {
    typedef Element<A, AI> Auto;
    AUTOMATON_TYPES(Auto);
    AUTOMATON_FREEMONOID_TYPES(Auto);
    typedef std::vector<semiring_elt_t> semiring_vector_t;
    typedef std::vector<std::map<std::size_t, semiring_elt_t> > semiring_matrix_t;
    typedef std::map<monoid_elt_t, semiring_matrix_t> semiring_matrix_set_t;

  /* output may have an implementation different from the
     implementation of the input; this is for instance the case where
     input is a transpose view, as in the wrappers.
     */

  public:
    reducer(const Element<A, AI>& input, Element<A, AO>& output) :
      zero(input.series().semiring().wzero_),
      one(input.series().semiring().wone_),
      empty_word(input.series().monoid().VCSN_EMPTY_),
      output(output)
    {
      std::map<hstate_t, int>	state_to_index;
      int i = 0;

      for_all_const_states(s, input)
	state_to_index[*s] = i++;
      nb_states = i;

      init.resize(i);
      final.resize(i);

      // We assume that there are only weights on initial and final
      // transitions

      // Conversion of the automaton into linear representation
      for_all_const_initial_states(s, input)
	init[state_to_index[*s]] = input.get_initial(*s).get(empty_word);

      for_all_const_final_states(s, input)
	final[state_to_index[*s]] = input.get_final(*s).get(empty_word);

      for_all_const_transitions(t, input)
      {
	series_set_elt_t s = input.series_of(*t);
	assert(is_support_in_alphabet(s));
	for_all_(series_set_elt_t::support_t, l, s.supp())
	{
	  const monoid_elt_t m(input.structure().series().monoid(), *l);
	  typename semiring_matrix_set_t::iterator it = letter_matrix_set.find(m);
	  if (it == letter_matrix_set.end())
	    it = letter_matrix_set.insert(make_pair(m, semiring_matrix_t(nb_states))).first;
	  it->second[state_to_index[input.src_of(*t)]][state_to_index[input.dst_of(*t)]] = s.get(m);
	}
      }
    }

    //utility class
    struct triple_t
    {
      hstate_t state;
      semiring_vector_t vector;
      monoid_elt_t letter;

      triple_t(const hstate_t& state, const semiring_vector_t& vector,
	       const monoid_elt_t& letter) :
	state(state), vector(vector), letter(letter) {}

    };

    //utility methods
    void product_vector_matrix(const semiring_vector_t& v,
			       const semiring_matrix_t& m,
			       semiring_vector_t& res)
    {
      for(int i=0; i<nb_states; i++)
	for(typename std::map<std::size_t, semiring_elt_t>::const_iterator it
	      = m[i].begin(); it != m[i].end(); ++it)
	  {
	    int j = it->first;
	    res[j] += v[i] * it->second;
	  }
    }

    semiring_elt_t scalar_product(const semiring_vector_t& v,
				  const semiring_vector_t& w)
    {
      semiring_elt_t res(zero);
      for(int i = 0; i < nb_states; ++i)
	res += v[i] * w[i];
      return res;
    }

    //core of the algorithm
    void
    left_reduce()
    {
      //if the initial vector is null, the reduction is empty
      {
	int i;
        for (i = 0; i < nb_states; ++i)
          if (init[i] != zero)
            break;
        if (i == nb_states)
          return;
      }
      // otherwise...
      std::queue<triple_t> queue;
      // The base is a list of vectors, each vector is associated with
      // a state of the output
      std::list<std::pair<hstate_t,semiring_vector_t> > base;
      // The initial vector corresponds to the first state and is the
      // first element of the new base
      hstate_t n_init = output.add_state();
      base.push_back(std::pair<hstate_t,semiring_vector_t>(n_init, init));
      output.set_initial(n_init);
      // Final weight of the initial state
      semiring_elt_t t = scalar_product(init, final);
      if(t != zero)
	{
	  series_set_elt_t s(output.structure().series());
	  s.assoc(empty_word, t);
	  output.set_final(n_init, s);
	}
      /* for each letter a, I.mu(a) is computed and pushed in the queue
	 with the letter a and the state corresponding to I; it allows to
	 build the automaton in the same time.
      */
      for (typename semiring_matrix_set_t::const_iterator it
	     = letter_matrix_set.begin(); it != letter_matrix_set.end(); ++it)
	{
	  semiring_vector_t nv(nb_states);
	  product_vector_matrix(init, it->second, nv);
	  queue.push(triple_t(n_init, nv, it->first));
	}
      while (!queue.empty())
	{
	  triple_t& tr = queue.front();
	  //the triple tr is not yet poped, to keep valid references.
	  semiring_vector_t& current = tr.vector;
	  // first non null indices of current and base vectors.
	  std::size_t curr_fnn = 0;
	  std::size_t base_fnn = 0;
	  for(typename std::list<std::pair<hstate_t,semiring_vector_t> >::iterator it
		= base.begin(); it!=base.end(); ++it)
	  {
	    while (curr_fnn < nb_states && current[curr_fnn] == zero)
	      ++curr_fnn;
	    // first non null index of the base vector
	    // As the matrix is "in stairs" the base_fnn is larger than the previous one
	    semiring_vector_t& vbase = it->second;
	    while (base_fnn < nb_states && vbase[base_fnn] == zero)
	      ++base_fnn;
	    // Case A
	    if (base_fnn < curr_fnn)
	      // nothing to do in this case
	      continue;
	    // Case B
	    if (base_fnn > curr_fnn)
	      // current is added to the base before the current base vector
	      {
	        hstate_t n_state= output.add_state();
	        base.insert(it,std::pair<hstate_t,semiring_vector_t>(n_state,
								     current));
		series_set_elt_t s(output.structure().series());
		s.assoc(tr.letter, one);
	        output.add_series_transition(tr.state, n_state, s);
	        semiring_elt_t t=scalar_product(current, final);
	        if(t != zero)
	        {
		  series_set_elt_t s(output.structure().series());
		  s.assoc(empty_word, t);
		  output.set_final(n_state, s);
		}
		// All the vectors current.mu(a) are put in the queue
		for (typename semiring_matrix_set_t::const_iterator itm
		       = letter_matrix_set.begin();
		     itm != letter_matrix_set.end(); ++itm)
	       {
	    	  semiring_vector_t nv(nb_states);
		  product_vector_matrix(current, itm->second, nv);
		  queue.push(triple_t(n_state, nv, itm->first));
	       }
		// To avoid treatment after exiting the loop:
		curr_fnn = nb_states;
		break;
	      }
	    // Case C
	    // Otherwise, current is reduced w.r.t base
	    semiring_elt_t ratio = current[curr_fnn] / vbase[curr_fnn];
	    // This is safer than current[curr_fnn] = current[curr_fnn]-ratio*vbase[curr_fnn];
	    current[curr_fnn] = zero;
	    for(int i = curr_fnn+1; i < nb_states; ++i)
		current[i ] =current[i] - ratio*vbase[i];
		series_set_elt_t s(output.structure().series());
		s.assoc(tr.letter, ratio);
	    output.add_series_transition(tr.state, it->first, s);
	  }
	  // If current has not been totally reduced w.r.t the base,
	  // it has to be put itself in the base
	  while (curr_fnn < nb_states && current[curr_fnn] == zero)
	    ++curr_fnn;
	  if (nb_states> curr_fnn)
	    // current is added at the end of the base
	    {
	      hstate_t n_state= output.add_state();
	      base.push_back(std::pair<hstate_t,semiring_vector_t>(n_state,
								   current));
	      series_set_elt_t s(output.structure().series());
	      s.assoc(tr.letter, one);
	      output.add_series_transition(tr.state, n_state, s);
	      semiring_elt_t t=scalar_product(current, final);
	      if(t != zero)
		{
		  series_set_elt_t s(output.structure().series());
		  s.assoc(empty_word, t);
		  output.set_final(n_state, s);
		}
	      for (typename semiring_matrix_set_t::const_iterator itm
		     = letter_matrix_set.begin();
		   itm != letter_matrix_set.end(); ++itm)
	      {
		semiring_vector_t nv(nb_states);
		product_vector_matrix(current, itm->second, nv);
		queue.push(triple_t(n_state, nv, itm->first));
	      }
	   }
	  queue.pop();
	}
	/* Print the base
 	  for(typename std::list<std::pair<hstate_t,semiring_vector_t> >::iterator it = base.begin(); it!=base.end(); ++it)
	  {
	  	std::cerr << it->first << ':';
	  	for(int i=0; i < nb_states; ++i)
 		  	std::cerr << (it->second)[i] << ',';
		std::cerr << std::endl;
	  }
	  */
    }

  private:
    // zero and identity of used algebraic structure.
    semiring_elt_t	zero;
    semiring_elt_t	one;
    monoid_elt_t	empty_word;

    // Linear representation of the input automaton in matrix form
    semiring_vector_t init;
    semiring_vector_t final;
    semiring_matrix_set_t letter_matrix_set;
    size_t nb_states;

    Element<A, AO>& output;
  };

  template<typename A, typename AI, typename AO>
  void
  do_semi_reduce(const Element<A, AI>& a, Element<A, AO>& output)
  {
    reducer<A, AI, AO> r(a, output);
    r.left_reduce();
  }

  template<typename A, typename AI>
  Element<A, AI>
  semi_reduce(const Element<A, AI>& a)
  {
    precondition(is_realtime(a));
    Element<A, AI> output(a.structure());
    do_semi_reduce(a, output);
    return output;
  }

  template<typename A, typename AI>
  Element<A, AI>
  reduce(const Element<A, AI>& a, misc::direction_type dir)
  {
    precondition(is_realtime(a));
    Element<A, AI> tmp(a.structure());
    Element<A, AI> output(a.structure());
    if (dir == misc::right_left)
    {
      do_semi_reduce(transpose_view(a), tmp);
      do_semi_reduce(transpose_view(tmp), output);
      return output;
    }
    else
    {
      do_semi_reduce(a, tmp);
      do_semi_reduce(transpose_view(tmp), output);
      return transpose(output);
    }
  }


} // vcsn

#endif // !VCSN_ALGORITHMS_REDUCE_HXX //
