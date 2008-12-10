// reduce.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2008 The Vaucanson Group.
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
# include <vector>
# include <map>
# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {

  template<typename A, typename AI>
  class reducer
  {
    // preconditions : letterized //
    typedef Element<A, AI> Auto;
    AUTOMATON_TYPES(Auto);
    AUTOMATON_FREEMONOID_TYPES(Auto);
    // AUTOMATA_SET_TYPES(automata_set_t);
    typedef std::vector<semiring_elt_t> semiring_vector_t;
    typedef std::vector<std::map<std::size_t, semiring_elt_t> > semiring_matrix_t;
    typedef std::map<monoid_elt_t, semiring_matrix_t> semiring_matrix_set_t;

  public:
    reducer(const Element<A, AI>& input, Element<A, AI>& output) :
      null_series_(input.series().zero_),
      semiring_elt_zero_(input.series().semiring().wzero_),
      semiring_elt_one_(input.series().semiring().wone_),
      monoid_identity_(input.series().monoid().VCSN_EMPTY_),
      output_(output)
    {
      std::map<hstate_t, int>	state_to_index;
      int i = 0;

      for_all_const_states(s, input)
	state_to_index[*s] = i++;
      nb_states_ = i;

      init_.resize(i);
      final_.resize(i);

      // We  assume that there are only weights on initial and final transitions

      for_all_const_initial_states(s, input)
	init_[state_to_index[*s]] = input.get_initial(*s).get(monoid_identity_);

      for_all_const_final_states(s, input)
	final_[state_to_index[*s]] = input.get_final(*s).get(monoid_identity_);

      for_all_const_transitions(t, input)
      {
	series_set_elt_t s = input.series_of(*t);
	assert(is_support_in_alphabet(s));
	for_all_(series_set_elt_t::support_t, l, s.supp())
	{
	  const monoid_elt_t m(input.structure().series().monoid(), *l);
	  typename semiring_matrix_set_t::iterator it = letter_matrix_set_.find(m);
	  if (it == letter_matrix_set_.end())
	    it = letter_matrix_set_.insert(make_pair(m, semiring_matrix_t(nb_states_))).first;
	  it->second[state_to_index[input.src_of(*t)]][state_to_index[input.dst_of(*t)]] = s.get(m);
	}
      }
    }

    void
    left_reduce()
    {
      std::queue<semiring_vector_t> q;
      q.push(init_);
      semiring_matrix_t m;

      while (!q.empty())
      {
	semiring_vector_t curr = q.front();
	q.pop();

	// first non null index of curr
	std::size_t curr_fnn = 0;

	// current row of the matrix
	typename semiring_matrix_t::iterator m_row = m.begin();
	while (m_row != m.end())
	{
	  while (curr_fnn < nb_states_ && curr[curr_fnn] == semiring_elt_zero_)
	    curr_fnn++;

	  // first non null index of the current row of the matrix
	  std::size_t m_row_fnn = 0;
	  while (m_row_fnn < nb_states_ && m_row->find(m_row_fnn) == m_row->end())
	    m_row_fnn++;

	  // if the first non null value of curr is before the first non null
	  // value of the current row we must insert it before this line
	  if (curr_fnn < m_row_fnn)
	    break;

	  if (curr_fnn == m_row_fnn)
	  {
	    semiring_elt_t coef = curr[curr_fnn] / (*m_row)[m_row_fnn];
	    for (typename std::map<std::size_t, semiring_elt_t>::const_iterator it = (*m_row).begin();
		 it != (*m_row).end(); it++)
	    {
	      semiring_elt_t tmp = curr[it->first] - coef * it->second;
	      // some semirings have not an exact representation in
	      // these semirings op_eq is override to handle this problem
	      if (tmp == semiring_elt_zero_)
		curr[it->first] = semiring_elt_zero_;
	      else
		curr[it->first] = tmp;
	    }
	  }
	  m_row++;
	}
	while (curr_fnn < nb_states_ && curr[curr_fnn] == semiring_elt_zero_)
	  curr_fnn++;
	if (curr_fnn != nb_states_) // curr is not full of semiring_elt_zero_
	{
	  m_row = m.insert(m_row, std::map<std::size_t, semiring_elt_t>());
	  for (size_t i = curr_fnn; i < nb_states_; i++)
	    if (curr[i] != semiring_elt_zero_)
	      (*m_row)[i] = curr[i];

	  // multiply curr with the matrix representing each letter
	  // and push it in q
	  for (typename semiring_matrix_set_t::const_iterator it = letter_matrix_set_.begin();
	       it != letter_matrix_set_.end(); it++)
	  {
	    semiring_vector_t to_push(nb_states_, semiring_elt_zero_);
	    typename std::map<std::size_t, semiring_elt_t>::const_iterator tmp;
	    for (size_t i = 0; i < nb_states_; i++)
	      for (size_t j = 0; j < nb_states_; j++)
		if ((tmp = it->second[j].find(i)) != it->second[j].end())
		  to_push[i] += curr[j] * tmp->second;
	    q.push(to_push);
	  }
	}
      }

      // New Initial Vector
      semiring_vector_t newinit(m.size(), semiring_elt_zero_);
      // Change Base
      for (std::size_t i = 0; i < m.size(); i++)
      { // m , init_, newinit
	std::size_t init_fnn = 0;
	for (std::size_t j = 0; j < m.size(); j++)
	{
	  while (init_fnn < nb_states_ && init_[init_fnn] == semiring_elt_zero_)
	    init_fnn++;

	  std::size_t mj_fnn = 0;
	  while (mj_fnn < m.size() && m[j].find(mj_fnn) == m[j].end())
	    mj_fnn++;

	  if (init_fnn == mj_fnn)
	  {
	    semiring_elt_t coef = init_[init_fnn] / m[j][mj_fnn];
	    for (typename std::map<std::size_t, semiring_elt_t>::const_iterator it = m[j].begin();
		 it != m[j].end(); it++)
	    {
	      semiring_elt_t tmp = init_[it->first] - coef * it->second;
	      // some semirings have not an exact representation in
	      // these semirings op_eq is override to handle this problem
	      if (tmp == semiring_elt_zero_)
		init_[it->first] = semiring_elt_zero_;
	      else
		init_[it->first] = tmp;
	    }
	    newinit[j] = coef;
	  }
	}
      }
      std::swap(init_, newinit);

      // New Final Vector
      semiring_vector_t newfinal(m.size(), semiring_elt_zero_);
      for (std::size_t i = 0; i < m.size(); i++)
      {
	for (typename std::map<std::size_t, semiring_elt_t>::iterator it = m[i].begin();
	     it != m[i].end(); it++)
	  newfinal[i] += it->second * final_[it->first];
      }
      std::swap(final_, newfinal);

      // New Matrices for Letters
      for (typename semiring_matrix_set_t::iterator lit = letter_matrix_set_.begin();
	   lit != letter_matrix_set_.end(); lit++)
      {
	std::vector<semiring_vector_t> lm(m.size(),
					  semiring_vector_t(nb_states_,
							    semiring_elt_zero_));
	// tmp will be used to perform the multiplication only if necessary
	typename std::map<std::size_t, semiring_elt_t>::iterator tmp;
	for (std::size_t i = 0; i < m.size(); i++)
	{
	  for (std::size_t k = 0; k < nb_states_; k++)
	    for (typename std::map<std::size_t, semiring_elt_t>::iterator mit = m[i].begin();
		 mit != m[i].end(); mit++)
		if ((tmp = lit->second[mit->first].find(k)) != lit->second[mit->first].end())
		  lm[i][k] += mit->second * tmp->second;
	  lit->second.resize(m.size());
	}
	// Change Base
	for (std::size_t i = 0; i < m.size(); i++)
	{ // m , lm[i], lit->second[i]
	  lit->second[i].clear();
	  std::size_t lmi_fnn = 0;
	  for (std::size_t j = 0; j < m.size(); j++)
	  {
	    while (lmi_fnn < nb_states_ && lm[i][lmi_fnn] == semiring_elt_zero_)
	      lmi_fnn++;

	    std::size_t mj_fnn = 0;
	    while (mj_fnn < m.size() && m[j].find(mj_fnn) == m[j].end())
	      mj_fnn++;

	    if (lmi_fnn == mj_fnn)
	    {
	      semiring_elt_t coef = lm[i][lmi_fnn] / m[j][mj_fnn];
	      for (typename std::map<std::size_t, semiring_elt_t>::const_iterator it = m[j].begin();
		   it != m[j].end(); it++)
	      {
		semiring_elt_t tmp = lm[i][it->first] - coef * it->second;
		// some semirings have not an exact representation in
		// these semirings op_eq is override to handle this problem
		if (tmp == semiring_elt_zero_)
		  lm[i][it->first] = semiring_elt_zero_;
		else
		  lm[i][it->first] = tmp;
	      }
	      lit->second[i][j] = coef;
	    }
	  }
	}
      }
      nb_states_ = m.size();
    }

    void
    transpose()
    {
      std::swap(init_, final_);
      for (typename semiring_matrix_set_t::iterator lit = letter_matrix_set_.begin();
	   lit != letter_matrix_set_.end(); lit++)
      {
	for (std::size_t i = 0; i < nb_states_; i++)
	  for (std::size_t j = i; j < nb_states_; j++)
	  {
	    typename std::map<std::size_t, semiring_elt_t>::iterator ij = lit->second[i].find(j);
	    typename std::map<std::size_t, semiring_elt_t>::iterator ji = lit->second[j].find(i);
	    if (ij != lit->second[i].end())
	      if (ji != lit->second[j].end()) // both exist
		std::swap(ij->second, ji->second);
	      else // only ij exist
	      {
		lit->second[j][i] = ij->second;
		lit->second[i].erase(ij);
	      }
	    else
	      if (ji != lit->second[j].end()) // only ji exist
	      {
		lit->second[i][j] = ji->second;
		lit->second[j].erase(ji);
	      }
	  }
      }
    }

    void
    release()
    {
      std::vector<hstate_t> new_states(nb_states_);

      // Create all states and set them to initial or final if necessary.
      for (std::size_t i = 0; i < nb_states_; i++)
      {
	new_states[i] = output_.add_state();
	if (init_[i] != semiring_elt_zero_)
	  ;//output_.set_initial(new_states[i], init_[i]);
	if (final_[i] != semiring_elt_zero_)
	  ;//output_.set_final(new_states[i], final_[i]);
      }

      // Create all transitions.
      for (typename semiring_matrix_set_t::iterator lit = letter_matrix_set_.begin();
	  lit != letter_matrix_set_.end(); lit++)
	for (std::size_t i = 0; i < nb_states_; i++)
	  for (std::size_t j = 0; j < nb_states_; j++)
	  {
	    typename std::map<std::size_t, semiring_elt_t>::iterator tmp;
	    if ((tmp = lit->second[i].find(j)) != lit->second[i].end())
	      ;//output_.add_series_transition(new_states[i], new_states[i], *tmp);
	  }
    }

    void
    check()
    {
      /* DEBUG */
      for (typename semiring_matrix_set_t::iterator lit = letter_matrix_set_.begin();
	   lit != letter_matrix_set_.end(); lit++)
      {
	std::cout << lit->first << std::endl;
	for (std::size_t i = 0; i < nb_states_; i++)
	{
	  for (typename std::map<std::size_t, semiring_elt_t>::iterator it = lit->second[i].begin();
	       it != lit->second[i].end(); it++)
	    std::cout << it->first << " : " << it->second << " // ";
	  std::cout << std::endl;
	}
      }

      std::cout << "Initial : ";
      for (std::size_t i = 0; i < init_.size(); i++)
	if (init_[i] != semiring_elt_zero_)
	  std::cout << i << " : " << init_[i] << " // ";
      std::cout << std::endl;

      std::cout << "Final : ";
      for (std::size_t i = 0; i < final_.size(); i++)
	if (final_[i] != semiring_elt_zero_)
	  std::cout << i << " : " << final_[i] << " // ";
      std::cout << std::endl;
      /* DEBUG */
    }

  private:
    // zero and identity of used algebraic structure.
    series_set_elt_t	null_series_;
    semiring_elt_t	semiring_elt_zero_;
    semiring_elt_t	semiring_elt_one_;
    monoid_elt_t	monoid_identity_;

    // Automaton in matrix form
    semiring_vector_t init_;
    semiring_vector_t final_;
    semiring_matrix_set_t letter_matrix_set_;
    size_t nb_states_;

    automaton_t& output_;
  };


  template<typename A, typename AI>
  Element<A, AI>
  reduce(const Element<A, AI>& a, misc::direction_type dir)
  {
    Element<A, AI> output(a.structure());
    reducer<A, AI> r(a, output);
    if (dir == misc::backward)
      r.transpose();
    r.left_reduce();
    r.transpose();
    r.left_reduce();
    if (dir == misc::forward)
      r.transpose();
    r.release();
    return output;
  }

  template<typename A, typename AI>
  void
  reduce_here(Element<A, AI>& a, misc::direction_type dir)
  {
    reducer<A, AI> r(a, a);
    if (dir == misc::backward)
      r.transpose();
    r.left_reduce();
    r.transpose();
    r.left_reduce();
    if (dir == misc::forward)
      r.transpose();
    r.release();
  }

} // vcsn

#endif // !VCSN_ALGORITHMS_REDUCE_HXX //
