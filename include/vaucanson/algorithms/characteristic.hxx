// characteristic.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2011 The Vaucanson Group.
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

# include <vaucanson/design_pattern/design_pattern.hh>
# include <vaucanson/automata/concept/automata.hh>
# include <map>

namespace vcsn
{
  template<typename lhs_t, typename rhs_t>
  void characteristic(lhs_t& dst, const rhs_t& from)
  {
    std::map<typename rhs_t::hstate_t, typename lhs_t::hstate_t> stmap;

    for (typename rhs_t::state_iterator i = from.states().begin();
         i != from.states().end(); ++i)
      {
	typename lhs_t::hstate_t s = dst.add_state();
	if (from.is_final(*i))
	  dst.set_final(s);
	if (from.is_initial(*i))
	  dst.set_initial(s);
	stmap[*i] = s;
      }

    typedef typename lhs_t::semiring_elt_t semiring_elt_t;
    semiring_elt_t one(dst.series().semiring().wone_);
    for (typename rhs_t::transition_iterator i = from.transitions().begin();
         i != from.transitions().end(); ++i)
      {
	typename rhs_t::series_set_elt_t label(from.series_of(*i));

	int size = label.supp().size();
	if (size > 0)
	  {
	    typename rhs_t::series_set_elt_t::support_t::const_iterator m =
	      label.supp().begin();
	    for (int j = 0; j < size; ++j, ++m)
	      {
		typename lhs_t::series_set_elt_t
		  series(dst.structure().series());
		typename lhs_t::monoid_elt_t
		  mv(dst.structure().series().monoid());
		mv = *m;
		series.assoc(mv, one);
		dst.add_series_transition(stmap[from.src_of(*i)],
					  stmap[from.dst_of(*i)], series);
	      }
        }
      }
  }

} // ! vcsn
