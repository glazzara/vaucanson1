// projection.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGORITHMS_PROJECTION_HXX
#define  VCSN_ALGORITHMS_PROJECTION_HXX

#include <vaucanson/algorithms/projection.hh>
//#include <vaucanson/algorithms/krat_exp_print.hh>

namespace vcsn {

  template<typename ST, typename SA,
	   typename Trans_t, typename Auto_t>
  void 
  do_output_projection(const TransducerBase<ST>&,
		       const AutomataBase<SA>&,
		       const Trans_t& t,
		       Auto_t& ret)
  {
    AUTOMATON_TYPES(Trans_t);

    map<hstate_t, hstate_t> m;
    
    for_each_state(p, t)
      m[*p] = ret.add_state();

    monoid_elt_t empty = 
      algebra::identity_as<monoid_elt_value_t>::of(t.series().monoid());
    for_each_initial_state(p, t)
      {
	ret.set_initial(m[*p], t.get_initial(*p).get(empty)); 
      }
    
    for_each_final_state(p, t)
      ret.set_final(m[*p], t.get_final(*p).get(empty));

    for_each_edge(e, t)
      {
	hedge_t re = ret.add_serie_edge(m[t.origin_of(*e)], 
					m[t.aim_of(*e)], 
					t.output_of(*e));
      }
  }

  template <class ST, class TT,
	    class SA, class TA>
  void
  output_projection(const Element<ST, TT>& t, 
		    Element<SA, TA>& a)
  {
    return do_output_projection(t.set(), a.set(), t, a);
  }
  
  ////////////////////////////////////////////////////////////

  template <typename S, typename T>
  typename output_projection_helper<S, T>::ret
  do_output_projection(const TransducerBase<S>&,
		       const Element<S, T>& t,
		       std::map<hstate_t, hstate_t>& m_)
  {
    using namespace std;
    typedef Element<S, T>  Trans_t;
    AUTOMATON_TYPES(Trans_t);

    typedef typename output_projection_helper<S, T>::ret    Auto_t;
    typedef typename Auto_t::set_t                   Auto_set_t;
    typedef typename Auto_set_t::series_t            Auto_series_t;

    Auto_set_t   auto_set(Auto_series_t(t.set().series().semiring()));
    Auto_t       ret(auto_set);

    monoid_elt_t empty = t.series().monoid().empty_;
    std::map<hstate_t, hstate_t> m;

    for_each_state(p, t)
      {
	m[*p] = ret.add_state();
	m_[m[*p]] = *p;
      }

    for_each_initial_state(p, t)
      ret.set_initial(m[*p], t.get_initial(*p).get(empty));    

    for_each_final_state(p, t)
      ret.set_final(m[*p], t.get_final(*p).get(empty));

    for_each_edge(e, t)
      ret.add_serie_edge(m[t.origin_of(*e)], m[t.aim_of(*e)], t.output_of(*e));
    
    return ret;
  }

  template <typename S, typename T>
  typename output_projection_helper<S,T>::ret
  output_projection(const Element<S, T>& t,
		    std::map<hstate_t, hstate_t>& m)
  {
    return do_output_projection(t.set(), t, m);
  }

  template <typename S, typename T>
  typename output_projection_helper<S,T>::ret
  output_projection(const Element<S, T>& t)
  {
    std::map<hstate_t, hstate_t> m;
    return do_output_projection(t.set(), t, m);
  }
}

#endif //  VCSN_ALGORITHMS_PROJECTION_HXX
