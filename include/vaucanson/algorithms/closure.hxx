// closure.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_CLOSURE_HXX
# define VCSN_ALGORITHMS_CLOSURE_HXX

# include <vaucanson/algorithms/closure.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <vector>

namespace vcsn {

  /*--------.
  | closure |
  `--------*/
  template <class A_, typename Auto>
  void
  do_closure_here(const AutomataBase<A_>&, Auto& a, bool bck_fwd)
  {
    // bck_fwd : true -> backward closure , false -> forward closure
    AUTOMATON_TYPES(Auto);
    typedef std::vector<std::vector<semiring_elt_t> >	matrix_semiring_elt_t;
    typedef std::vector<series_set_elt_t>		vector_series_t;

    series_set_elt_t	series_identity = a.series().zero_;
    semiring_elt_t	semiring_elt_zero = a.series().semiring().wzero_;
    monoid_elt_t        monoid_identity = a.series().monoid().empty_;

    int                   i, j, k, size = a.states().size();

    matrix_semiring_elt_t	m_semiring_elt (size);

    for (i = 0; i < size; i++)
	m_semiring_elt[i].resize(size, semiring_elt_zero);

    /// @bug FIXME: This converters should be removed
    // Initialize converters between matrix index and states.
    std::vector<hstate_t>	index_to_state (size);
    std::map<hstate_t, int>	state_to_index;
    i = 0;
    for_each_state(s, a)
    {
      index_to_state[i] = *s;
      state_to_index[*s] = i++;
    }

    // Initialize the matrix m_semiring_elt
    // with the original automaton and delete epsilon-transitions
    for_each_state(s, a)
    {
      std::list<hedge_t>	edge_list;
      a.deltac(edge_list, *s, delta_kind::edges());

      int origin = state_to_index[*s];

      for_each_const_(std::list<hedge_t>, e, edge_list)
	{
	  int aim = state_to_index[a.aim_of(*e)];
	  series_set_elt_t t = a.series_of(*e);
	  m_semiring_elt[origin][aim] += t.get(monoid_identity);
	  t.assoc(monoid_identity.value(), semiring_elt_zero.value());
	  if(t != series_identity)
	    a.add_series_edge(*s, a.aim_of(*e), t);
	  a.del_edge(*e);
	}
    }

    // Compute star(m_semiring_elt) <--> epsilon-closure
    for (int r = 0; r < size; r++)
      {
	result_not_computable_if(!m_semiring_elt[r][r].starable());

	semiring_elt_t w = m_semiring_elt[r][r].star();
	m_semiring_elt[r][r] = w;
	for (i = 0; i < size; i++)
	  if (i != r)
	    {
	      semiring_elt_t z = m_semiring_elt[i][r] * w;
	      m_semiring_elt[i][r] = z;
	      if(z != semiring_elt_zero)
		for (j = 0; j < size; j++)
		  if(j != r)
		    m_semiring_elt[i][j] += z * m_semiring_elt[r][j];
	    }
	for (j = 0; j < size; j++)
	  if (j != r)
	    m_semiring_elt[r][j] = w * m_semiring_elt[r][j];
      }

    if (bck_fwd)
      {
	// Backward_closure
	// Initialize the m_wfinal
	vector_series_t	m_wfinal (size, series_identity);
	for_each_final_state(p, a)
	  m_wfinal[state_to_index[*p]] = a.get_final(*p);
	a.clear_final();

	// Compute the backward_closure
	for_each_state(s, a)
	  {
	    std::list<hedge_t> edge_list;
	    a.rdeltac(edge_list, *s, delta_kind::edges());
	    int aim = state_to_index[*s];
	    for_each_const_(std::list<hedge_t>, e, edge_list)
	      {
		int origin = state_to_index[a.origin_of(*e)];
		series_set_elt_t t = a.series_of(*e);
		for (k = 0; k < size; k++)
		  {
		    semiring_elt_t w = m_semiring_elt[k][origin];
		    if (w != semiring_elt_zero)
		      a.add_series_edge(index_to_state[k], *s, w * t);
		  }
		a.del_edge(*e);
	      }
	    series_set_elt_t tw = series_identity;
	    for (k = 0; k < size; k++)
	      tw += m_semiring_elt[aim][k] * m_wfinal[k];
	    if (tw != series_identity)
	      a.set_final(*s, tw);
	  }
      }
    else
      {
	// Forward closure
	// Initialize the m_wfinal
	vector_series_t	m_winitial (size, series_identity);
	for_each_initial_state(p, a)
	  m_winitial[state_to_index[*p]] = a.get_initial(*p);
	a.clear_initial();

	// Compute the forward_closure
	for_each_state(s, a)
	  {
	    std::list<hedge_t> edge_list;
	    a.deltac(edge_list, *s, delta_kind::edges());
	    int origin = state_to_index[*s];
	    for_each_const_(std::list<hedge_t>, e, edge_list)
	      {
		int aim = state_to_index[a.aim_of(*e)];
		series_set_elt_t t = a.series_of(*e);
		for (k = 0; k < size; k++)
		  {
		    semiring_elt_t w = m_semiring_elt[aim][k];
		    if (w != semiring_elt_zero)
		      a.add_series_edge(*s, index_to_state[k], t * w);
		  }
		a.del_edge(*e);
	      }
	    series_set_elt_t tw = series_identity;
	    for (k = 0; k < size; k++)
	      tw += m_winitial[k] * m_semiring_elt[k][origin];
	    if (tw != series_identity)
	      a.set_initial(*s, tw);
	  }
      }
  }

  template<typename  A, typename  T>
  void
  closure_here(Element<A, T>& a, bool bck)
  {
    do_closure_here(a.structure(), a, bck);
  }

  template<typename  A, typename  T>
  Element<A, T>
  closure(const Element<A, T>& a, bool bck)
  {
    Element<A, T> ret(a);
    do_closure_here(ret.structure(), ret, bck);
    return ret;
  }

  template<typename  A, typename  T>
  void
  backward_closure_here(Element<A, T>& a)
  {
    do_closure_here(a.structure(), a, true);
  }

  template<typename  A, typename  T>
  Element<A, T>
  backward_closure(const Element<A, T>& a)
  {
    Element<A, T> ret(a);
    do_closure_here(ret.structure(), ret, true);
    return ret;
  }

  template<typename  A, typename  T>
  void
  forward_closure_here(Element<A, T>& a)
  {
    do_closure_here(a.structure(), a, false);
  }

  template<typename  A, typename  T>
  Element<A, T>
  forward_closure(const Element<A, T>& a)
  {
    Element<A, T> ret(a);
    do_closure_here(ret.structure(), ret, false);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_CLOSURE_HXX
