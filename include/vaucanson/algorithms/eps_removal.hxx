// eps_removal.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_EPS_REMOVAL_HXX
# define VCSN_ALGORITHMS_EPS_REMOVAL_HXX

# include <vaucanson/algorithms/eps_removal.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>

# include <vector>

namespace vcsn {


  template
  <class A_, typename Auto>
  class EpsilonRemover
  {
    AUTOMATON_TYPES(Auto);
    typedef std::vector<std::vector<semiring_elt_t> >	matrix_semiring_elt_t;
    typedef std::vector<series_set_elt_t>		vector_series_t;

  public:
    EpsilonRemover(const AutomataBase<A_>&, Auto& aut)
      : a(aut),
	size(aut.states().size()),
	null_series(aut.series().zero_),
	semiring_elt_zero(aut.series().semiring().wzero_),
	monoid_identity(aut.series().monoid().empty_)
    {

      /// @bug FIXME: This converters should be removed
      // Initialize converters between matrix index and states.
      index_to_state.resize(size);
      int i = 0;
      for_all_states(s, a)
      {
	index_to_state[i] = *s;
	state_to_index[*s] = i++;
      }

      // Initialize m_semiring_elt matrix with epsilon transitions,
      // and suppress them.
      m_semiring_elt.resize(size);
      for (int i = 0; i < size; i++)
	m_semiring_elt[i].resize(size, semiring_elt_zero);

      for_all_states(s, a)
      {
	std::list<htransition_t>	transition_list;
	int src = state_to_index[*s];

	a.deltac(transition_list, *s, delta_kind::transitions());
	for_all_const_(std::list<htransition_t>, e, transition_list)
	{
	  int dst = state_to_index[a.dst_of(*e)];
	  series_set_elt_t t = a.series_of(*e);

	  m_semiring_elt[src][dst] += t.get(monoid_identity);
	  t.assoc(monoid_identity.value(), semiring_elt_zero.value());
	  if(t != null_series)
	    a.add_series_transition(*s, a.dst_of(*e), t);
	  a.del_transition(*e);
	}
      }
    }

    void run(misc::direction_type dir)
    {
      star_matrix();
      if (dir == misc::backward)
	backward_remove();
      else
	forward_remove();
    }

  private:
    // Compute the star of the matrix,
    // it's equivalent to a transitive closure.
    void star_matrix()
    {
      for (int r = 0; r < size; r++)
      {
	result_not_computable_if(!m_semiring_elt[r][r].starable());

	semiring_elt_t w = m_semiring_elt[r][r].star();
	m_semiring_elt[r][r] = w;
	for (int i = 0; i < size; i++)
	  if (i != r)
	  {
	    semiring_elt_t z = m_semiring_elt[i][r] * w;
	    m_semiring_elt[i][r] = z;
	    if(z != semiring_elt_zero)
	      for (int j = 0; j < size; j++)
		if (j != r)
		  m_semiring_elt[i][j] += z * m_semiring_elt[r][j];
	  }
	for (int j = 0; j < size; j++)
	  if (j != r)
	    m_semiring_elt[r][j] = w * m_semiring_elt[r][j];
      }
    }

    void backward_remove()
    {
      // Backward_eps_removal
      // Initialize the m_wfinal
      vector_series_t	m_wfinal (size, null_series);
      for_all_final_states(p, a)
	m_wfinal[state_to_index[*p]] = a.get_final(*p);
      a.clear_final();

      // Compute the backward_eps_removal
      for_all_states(s, a)
	{
	  std::list<htransition_t> transition_list;
	  a.rdeltac(transition_list, *s, delta_kind::transitions());
	  int dst = state_to_index[*s];
	  for_all_const_(std::list<htransition_t>, e, transition_list)
	    {
	      int src = state_to_index[a.src_of(*e)];
	      series_set_elt_t t = a.series_of(*e);
	      for (int k = 0; k < size; k++)
	      {
		semiring_elt_t w = m_semiring_elt[k][src];
		if (w != semiring_elt_zero)
		  a.add_series_transition(index_to_state[k], *s, w * t);
	      }
	      a.del_transition(*e);
	    }
	  series_set_elt_t tw = null_series;
	  for (int k = 0; k < size; k++)
	    tw += m_semiring_elt[dst][k] * m_wfinal[k];
	  if (tw != null_series)
	    a.set_final(*s, tw);
	}
    }

    void forward_remove()
    {
      // Forward eps_removal
      // Initialize the m_wfinal
      vector_series_t	m_winitial (size, null_series);
      for_all_initial_states(p, a)
	m_winitial[state_to_index[*p]] = a.get_initial(*p);
      a.clear_initial();

      // Compute the forward_eps_removal
      for_all_states(s, a)
      {
	std::list<htransition_t> transition_list;
	a.deltac(transition_list, *s, delta_kind::transitions());
	int src = state_to_index[*s];
	for_all_const_(std::list<htransition_t>, e, transition_list)
	{
	  int dst = state_to_index[a.dst_of(*e)];
	  series_set_elt_t t = a.series_of(*e);
	  for (int k = 0; k < size; k++)
	  {
	    semiring_elt_t w = m_semiring_elt[dst][k];
	    if (w != semiring_elt_zero)
	      a.add_series_transition(*s, index_to_state[k], t * w);
	  }
	  a.del_transition(*e);
	}
	series_set_elt_t tw = null_series;
	for (int k = 0; k < size; k++)
	  tw += m_winitial[k] * m_semiring_elt[k][src];
	if (tw != null_series)
	  a.set_initial(*s, tw);
      }
    }

    automaton_t&	a;
    int			size;
    series_set_elt_t	null_series;
    semiring_elt_t	semiring_elt_zero;
    monoid_elt_t	monoid_identity;
    matrix_semiring_elt_t	m_semiring_elt;
    std::vector<hstate_t>	index_to_state;
    std::map<hstate_t, int>	state_to_index;
  };


  /*--------------.
    | eps_removal.  |
    `--------------*/
  template <class A_, typename Auto>
  void
  do_eps_removal_here(const AutomataBase<A_>& a_set, Auto& a,
		      misc::direction_type dir)
  {
    TIMER_SCOPED("eps_removal");

    EpsilonRemover<A_, Auto> algo(a_set, a);
    algo.run(dir);
  }

  template<typename  A, typename  T>
  void
  eps_removal_here(Element<A, T>& a, misc::direction_type dir)
  {
    do_eps_removal_here(a.structure(), a, dir);
  }

  template<typename  A, typename  T>
  Element<A, T>
  eps_removal(const Element<A, T>& a, misc::direction_type dir)
  {
    Element<A, T> ret(a);
    do_eps_removal_here(ret.structure(), ret, dir);
    return ret;
  }

  template<typename  A, typename  T>
  void
  backward_eps_removal_here(Element<A, T>& a)
  {
    do_eps_removal_here(a.structure(), a, misc::backward);
  }

  template<typename  A, typename  T>
  Element<A, T>
  backward_eps_removal(const Element<A, T>& a)
  {
    Element<A, T> ret(a);
    do_eps_removal_here(ret.structure(), ret, misc::backward);
    return ret;
  }

  template<typename  A, typename  T>
  void
  forward_eps_removal_here(Element<A, T>& a)
  {
    do_eps_removal_here(a.structure(), a, misc::forward);
  }

  template<typename  A, typename  T>
  Element<A, T>
  forward_eps_removal(const Element<A, T>& a)
  {
    Element<A, T> ret(a);
    do_eps_removal_here(ret.structure(), ret, misc::forward);
    return ret;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_EPS_REMOVAL_HXX
