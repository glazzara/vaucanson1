// letter_to_letter_composition.hxx:this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_LETTER_TO_LETTER_COMPOSITION_HXX
# define VCSN_ALGORITHMS_LETTER_TO_LETTER_COMPOSITION_HXX

# include <vaucanson/automata/concept/transducer_base.hh>
# include <vaucanson/tools/usual_macros.hh>

# include <set>
# include <map>

namespace vcsn {


  template <class Self, class T>
  Element<Self, T>
  do_letter_to_letter_composition(const TransducerBase<Self>& s,
				  const Element<Self, T>& f,
				  const Element<Self, T>& g)
  {
    typedef Element<Self, T> transducer_t;
    AUTOMATON_TYPES(transducer_t);
    typedef std::map<std::pair<hstate_t, hstate_t>, hstate_t> assoc_t;
    typedef std::set<hedge_t> delta_ret_t;

    semiring_t output_series(f.series().semiring().semiring(),
			     f.series().semiring().monoid());
    series_set_t series(output_series, g.series().monoid());
    automata_set_t structure(series);
    transducer_t output(set);
    delta_ret_t f_delta_ret, g_delta_ret;
    assoc_t conv;
    series_elt_t zero = algebra::zero_as<series_value_t>::of(output.series());

    for_each_state(s, f)
      for_each_state(t, g)
      {
	hstate_t ns = output.add_state();
	conv[std::make_pair(*s, *t)] = ns;
	output.set_initial(ns,
			   f.get_initial(*s) * g.get_initial(*t));
	output.set_final(ns,
			 f.get_final(*s) * g.get_final(*t));

      }

    for_each_state(s, f)
      for_each_state(t, g)
      {
	f_delta_ret.clear();
	g_delta_ret.clear();

	f.deltac(f_delta_ret, *s, delta_kind::edges());
	g.deltac(g_delta_ret, *t, delta_kind::edges());

	for_all_const_(delta_ret_t, lhs_e, f_delta_ret)
	  {
	    series_elt_t l = f.series_of(*lhs_e);
	    for_all_const_(delta_ret_t, rhs_e, g_delta_ret)
	      {
		series_elt_t l_ = g.series_of(*rhs_e);
		series_elt_t l__(series);
		typedef typename series_set_t::support_t support_t;
		for_all_const_(support_t, supp, l.supp())
		  {
		    semiring_elt_t ol = l.get(*supp);
		    typedef typename semiring_elt_t::support_t wsupport_t;
		    wsupport_t wsupp = ol.supp();
		    series_set_t ts(series, monoid_elt_t(*supp));
		    for_all_const_(wsupport_t, ss, wsupp)
		      l__ += ts * l_.get(*ss);
		  }
		if (l__ != zero)
		  {
		    output.add_series_edge(conv[std::make_pair(*s, *t)],
					  conv[std::make_pair(f.aim_of(*lhs_e),
							      g.aim_of(*rhs_e))
					  ],
					  l__);
		  }
	      }
	  }
      }
    return output;
  }

  template <class S, class T>
  Element<S, T>
  letter_to_letter_composition(const Element<S, T>& lhs,
			       const Element<S, T>& rhs)
  {
    return do_letter_to_letter_composition(lhs.structure(), lhs, rhs);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_LETTER_TO_LETTER_COMPOSITION_HH
