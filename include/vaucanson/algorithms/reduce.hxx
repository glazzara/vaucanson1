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

      assert(is_realtime(input));
      std::map<hstate_t, int>	state_to_index;
      int i = 0;

      for_all_const_states(s, input)
	state_to_index[*s] = i++;
      nb_states = i;

      init.resize(i);
      final.resize(i);

      // Conversion of the automaton into linear representation
      for_all_const_initial_states(s, input)
	init[state_to_index[*s]] = input.get_initial(*s).get(empty_word);

      for_all_const_final_states(s, input)
	final[state_to_index[*s]] = input.get_final(*s).get(empty_word);

      for_all_const_transitions(t, input)
      {
	series_set_elt_t s = input.series_of(*t);
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
      // If the initial vector is null, the function immediatly returns

      // this allows to find a pivot for reducing further vectors
      // this pivot is a non zero entry, if one entry is equal to 1
      // it is chosen as a pivot
      unsigned nonzero= nb_states;
      for (unsigned i = 0; i <nb_states; ++i) 
	if(init[i] != zero)
	{
	  nonzero=i;
	  if(init[i] == one)
	    break;
	}
      if(nonzero == nb_states) //all components of init are 0
	return;
      
      // The base is a list of vectors, each vector is associated with
      // a state of the output
      std::vector<semiring_vector_t> base;
      std::vector<hstate_t> new_states;
      // The initial vector corresponds to the first state and is the
      // first element of the new base
      hstate_t initial=output.add_state();
      series_set_elt_t si(output.structure().series());
      si.assoc(empty_word, init[nonzero]);
      output.set_initial(initial, si);
      for (unsigned i = 0; i <nb_states; ++i)
	init[i]=init[i]/init[nonzero];
      base.push_back(init);
      new_states.push_back(initial);
      // To each vector of the base, the index of the pivot is store in
      // the pivot array, which is a permutation.
      unsigned pivot[nb_states];
      for (unsigned i = 0; i < nb_states; ++i)
	pivot[i] = i;
      // The pivot of the first base vector is pivot[0];
      pivot[0]=nonzero; pivot[nonzero]=0;
      // To each vector of the base, all the successor vectors are computed,
      // reduced to respect to the base, and finally, if linearly independant,
      // pushed at the end of the base itself.
      for(unsigned nb=0; nb<base.size(); ++nb)
      {
	//Set the final weight
	semiring_elt_t t=scalar_product(base[nb], final);
	if (t != zero)
	{
	  series_set_elt_t s(output.structure().series());
	  s.assoc(empty_word, t);
	  output.set_final(new_states[nb], s);
	}
	// All the vectors base[nb].mu(a) are processed
	for (typename semiring_matrix_set_t::const_iterator itm
	       = letter_matrix_set.begin();
	     itm != letter_matrix_set.end(); ++itm)
	{
	  semiring_vector_t current(nb_states);
	  product_vector_matrix(base[nb], itm->second, current);
	  monoid_elt_t a = itm->first;
	  
	  //reduction of current w.r.t each base vector;
	  for (unsigned b=0; b<base.size(); ++b)
	  {
	    unsigned p = pivot[b];
	    if (current[p] == zero)
	      continue;
	    semiring_vector_t& vbase = base[b];
	    semiring_elt_t ratio = current[p] / vbase[p];
	    // This is safer than current[p] = current[p]-ratio*vbase[p];
	    current[p] = zero;
	    for (int i = b+1; i < nb_states; ++i)
	      current[pivot[i]] = current[pivot[i]] - ratio*vbase[pivot[i]];
	    series_set_elt_t s(output.structure().series());
	    s.assoc(a, ratio);
	    output.add_series_transition(new_states[nb], new_states[b], s);
	  }
	  nonzero=nb_states;
	  for (unsigned i = base.size(); i < nb_states; ++i)
	    if(current[pivot[i]] != zero)
	    {
	      nonzero=i;
	      if(current[pivot[i]] == one)
		break;
	    }
	  if (nonzero != nb_states) //otherwise, current is null
	  {
	    unsigned j= pivot[nonzero];
	    pivot[nonzero]=pivot[base.size()]; pivot[base.size()]=j;//this is the pivot
	    semiring_elt_t k=current[j];
	    if(k != one)
	    {
	      current[j]=one;
	      for(unsigned r=base.size()+1; r<nb_states; ++r)
		current[pivot[r]]=current[pivot[r]]/k;
	    }
	    hstate_t n_state= output.add_state();
	    base.push_back(current);
	    new_states.push_back(n_state);
	    series_set_elt_t s(output.structure().series());
	    s.assoc(a, k);
	    output.add_series_transition(new_states[nb], n_state, s);
	  }
	}
      }
	/* Print the base
 	  for(typename std::vector<std::pair<hstate_t,semiring_vector_t> >::iterator it = base.begin(); it!=base.end(); ++it)
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
