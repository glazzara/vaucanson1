// outsplitting.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_ALGORITHMS_OUTSPLITTING_HXX
# define VCSN_ALGORITHMS_OUTSPLITTING_HXX


/**
  * @file outsplitting.hxx
  *
  * @brief Outsplitting and insplitting algorithms for normalized and
  * sub-normalized transducers seen as automata over a free monoid
  * product.
  *
  * @author Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
  */

# include <vaucanson/algorithms/outsplitting.hh>
# include <vaucanson/algebra/implementation/series/series.hh>

namespace vcsn {

  /// Separate states considering their output:
  /// a|1 on one state,
  /// 1|x and a|x on the other.

  template <typename Auto_t>
  static Auto_t
  outsplitting(const Auto_t& aut, std::set<hstate_t>& m)
  {
    AUTOMATON_TYPES(Auto_t);

    typedef typename series_set_elt_t::support_t	support_t;

    typedef typename monoid_t::second_monoid_t	second_monoid_t;

    typedef typename monoid_elt_value_t::second_type
						second_monoid_elt_value_t;
    typedef Element<second_monoid_t, second_monoid_elt_value_t>
						second_monoid_elt_t;

    typedef std::set<hedge_t>			set_of_edges_t;



    second_monoid_elt_t second_identity =
      algebra::identity_as<second_monoid_elt_value_t>::
      of(aut.structure().series().monoid().second_monoid());

    Auto_t res(aut);

    const series_set_t&	series   = res.structure().series();
    const monoid_t&	monoid   = series.monoid();



    for_each_state(s, res)
      {
	bool eps_out = false;
	bool other_out = false;
	bool diff = false;

	// Test whether there are different types of outgoing transitions.

	set_of_edges_t edges;
	res.deltac(edges, *s, delta_kind::edges());
	for_each_const_(set_of_edges_t, e, edges)
	  {
	    const series_set_elt_t	series  = res.series_of(*e);
	    support_t			supp = series.supp();
	    const monoid_elt_t		supp_elt (monoid, *(supp.begin()));

	    if (supp_elt.value().second == second_identity.value())
	      eps_out = true;
	    else
	      other_out = true;
	    if (eps_out and other_out)
	      {
		diff = true;
		break;
	      }
	  }

	if (eps_out and not diff)
	  m.insert(*s);

	// If there are different types of outgoing transitions.
	if (diff)
	  {
	    hstate_t s2 = res.add_state();
	    if (res.is_initial(*s))
	      res.set_initial(s2, res.get_initial(*s));

	    set_of_edges_t in_edges;
	    res.rdeltac(in_edges, *s, delta_kind::edges());

	    for_each_(set_of_edges_t, e, in_edges)
	      res.add_series_edge(res.origin_of(*e), s2, res.series_of(*e));

	    for_each_const_(set_of_edges_t, e, edges)
	      {
		const series_set_elt_t	series  = res.series_of(*e);
		support_t		supp = series.supp();
		const monoid_elt_t	supp_elt (monoid, *(supp.begin()));

		if (supp_elt.value().second == second_identity.value())
		  {
		    res.add_series_edge(s2, res.aim_of(*e), res.series_of(*e));
		    res.del_edge(*e);
		  }
	      }
	    m.insert(s2);
	  }
      }
    return res;
  }


  /// Separate states considering their input:
  /// 1|x on one state,
  /// a|1 and a|x on the other.

  template <typename Auto_t>
  static Auto_t
  insplitting(const Auto_t& aut, std::set<hstate_t>& m)
  {
    AUTOMATON_TYPES(Auto_t);

    typedef typename series_set_elt_t::support_t	support_t;

    typedef typename monoid_t::first_monoid_t	first_monoid_t;

    typedef typename monoid_elt_value_t::first_type
						first_monoid_elt_value_t;
    typedef Element<first_monoid_t, first_monoid_elt_value_t>
						first_monoid_elt_t;

    typedef std::set<hedge_t>			set_of_edges_t;



    first_monoid_elt_t first_identity =
      algebra::identity_as<first_monoid_elt_value_t>::
      of(aut.structure().series().monoid().first_monoid());

    Auto_t res(aut);

    const series_set_t&	series   = res.structure().series();
    const monoid_t&	monoid   = series.monoid();



    for_each_state(s, res)
      {
	bool eps_in = false;
	bool other_in = false;
	bool diff = false;

	// Test whether there are different types of incoming transitions.

	set_of_edges_t edges;
	res.rdeltac(edges, *s, delta_kind::edges());
	for_each_const_(set_of_edges_t, e, edges)
	  {
	    const series_set_elt_t	series  = res.series_of(*e);
	    support_t			supp = series.supp();
	    const monoid_elt_t		supp_elt (monoid, *(supp.begin()));

	    if (supp_elt.value().first == first_identity.value())
	      eps_in = true;
	    else
	      other_in = true;
	    if (eps_in and other_in)
	      {
		diff = true;
		break;
	      }
	  }

	if (eps_in and not diff)
	  m.insert(*s);

	// If there are different types of incoming transitions.
	if (diff)
	  {
	    hstate_t s2 = res.add_state();
	    if (res.is_final(*s))
	      res.set_final(s2, res.get_final(*s));

	    set_of_edges_t out_edges;
	    res.deltac(out_edges, *s, delta_kind::edges());

	    for_each_(set_of_edges_t, e, out_edges)
	      res.add_series_edge(s2, res.aim_of(*e), res.series_of(*e));

	    for_each_const_(set_of_edges_t, e, edges)
	      {
		const series_set_elt_t	series  = res.series_of(*e);
		support_t		supp = series.supp();
		const monoid_elt_t	supp_elt (monoid, *(supp.begin()));

		if (supp_elt.value().first == first_identity.value())
		  {
		    res.add_series_edge(res.origin_of(*e), s2,
					res.series_of(*e));
		    res.del_edge(*e);
		  }
	      }
	    m.insert(s2);
	  }
      }
    return res;
  }


} // End of namespace vcsn.

# endif // ! VCSN_ALGORITHMS_OUTSPLITTING_HXX
