// extension.hxx: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGORITHMS_EXTENSION_HXX
# define VCSN_ALGORITHMS_EXTENSION_HXX

# include <vaucanson/algorithms/extension.hh>

# include <vaucanson/tools/usual_macros.hh>

using namespace std;

namespace vcsn {

  template <typename S, typename T, typename Auto_t>
  typename identity_transducer_helper<S, T>::ret
  do_extension(const AutomataBase<S>& s,
	       const Auto_t& a)
  {
    AUTOMATON_TYPES(Auto_t);
    // ret_t is the type of the transducer returned.
    typedef typename identity_transducer_helper<S, T>::ret    ret_t;

    AUTOMATON_TYPES_(ret_t, t_);
    typedef typename ret_t::set_t                 set_t;
    typedef typename set_t::series_t              o_series_t;
    typedef typename ret_t::series_elt_t               output_series_elt_t;
    typedef typename series_elt_t::support_t           support_t;

    set_t          ts(o_series_t(a.set().series(), a.set().series().monoid()));
    ret_t          t_ret(ts);

    monoid_elt_t   neutre   = a.series().monoid().empty_;
    monoid_elt_t   t_neutre =
      t_ret.series().monoid()
      .identity(SELECT(typename t_monoid_elt_t::value_t));

    vector<hstate_t>    conv(a.states().size());

    for_each_state(s, a)
      conv[t_ret.add_state()] = *s;

    for_each_edge(e, a)
      {
	series_elt_t t = a.series_of(*e);
	series_elt_t s(t);
	output_series_elt_t os(t_ret.set().series());
	support_t supp = s.supp();
	for_each_const_(support_t, m, supp)
	  {
	    series_elt_t tmp(a.set().series());
	    // try to associate the neutral monoid element with a weight
	    // to create a series which will be a weight in the series os
	    tmp.assoc(neutre, s.get(*m));
	    os.assoc(*m, tmp);
	  }
	hedge_t f = t_ret.add_series_edge(conv[a.origin_of(*e)],
					 conv[a.aim_of(*e)],
					 os);
      }

    for_each_initial_state(i, a)
      {
	series_elt_t a_series = a.get_initial(*i);
	t_series_elt_t s;
	s.value_set(t_neutre, a_series);
	t_ret.set_initial(conv[*i], s);
      }

    for_each_final_state(f, a)
      {
	series_elt_t a_series = a.get_final(*f);
	t_series_elt_t s;
	s.value_set(t_neutre, a_series);
	t_ret.set_final(conv[*f], s);
      }

    return t_ret;
  }

  template<typename S, typename T>
  typename identity_transducer_helper<S, T>::ret extension(const Element<S, T>& a)
  {
    return do_extension(a.set(), a);
  }

  ////////////////////////////////////////////////////////////

  template<typename SA, typename ST, typename Auto_t, typename Trans_t>
  Trans_t do_extension(const AutomataBase<SA>&,
		       const TransducerBase<ST>&,
		       const Auto_t& a,
		       const Trans_t& t)
  {
    AUTOMATON_TYPES_(Trans_t, t_);
    AUTOMATON_TYPES_(Auto_t, a_);
    typedef typename Trans_t::series_elt_t            t_output_series_elt_t;
    typedef typename Auto_t::series_elt_t::support_t  a_support_t;
    typedef typename Trans_t::semiring_elt_t	      t_weight_t;

    Trans_t                   tt(t.set());
    map<hstate_t, hstate_t>   conv;

    a_monoid_elt_t a_neutre =
      a.series().monoid().identity(SELECT(typename a_monoid_elt_t::value_t));
    t_monoid_elt_t t_neutre =
      t.series().monoid().identity(SELECT(typename t_monoid_elt_t::value_t));

    for(a_state_iterator p = a.states().begin(); p != a.states().end(); ++p)
      conv[*p] = tt.add_state();

    // convert edges
    for(a_edge_iterator e = a.edges().begin(); e != a.edges().end(); ++e)
      {
	a_series_elt_t s_ = a.series_of(*e);
	a_series_elt_t s(s_);

	t_output_series_elt_t os(t.set().series());

	a_support_t supp = s.supp();
	for(typename a_support_t::const_iterator m = supp.begin();
	    m != supp.end(); ++m)
	  {
	    t_weight_t tmp(t.set().series().semiring());
	    tmp.assoc(a_neutre, s.get(*m));
	    os.assoc(a_monoid_elt_t (a.set().series().monoid(), *m), tmp);
	  }

	tt.add_series_edge(conv[a.origin_of(*e)], conv[a.aim_of(*e)], os);
      }

    for(a_initial_iterator p = a.initial().begin();
	p != a.initial().end();
	++p)
      {
	a_series_elt_t a_series = a.get_initial(*p);
	t_series_elt_t s (t.set().series());
	s.assoc(t_neutre, a_series);
	tt.set_initial(conv[*p], s);
      }

    for(a_final_iterator p = a.final().begin();
	p != a.final().end();
	++p)
      {
	a_series_elt_t a_series = a.get_final(*p);
	t_series_elt_t s (t.set().series());
	s.assoc(t_neutre, a_series);
	tt.set_final(conv[*p], s);
      }

    return tt;
  }

  template<typename SA, typename TA, typename ST, typename TT>
  Element<ST, TT> extension(const Element<SA, TA>& a, const Element<ST, TT>& t)
  {
    return do_extension(a.set(), t.set(), a, t);
  }

}

#endif //VCSN_ALGORITHMS_EXTENSION_HXX
