// cut_up.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2005 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//

#ifndef VCSN_ALGORITHMS_CUT_UP_HXX
# define VCSN_ALGORITHMS_CUT_UP_HXX

/**
 * @file cut_up.hxx
 *
 * Cut-up algorithm.
 *
 * @author Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
 */


namespace vcsn {


  /*--------------------------------.
  | Check if an automaton is cut up |
  `--------------------------------*/

  template <class S, class T>
  bool is_cut_up(const Element<S, T>& a)
  {
    typedef Element<S, T> automaton_t;
    AUTOMATON_TYPES(automaton_t);

    for_each_edge(e, a)
      if (! a.series_of(*e).is_finite_app() ||
	  a.series_of(*e).supp().size() > 1)
	return false;

    return true;
  }


  /*----------------------------------------------.
  | Specialization for label with rational series |
  `----------------------------------------------*/

  template <class S, class T, class TT, class Auto, class Ret>
  void do_cut_up(const AutomataBase<S>&,
		 const rat::exp<T, TT>&,
		 const Auto& a,
		 Ret& res)
  {
    AUTOMATON_TYPES(Ret);
    typedef typename generalized_traits<Ret>::automaton_t gen_automaton_t;

    auto_copy(res, a);

    std::map<hstate_t, hstate_t> statemap;

    edges_t		edges = res.value().edges();

    for_each_(edges_t, e, edges)
      {
	if (! res.series_of(*e).is_finite_app() ||
	    res.series_of(*e).supp().size() > 1)
	  {
	    gen_automaton_t tmp(res.structure());
	    standard_of(tmp, res.series_of(*e).value());

	    for_each_state(s, tmp)
	      statemap[*s] = res.add_state();

	    for_each_initial_state(i, tmp)
	      res.add_series_edge(res.origin_of(*e),
				  statemap[*i],
				  tmp.get_initial(*i));

	    for_each_edge(ed, tmp)
	      res.add_edge(statemap[tmp.origin_of(*ed)],
			   statemap[tmp.aim_of(*ed)],
			   tmp.label_of(*ed));

	    for_each_final_state(f, tmp)
	      res.add_series_edge(statemap[*f], res.aim_of(*e),
				  tmp.get_final(*f));

	    res.del_edge(*e);
	  }
      }
  }


  /*------------------------------------------------.
  | Specialization for label with polynomial series |
  `------------------------------------------------*/

  template <class S, class T, class TT, class Auto, class Ret>
  void do_cut_up(const S&,
		 const algebra::polynom<T, TT>&,
		 const Auto& a,
		 Ret& res)
  {
    hstate_t			s0;
    hstate_t			s1;
    int				size;
    typedef typename Ret::series_set_elt_t series_set_elt_t;
    typedef typename series_set_elt_t::support_t support_t;
    typedef typename Ret::value_t::edges_t edges_t;

    auto_copy(res, a);

    edges_t		edges = res.value().edges();

    for_each_(edges_t, e, edges)
      {
	series_set_elt_t label(res.structure().series());
	label = res.series_of(*e);

	if ((size = label.supp().size()) > 1)
	  {
	    typename support_t::const_iterator m = label.supp().begin();
	    s1 = res.add_state();
	    series_set_elt_t series_start(res.structure().series());
	    series_start.assoc(*m, label.get(*m));
	    res.add_series_edge(res.origin_of(*e), s1, series_start);
 	    m++;

	    for (int i = 1; i < size - 1; ++i, ++m)
	      {
		s0 = s1;
		s1 = res.add_state();
		series_set_elt_t series(res.structure().series());
		series.assoc(*m, label.get(*m));
		res.add_series_edge(s0, s1, series);
	      }

	    series_set_elt_t series_end(res.structure().series());
	    series_end.assoc(*m, label.get(*m));
	    res.add_series_edge(s1, res.aim_of(*e), series_end);

	    res.del_edge(*e);
	  }
      }
  }


  /*---------.
  | Wrappers |
  `---------*/

  template <class S, class T>
  Element<S, T>
  cut_up(const Element<S, T>& a)
  {
    typedef typename Element<S, T>::series_set_elt_t::value_t series_impl_t;

    Element<S, T> res(a.structure());
    do_cut_up(a.structure(),SELECT(series_impl_t), a, res);

    return res;
  }


  template <class S, class T>
  void
  cut_up(const Element<S, T>& a, Element<S, T>& res)
  {
    typedef typename Element<S, T>::series_set_elt_t::value_t series_impl_t;

    do_cut_up(a.structure(), SELECT(series_impl_t), a, res);
  }


  template <class S, class T>
  void
  cut_up_here(Element<S, T>& a)
  {
    typedef typename Element<S, T>::series_set_elt_t::value_t series_impl_t;

    Element<S, T> res(a.structure());
    do_cut_up(a.structure(),SELECT(series_impl_t), a, res);

    a = res;
  }

  
} // ! vcsn


#endif // VCSN_ALGORITHMS_CUT_UP_HXX
