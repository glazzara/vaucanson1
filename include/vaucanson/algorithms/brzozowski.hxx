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
  
  // The functions which is needed by the algorithm constructor
  struct BrzozowskiFuns
  {
    // FIXME : optimize the on_state function
    
    // The function applied on each state
    template <typename T_auto, typename Exp, typename T>
    void on_state(IncAutomataConstructor<T_auto, Exp, T>& a, const Exp& e)
    {
      AUTOMATON_TYPES(T_auto);
      
      alphabet_t alpha = a.get()->series().monoid().alphabet();
      if (constant_term(e).first)
	a.set_final();
      for (alphabet_iterator i = alpha.begin(); i != alpha.end(); ++i)
	a.link_to(canonical(derivate(e, *i).first), *i);
    }

    // The ordered relation which is used by the map.
    template <typename Exp>
    bool operator()(const Exp& e1, const Exp& e2) const
    {
      return e1 < e2;
    }
  };

  template<typename T_auto, typename Exp>
  T_auto*	do_brzozowski(const T_auto& out, const Exp &kexp)
  {
    IncAutomataConstructor<T_auto, Exp, BrzozowskiFuns>
      BrzozowskiAlgo(out.series(), canonical(kexp));
    BrzozowskiAlgo.run();
    return BrzozowskiAlgo.get();
  }

  // The function called by <<user>>
  template<typename A, typename T, typename Exp>
  void	brzozowski(Element<A, T>& out, const Exp& kexp)
  {
    out = *do_brzozowski(out, kexp);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_BRZOZOWSKI_HXX
