// infiltration.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_INFILTRATION_HXX
# define VCSN_ALGORITHMS_INFILTRATION_HXX

# include <set>
# include <map>
# include <queue>
# include <stack>

# include <vaucanson/algorithms/infiltration.hh>

# ifndef VCSN_NDEBUG
#  include <vaucanson/algorithms/realtime.hh>
# endif // ! VCSN_NDEBUG

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/automata/implementation/geometry.hh>
# include <vaucanson/misc/static.hh>

namespace vcsn
{

/*--------------------------------.
| Functor for infiltration algorithm.  |
`--------------------------------*/
template<typename A, typename T, typename U>
class Infiltration
{
  public:
    typedef AutomataBase<A> structure_t;
    typedef Element<A, T> lhs_t;
    typedef Element<A, U> rhs_t;
    typedef lhs_t	    output_t;
    typedef std::map<typename output_t::hstate_t,
	      std::pair<typename lhs_t::hstate_t, typename rhs_t::hstate_t> >
			  pair_map_t;

    Infiltration (const structure_t& structure,
	     const bool use_geometry)
      : use_geometry_(use_geometry),
	series_(structure.series()),
	monoid_(series_.monoid()),
	semiring_zero_(series_.semiring().zero(SELECT(semiring_elt_value_t)))
    {
    }

    // returns the infiltration of @c lhs and @c rhs (and put it also in @c output)
    output_t&
    operator() (output_t& output,
		const lhs_t& lhs,
		const rhs_t& rhs,
		pair_map_t& m)
    {
      BENCH_TASK_SCOPED("infiltration");
      visited_.clear();

      precondition(is_realtime(lhs));
      precondition(is_realtime(rhs));

      this->initialize_queue(output, lhs, rhs, m);

      while (not to_process_.empty())
      {
	const pair_hstate_t current_pair = to_process_.front();
	to_process_.pop();

	const hstate_t lhs_s	     = current_pair.first;
	const hstate_t rhs_s	     = current_pair.second;
	const hstate_t current_state = visited_[current_pair];

	output.set_initial(current_state,
			   lhs.get_initial(lhs_s) * rhs.get_initial(rhs_s));
	output.set_final(current_state,
			 lhs.get_final(lhs_s) * rhs.get_final(rhs_s));

        for (typename lhs_t::delta_iterator l(lhs.value(), lhs_s);
             ! l.done();
             l.next())
          for (typename rhs_t::delta_iterator r(rhs.value(), rhs_s);
               ! r.done();
               r.next())
	  {
	    series_set_elt_t	prod_series(series_);

	    if (is_product_not_null(lhs, rhs, l, r, prod_series))
	    {
	      const pair_hstate_t new_pair(lhs.dst_of(*l), rhs.dst_of(*r));
	      typename visited_t::const_iterator found = visited_.find(new_pair);

	      hstate_t dst;
	      if (found == visited_.end())
	      {
		dst = output.add_state();

		this->add_state_to_process(output, lhs, rhs, m, dst, new_pair);
	      }
	      else
		dst = found->second;
	      output.add_series_transition(current_state, dst, prod_series);
	    }
	  }
        for (typename lhs_t::delta_iterator l(lhs.value(), lhs_s);
             ! l.done();
             l.next())
	{
	      const pair_hstate_t new_pair(lhs.dst_of(*l), rhs_s);
	      typename visited_t::const_iterator found = visited_.find(new_pair);

	      hstate_t dst;
	      if (found == visited_.end())
	      {
		dst = output.add_state();

		this->add_state_to_process(output, lhs, rhs, m, dst, new_pair);
	      }
	      else
		dst = found->second;
	      output.add_series_transition(current_state, dst, lhs.series_of(*l));
	}
        for (typename rhs_t::delta_iterator r(rhs.value(), rhs_s);
             ! r.done();
             r.next())
	{
	      const pair_hstate_t new_pair(lhs_s, rhs.dst_of(*r));
	      typename visited_t::const_iterator found = visited_.find(new_pair);

	      hstate_t dst;
	      if (found == visited_.end())
	      {
		dst = output.add_state();

		this->add_state_to_process(output, lhs, rhs, m, dst, new_pair);
	      }
	      else
		dst = found->second;
	      output.add_series_transition(current_state, dst, rhs.series_of(*r));
	}

      }
      merge_transitions(output);
      return output;
    }

  private:
     //merge transitions with the same ends
    void merge_transitions(output_t& a)
    {
      typedef std::map<hstate_t, series_set_elt_t> map_t;
      for_all_states(s, a)
	{
	  map_t map;
	  std::list<htransition_t> transitions;
	  for (delta_iterator e(a.value(), *s); ! e.done(); e.next())
	    {
	      hstate_t target = a.dst_of(*e);
	      transitions.push_back(*e);
	      typename map_t::iterator it = map.find(target);
	      if (it == map.end())
		map.insert(std::pair<hstate_t, series_set_elt_t>(target,
								 a.series_of(*e)));
	      else
		it->second += a.series_of(*e);
	    }
	  for_all_(std::list<htransition_t>, e, transitions)
	    a.del_transition(*e);
	  for_all_(map_t, it, map)
	  	if(it->second != a.series().zero_)
		    a.add_series_transition(*s, it->first, it->second);
	}
    }

    // Some little graphic tools
    class grphx
    {
      public:
	template <typename Output, typename Lhs, typename Rhs>
	static void
	setcoordfrom (Output& a,
		      const Lhs& lhs,
		      const Rhs& rhs,
		      const typename Output::hstate_t state,
		      const typename Lhs::hstate_t x_state,
		      const typename Rhs::hstate_t y_state)
	{
	  typename std::map<typename Lhs::hstate_t,
	    typename Lhs::geometry_t::coords_t>::const_iterator iter;
	  typename std::map<typename Rhs::hstate_t,
	    typename Rhs::geometry_t::coords_t>::const_iterator iter2;
	  double x = 0, y = 0;

	  iter = lhs.geometry().states().find(x_state);
	  if (iter != lhs.geometry().states().end())
	    x = iter->second.first;

	  iter2 = rhs.geometry().states().find(y_state);
	  if (iter2 != rhs.geometry().states().end())
	    y = iter2->second.second;

	  a.geometry().states()[state] = std::make_pair(x, y);
	}
      private:
	// Diagonal alignement with a depth-first traversal
	template<typename I>
	void
	align (const I& a)
	{
	  AUTOMATON_TYPES(I);
	  std::map<hstate_t,bool> visited;
	  std::stack<hstate_t> stack;

	  for_all_const_states(i, a)
	    {
	      visited[*i] = false;
	      // ensure inaccessible states will be visited
	      stack.push(*i);
	    }

	  for_all_const_initial_states(i, a)
	    stack.push(*i);

	  int x = 0;
	  while (!stack.empty())
	  {
	    hstate_t i = stack.top();
	    stack.pop();

	    if (!visited[i])
	    {
	      visited[i] = true;

	      a.geometry()[i] = std::make_pair(x, x);
	      x++;

              for (delta_iterator j(a.value(), i);
                   ! j.done();
                   j.next())
		stack.push(a.dst_of(*j));
	    }
	  }
	}

    };
    class no_grphx
    {
      public:
	template <typename Output, typename Lhs, typename Rhs>
	static void
	setcoordfrom (Output& a,
		      const Lhs& lhs,
		      const Rhs& rhs,
		      const typename Output::hstate_t state,
		      const typename Lhs::hstate_t x_state,
		      const typename Rhs::hstate_t y_state) {};
    };

    // useful typedefs
    AUTOMATON_TYPES(output_t);

    typedef std::pair<typename lhs_t::hstate_t, typename rhs_t::hstate_t>
						      pair_hstate_t;
    typedef std::list<htransition_t>			delta_ret_t;
    typedef std::map<pair_hstate_t, hstate_t>		visited_t;
    typedef typename series_set_elt_t::support_t	support_t;

    // add a @c new_state in the queue
    inline void
    add_state_to_process (output_t& output,
			  const lhs_t& lhs,
			  const rhs_t& rhs,
			  pair_map_t& m,
			  const hstate_t& new_state,
			  const pair_hstate_t& new_pair)
    {
      m[new_state] = new_pair;
      visited_[new_pair] = new_state;
      to_process_.push(new_pair);

# define if_(Cond, ThenClause, ElseClause)			\
misc::static_if_simple<Cond, ThenClause, ElseClause>::t
# define eq_(Type1, Type2)			\
misc::static_eq<Type1, Type2>::value
# define DECLARE_GEOMETRY(Type) \
  typedef geometry<typename Type::hstate_t, typename Type::htransition_t, typename Type::geometry_coords_t> geometry_ ## Type ;

      DECLARE_GEOMETRY(output_t)
      DECLARE_GEOMETRY(lhs_t)
      DECLARE_GEOMETRY(rhs_t)
      if (use_geometry_)
	if_(eq_(typename output_t::geometry_t, geometry_output_t)  and \
	    eq_(typename rhs_t::geometry_t, geometry_rhs_t) and	\
	    eq_(typename lhs_t::geometry_t, geometry_lhs_t),	\
	    grphx, no_grphx)
	  ::setcoordfrom(output, lhs, rhs,
			 new_state, new_pair.first, new_pair.second);
# undef if_
# undef eq_
    }

    // initialize queue with all pairs of intials states from @c lhs and @c rhs
    inline void
    initialize_queue (output_t& output,
		      const lhs_t& lhs,
		      const rhs_t& rhs,
		      pair_map_t& m)
    {
      for_all_const_initial_states(lhs_s, lhs)
	for_all_const_initial_states(rhs_s, rhs)
	{
	  const pair_hstate_t	new_pair(*lhs_s, *rhs_s);
	  const hstate_t	new_state = output.add_state();

	  this->add_state_to_process(output, lhs, rhs, m, new_state, new_pair);
	}
    }

    inline bool
    is_product_not_null (const lhs_t& lhs,
			 const rhs_t& rhs,
			 const typename lhs_t::delta_iterator& l,
			 const typename rhs_t::delta_iterator& r,
			 series_set_elt_t&  prod_series) const
    {
      const series_set_elt_t	left_series  = lhs.series_of(*l);
      const series_set_elt_t	right_series = rhs.series_of(*r);

      bool			prod_is_not_null = false;
      for_all_(support_t, supp, left_series.supp())
	{
	  const monoid_elt_t	 supp_elt (monoid_, *supp);
	  const semiring_elt_t l = left_series.get(supp_elt);
	  const semiring_elt_t r = right_series.get(supp_elt);
	  const semiring_elt_t p = l * r;
	  if (p != semiring_zero_)
	  {
	    prod_series.assoc(*supp, p.value());
	    prod_is_not_null = true;
	  }
	}
      return (prod_is_not_null);
    }

    // If set to true, <geometry> tags of the result automaton should be filled
    const bool	use_geometry_;

    // keep traces of new states created
    visited_t			visited_;
    // @c to_process_ stores all states of output that needs are not
    std::queue<pair_hstate_t>	to_process_;

    // frequently used objects in computation
    const series_set_t&	series_;
    const monoid_t&		monoid_;
    // This variable's type must not be set to a reference.
    const semiring_elt_t	semiring_zero_;
};

/*-----------.
| Wrappers.  |
`-----------*/

template<typename A, typename T, typename U>
Element<A, T>
infiltration (const Element<A, T>& lhs, const Element<A, U>& rhs,
	 std::map<typename T::hstate_t,
	 std::pair<typename T::hstate_t, typename U::hstate_t> >& m,
	 const bool use_geometry)
{
  Element<A, T> ret(rhs.structure());
  Infiltration<A, T, U> do_infiltration(ret.structure(), use_geometry);
  return do_infiltration (ret, lhs, rhs, m);
}

template<typename A, typename T, typename U>
Element<A, T>
infiltration (const Element<A, T>& lhs, const Element<A, U>& rhs,
	 const bool use_geometry)
{
  std::map<typename T::hstate_t,
    std::pair<typename T::hstate_t, typename U::hstate_t> > m;
  return infiltration (lhs, rhs, m, use_geometry);
}

} // End of namespace vcsn.

#endif // ! VCSN_ALGORITHMS_INFILTRATION_HXX
