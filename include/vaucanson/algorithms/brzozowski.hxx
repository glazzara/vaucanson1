// brzozowski.hxx
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


#ifndef VCSN_ALGORITHMS_BRZOZOWSKI_HXX
# define VCSN_ALGORITHMS_BRZOZOWSKI_HXX

# include <vaucanson/algorithms/brzozowski.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/standard.hh>
# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>
# include <vaucanson/algorithms/krat_exp_derivation.hh>
# include <vaucanson/algorithms/krat_exp_constant_term.hh>
# include <vaucanson/tools/usual_macros.hh>
# include <vaucanson/algorithms/algo_helper.hh>
# include <vaucanson/algorithms/aci_canonical.hh>

namespace vcsn {

  using namespace algorithm_patterns;
  
  // The brzozowski algorithm : it is derivated from IncAutomataConstructor
  // because it's an incremental algorithm.
  // It gives the function which must be applied on each state,
  // and may give the ordered function
  template <typename T_auto, typename Exp>
  struct BrzozowskiAlgo : public IncAutomataConstructor <
    BrzozowskiAlgo<T_auto, Exp>,
    T_auto,
    Exp >  
  {
    // Types used for the constructor
    AUTOMATON_TYPES(T_auto);
    // The constructor : only call the constructor of the base class
    BrzozowskiAlgo(const series_t& series, const Exp& exp):
      IncAutomataConstructor<BrzozowskiAlgo, T_auto, Exp>(series, exp)
    {}

    // The function applied on each state
    // FIXME : optimize it !
    void on_state(const Exp& e)
    {
      AUTOMATON_TYPES(T_auto);
      
      alphabet_t alpha = get()->series().monoid().alphabet();
      if (constant_term(e).first)
	set_final();
      for (alphabet_iterator i = alpha.begin(); i != alpha.end(); ++i)
	link_to(canonical(derivate(e, *i).first), *i);
    }

    // We take the default ordered function,
    // so we do not redefine it.

  };

  template<typename T_auto, typename Exp>
  T_auto*	do_brzozowski(const T_auto& out, const Exp &kexp)
  {
    BrzozowskiAlgo<T_auto, Exp> brzozowski_algo(out.series(), canonical(kexp));
    brzozowski_algo.run();
    return brzozowski_algo.get();
  }

  // The function called by <<user>>
  template<typename A, typename T, typename Exp>
  void	brzozowski(Element<A, T>& out, const Exp& kexp)
  {
    out = *do_brzozowski(out, kexp);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_BRZOZOWSKI_HXX
