// backward_closure.hxx: this file is part of the Vaucanson project.
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
    typedef std::vector<std::vector<semiring_elt_t> >         matrix_semiring_elt_t;
    typedef std::vector<std::vector<series_elt_t> >     matrix_series_t;
    typedef std::vector<semiring_elt_t>                       matrix_semiring_elt_final_t;

    series_elt_t          serie_identity  = a.series().zero_; 
    semiring_elt_t	          semiring_elt_zero     = a.series().semiring().wzero_; 
    monoid_elt_t          monoid_identity = a.series().monoid().empty_; 
    
    int                   i, j, k, size = a.states().size();

    matrix_series_t       m_series(size), m_series_ret(size);
    matrix_semiring_elt_t       m_semiring_elt(size), m_semiring_elt_tmp(size);
    matrix_semiring_elt_final_t m_wfinal(size), m_wfinal_tmp(size);
    
    for (i = 0; i < size; i++){
      m_semiring_elt[i].resize(size, semiring_elt_t(a.series().semiring()));
      m_semiring_elt_tmp[i].resize(size, semiring_elt_t(a.series().semiring()));
      m_series[i].resize(size, series_elt_t(a.series()));
      m_series_ret[i].resize(size, series_elt_t(a.series()));
    }

    /// @bug FIXME: This converters should be removed
    // Initialize converters between matrix index and states.
    std::vector<hstate_t>	index_to_state(size);
    std::map<hstate_t, int>	state_to_index;
    i = 0;
    for_each_state(s, a)
    {
      index_to_state[i] = *s;
      state_to_index[*s] = i++;
    }
    
    // Initialize the matrix m_semiring_elt, m_series and m_series_ret with
    // the original automaton
    std::list<hedge_t> to_remove;
    for_each_edge(e, a)
      {
	int aim = state_to_index[a.aim_of(*e)];
	int origin = state_to_index[a.origin_of(*e)];
	m_semiring_elt[origin][aim] += a.serie_of(*e).get(monoid_identity);
	m_series[origin][aim] += a.serie_of(*e);
	m_series[origin][aim].value_set(monoid_identity.value(),
					semiring_elt_zero.value());
	m_series_ret[origin][aim] = m_series[origin][aim];
	to_remove.push_back(*e);
      }
    for_each_const_(std::list<hedge_t>, e, to_remove)
      	a.del_edge(*e);

    // Initialize the m_wfinal, m_wfinal_tmp
    for_each_final_state(p, a)
      {
	int pos = state_to_index[*p];
	m_wfinal[pos] = a.get_final(*p).get(monoid_identity);
	m_wfinal_tmp[pos] = m_wfinal[pos];
      }
        
    // Compute star(m_semiring_elt)
    for (int r = 0; r < size; r++)
      {
	if (!m_semiring_elt[r][r].starable())
	  { 
	    // FIXME: add error handling.
	    std::cerr<< "Star not defined." << std::endl;
	    return;
	  }	
	semiring_elt_t        w_tmp   = m_semiring_elt[r][r];
	semiring_elt_t        w       = w_tmp.star();
	for (i = 0; i < size; i++)
	  for (j = 0; j < size; j++)
	    m_semiring_elt_tmp[i][j] = 
	      m_semiring_elt[i][j] + m_semiring_elt[i][r] * w * m_semiring_elt[r][j]; 
	m_semiring_elt = m_semiring_elt_tmp;
    }

    // Compute star(m_semiring_elt)*m_series, star(m_semiring_elt)*m_wfinal and
    // delete all spontaneous edges.
    for (i = 0; i < size; i++){
      for (j = 0; j < size; j++){
	for (k = 0; k < size; k++)
	  m_series_ret[i][j] += m_semiring_elt[i][k]*m_series[k][j]; 
	
	if (m_series_ret[i][j] != serie_identity)
	  a.add_serie_edge(index_to_state[i],
			   index_to_state[j],
			   m_series_ret[i][j]); 

	m_wfinal[i] += m_semiring_elt[i][j] * m_wfinal_tmp[j];
      } 
      
      if (m_wfinal[i] != semiring_elt_zero)
	a.set_final(index_to_state[i],
		    series_elt_t(a.series(), m_wfinal[i]));
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
