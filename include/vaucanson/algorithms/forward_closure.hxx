// forward_closure.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003, 2004 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_FORWARD_CLOSURE_HXX
# define VCSN_ALGORITHMS_FORWARD_CLOSURE_HXX

# include <vaucanson/algorithms/forward_closure.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <vector>

namespace vcsn {

  /*------------------.
  | forward closure   |
  `------------------*/
  // Algorithm based on Floyd/McNaughton/Yamada
  // author: Thanh-Hoc NGUYEN
  template <class A_, typename Auto>
  void
  do_forward_closure_here(const AutomataBase<A_>&,
			  Auto&			   a)
  {
    AUTOMATON_TYPES(Auto);
    typedef std::vector<std::vector<semiring_elt_t> >        matrix_semiring_elt_t;
    typedef std::vector<std::vector<series_elt_t> >    matrix_series_t;
    typedef std::vector<semiring_elt_t>                      matrix_semiring_elt_initial_t;

    series_elt_t            series_identity  = a.series().zero_;
    semiring_elt_t	    semiring_elt_zero     = a.series().semiring().wzero_;
    monoid_elt_t            monoid_identity = a.series().monoid().empty_;

    int                     i, j, k, size = a.states().size();

    matrix_series_t         m_series(size), m_series_ret(size);
    matrix_semiring_elt_t   m_semiring_elt(size), m_semiring_elt_tmp(size);
    matrix_semiring_elt_initial_t m_winitial(size), m_winitial_tmp(size);

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

    // Initialize the matrix m_semiring_elt, m_series, m_winitial and
    // m_series_ret with the original automaton
    std::list<hedge_t> to_remove;
    for_each_edge(e, a)
      {
	int origin = state_to_index[a.origin_of(*e)];
	int aim = state_to_index[a.aim_of(*e)];
	m_semiring_elt[origin][aim] += a.series_of(*e).get(monoid_identity);
	m_series[origin][aim] += a.series_of(*e);
	m_series[origin][aim].assoc(monoid_identity.value(),
				    semiring_elt_zero.value());
	m_series_ret[origin][aim] = m_series[origin][aim];
	to_remove.push_back(*e);
      }
    for_each_const_(std::list<hedge_t>, e, to_remove)
      a.del_edge(*e);

    // Initialize the matrix m_winitial and m_winitial_tmp
    for_each_initial_state(p, a)
      {
	int pos = state_to_index[*p];
	m_winitial[pos] = a.get_initial(*p).get(monoid_identity);
	m_winitial_tmp[pos] = m_winitial[pos];
      }

    // Compute star(m_semiring_elt)
    for (int r = 0; r < size; r++)
      {
	if (! m_semiring_elt[r][r].starable())
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

    // Compute m_winitial*star(m_semiring_elt), m_series*star(m_semiring_elt)
    // and remove all spontaneous edges.
    for (i = 0; i < size; i++){
      for (j = 0; j < size; j++){
	for (k = 0; k < size; k++)
	  m_series_ret[j][i] += m_series[j][k]*m_semiring_elt[k][i];

	if (m_series_ret[j][i] != series_identity)
	  a.add_series_edge(index_to_state[j],
			   index_to_state[i],
			   m_series_ret[j][i]);

	m_winitial[i] += m_winitial_tmp[j]*m_semiring_elt[j][i];
      }
      if (m_winitial[i] != semiring_elt_zero)
	a.set_initial(index_to_state[i],
		      series_elt_t(a.series(), m_winitial[i]));
    }
  }

  template<typename  A, typename  T>
  void
  forward_closure_here(Element<A, T>& a)
  {
    // FIXME: Hoc wrote "a.renumber_states();" here.
    do_forward_closure_here(a.structure(), a);
  }

  template<typename  A, typename  T>
  Element<A, T>
  forward_closure(const Element<A, T>& a)
  {
    Element<A, T> ret(a);
    do_forward_closure_here(ret.structure(), ret);
    return ret;
  }

} // vcsn

#endif // VCSN_ALGORITHMS_FORWARD_CLOSURE_HXX
