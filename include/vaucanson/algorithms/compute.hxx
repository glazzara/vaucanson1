// compute.hxx
//
// $Id$
// VCSN_HEADER
#ifndef ALGORITHMS_COMPUTE_HXX
# define ALGORITHMS_COMPUTE_HXX

# include <algorithm>

# include <vaucanson/algorithms/compute.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/selectors.hh>

namespace vcsn {

  /*--------.
  | Compute |
  `--------*/
  // precondition : the automaton is realtime
  //
  //
  template <typename A, typename auto_t, 
	    typename serie_t, typename input_t>
  void 
  do_compute(const AutomataBase<A>& a_set,
	     const auto_t&	    a,
	     const input_t&	    word, 
	     serie_t&		    result)
  {
    std::vector<serie_t>		v1(a.states().size());
    std::vector<serie_t>		v2(a.states().size());
    std::list<hedge_t>			delta_ret;
    const typename serie_t::set_t	&serie_set = result.set();

    // FIXME: add an assert.
    
    /*-------------------.
    | Initialize the set |
    `-------------------*/
    std::fill(v1.begin(), v1.end(), 
	      serie_set.zero(SELECT(typename serie_t::value_t)));

    /*--------.
    | Initial |
    `--------*/
    for (typename auto_t::initial_iterator i = a.initial().begin();
	 i != a.initial().end();
	 ++i)
      v1[*i] = a.get_initial(*i);

    /*------------.
    | Computation |
    `------------*/
    for (typename input_t::const_iterator e = word.begin();
	 e != word.end();
	 ++e)
      {
	std::fill(v2.begin(), v2.end(), 
		  serie_set.zero(SELECT(typename serie_t::value_t)));
	for (unsigned i = 0; i < v1.size(); ++i)
	  if (v1[i] != serie_set.zero(SELECT(typename serie_t::value_t)))
	  {
	    // FIXME : use the other version of delta to be more efficient !
	    delta_ret.clear();
	    a.letter_deltac(delta_ret, i, *e, delta_kind::edges());
	    for (typename std::list<hedge_t>::const_iterator l = 
		   delta_ret.begin();
		 l != delta_ret.end();
		 ++l)
	      v2[a.aim_of(*l)] += v1[i] * a.label_of(*l) ;
	  }
	std::swap(v1, v2);
      }

    /*-----------------.
    | Final and Result |
    `-----------------*/
    for (unsigned i = 0; i < v1.size(); ++i)
      if (v1[i] != serie_set.zero(SELECT(typename serie_t::value_t)))
	result += v1[i] * a.get_final(i);    
  }

  /*--------.
  | Wrapper |
  `--------*/
  template<typename A, typename T, typename W>
  typename Element<A, T>::series_elt_t
  compute(const Element<A, T>& a, const W& word)
  {
    typename Element<A, T>::series_elt_t ret;

    do_compute(a.set(), a, word, ret);
    return ret;
  }

} // vcsn

#endif // ALGORITHMS_COMPUTE_HXX
