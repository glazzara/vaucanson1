// derivates_automaton.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2003 Sakarovitch, Lombardy, Poss, Rey and Regis-Gianas.
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

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

#ifndef VCSN_ALGORITHMS_DERIVATES_AUTOMATON_HXX
# define VCSN_ALGORITHMS_DERIVATES_AUTOMATON_HXX

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/standard.hh>
# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/krat_exp_partial_derivation.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/algorithms/algo_helper.hh>
# include <vaucanson/algebra/concrete/series/krat_coefficient.hh>

namespace vcsn {

  using namespace algorithm_patterns;
  
  // In order to avoid re-calculation, the algorithm building
  // derivates automaton is implemented in a incremental way
  template <typename T_auto, typename Exp>
  struct DerivatesAlgo : public IncAutomataConstructor <
    DerivatesAlgo<T_auto, Exp>,
    T_auto,
    Exp >  
  {
    typedef typename std::set<Exp>::iterator	set_iterator;
    AUTOMATON_TYPES(T_auto);
    
    // Contructor -> initialize mother class and undefined attribute,
    // which indicate if the resulting automaton is valide
    DerivatesAlgo(const series_t& series, const Exp& exp):
      IncAutomataConstructor<DerivatesAlgo, T_auto, Exp>(series, exp),
      undefined(false)
    {}

    // Function applied on each state
    void on_state(const Exp& e)
    {
      AUTOMATON_TYPES(T_auto);
      
      alphabet_t alpha = get()->series().monoid().alphabet();

      // Test the constant term of current expression
      // If it is not zero, it is a final state
      std::pair<weight_t, bool>	c_term = constant_term(e);
      if (!c_term.second)
	undefined = true;
      if (c_term.first != e.set().weights().zero(SELECT(weight_value_t)))
	set_final(c_term.first);

      // Create links between current state and states corresponding to
      // partial derivates of current expression
      for (alphabet_iterator a = alpha.begin(); a != alpha.end(); ++a)
      {
	std::pair<std::set<Exp>, bool>	s = partial_derivate(e, *a);
	if (!s.second)
	  undefined = true;
	for (set_iterator i = s.first.begin(); i != s.first.end(); ++i)
	{
	  std::pair<weight_t, Exp> coef = coefficient(*i);
	  series_elt_t s_elt;
	  s_elt.value_set(monoid_elt_t(*a), coef.first);
	  link_to(coef.second, s_elt);
	}
      }
    }

    bool undefined;
  };

  template<typename T_auto, typename Exp>
  T_auto*	do_derivates_automaton(const T_auto& out, const Exp &kexp)
  {
    DerivatesAlgo<T_auto, Exp> derivates_algo(out.series(), kexp);
    derivates_algo.run();
    if (derivates_algo.undefined)
    {
      free(derivates_algo.get());
      return NULL;
    }
    else
      return derivates_algo.get();
  }

  // The function called by <<user>>
  template<typename A, typename T, typename Exp>
  void	derivates_automaton(Element<A, T>& out, const Exp& kexp)
  {
    Element<A, T>*	result = do_derivates_automaton(out, kexp);
    if (result != NULL)
      out = *result;
  }

} // vcsn

#endif // VCSN_ALGORITHMS_DERIVATES_AUTOMATON_HXX
