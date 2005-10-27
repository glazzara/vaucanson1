// letter_to_letter_composition.hxx: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
    transducer_t output(s);
    delta_ret_t f_delta_ret, g_delta_ret;
    assoc_t conv;
    series_set_elt_t zero =
      algebra::zero_as<series_set_elt_value_t>::of(output.series());

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
	    series_set_elt_t l = f.series_of(*lhs_e);
	    for_all_const_(delta_ret_t, rhs_e, g_delta_ret)
	      {
		series_set_elt_t l_ = g.series_of(*rhs_e);
		series_set_elt_t l__(series);
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

#endif // ! VCSN_ALGORITHMS_LETTER_TO_LETTER_COMPOSITION_HXX
