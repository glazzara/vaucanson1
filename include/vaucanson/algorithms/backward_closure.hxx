// backward_closure.hxx
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

#ifndef VCSN_ALGORITHMS_BACKWARD_CLOSURE_HXX
# define VCSN_ALGORITHMS_BACKWARD_CLOSURE_HXX

# include <set>
# include <vector>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/automata/concept/automata_base.hh>

# include <vaucanson/algorithms/backward_closure.hh> 

namespace vcsn {

  /*-----------------.
  | backward closure |
  `-----------------*/
  // Algorithm based on Floyd/McNaughton/Yamada
  // author: Thanh-Hoc NGUYEN
  template <class A_, typename Auto>
  void
  do_backward_closure_here(const AutomataBase<A_>&,
			   Auto&			   a)
  {
    AUTOMATON_TYPES(Auto);
    typedef std::vector<std::vector<weight_t> >         matrix_weight_t;
    typedef std::vector<std::vector<series_elt_t> >     matrix_series_t;
    typedef std::vector<weight_t>                       matrix_weight_final_t;

    series_elt_t          serie_identity  = a.series().zero_; 
    weight_t	          weight_zero     = a.series().weights().wzero_; 
    monoid_elt_t          monoid_identity = a.series().monoid().empty_; 
    
    int                   i, j, k, size = a.states().size();

    matrix_series_t       m_series(size), m_series_ret(size);
    matrix_weight_t       m_weight(size), m_weight_tmp(size);
    matrix_weight_final_t m_wfinal(size), m_wfinal_tmp(size);
    
    for (i = 0; i < size; i++){
      m_weight[i].resize(size);
      m_weight_tmp[i].resize(size);
      m_series[i].resize(size);
      m_series_ret[i].resize(size);
    }
    
    // Initialize the matrix m_weight, m_series and m_series_ret with
    // the original automaton
    for_each_edge(e, a)
      {
	hstate_t aim = a.aim_of(*e);
	hstate_t origin = a.origin_of(*e);
	m_weight[origin][aim] += a.serie_of(*e).get(monoid_identity);
	m_series[origin][aim] += a.serie_of(*e);
	m_series[origin][aim].value_set(monoid_identity.value(),
					weight_zero.value());
	m_series_ret[origin][aim] = m_series[origin][aim];
	a.del_edge(*e);
      }

    // Initialize the m_wfinal, m_wfinal_tmp
    for_each_final_state(p, a)
      {
	m_wfinal[*p] = a.get_final(*p).get(monoid_identity);
	m_wfinal_tmp[*p] = m_wfinal[*p];
      }
        
    // Compute star(m_weight)
    for (int r = 0; r < size; r++)
      {
	if (!m_weight[r][r].stareable())
	  { 
	    // FIXME: add error handling.
	    std::cerr<< "Star not defined." << std::endl;
	    return;
	  }	
	weight_t        w_tmp   = m_weight[r][r];
	weight_t        w       = w_tmp.star();
	for (i = 0; i < size; i++)
	  for (j = 0; j < size; j++)
	    m_weight_tmp[i][j] = 
	      m_weight[i][j] + m_weight[i][r] * w * m_weight[r][j]; 
	m_weight = m_weight_tmp;
    }

    // Compute star(m_weight)*m_series, star(m_weight)*m_wfinal and
    // delete all spontaneous edges.
    for (i = 0; i < size; i++){
      for (j = 0; j < size; j++){
	for (k = 0; k < size; k++)
	  m_series_ret[i][j] += m_weight[i][k]*m_series[k][j]; 
	
	if (m_series_ret[i][j] != serie_identity)
	  a.add_serie_edge(i, j, m_series_ret[i][j]); 

	m_wfinal[i] += m_weight[i][j] * m_wfinal_tmp[j];
      } 
      
      if (m_wfinal[i] != weight_zero)
	a.set_final(i, series_elt_t(m_wfinal[i]));
    } 
  }
  
  template<typename  A, typename  T>
  void
  backward_closure_here(Element<A, T>& a)
  {
    // FIXME: here, Hoc wrote : "a.renumber_states();"
    do_backward_closure_here(a.set(), a);
  }
  
  template<typename  A, typename  T>
  Element<A, T>
  backward_closure(const Element<A, T>& a)
  {
    Element<A, T> ret(a);
    do_backward_closure_here(ret.set(), ret);
    return ret;
  }

} // vcsn

#endif // VCSN_ALGORITHMS_BACKWARD_CLOSURE_HXX
