// brzozowski.hxx: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHMS_BRZOZOWSKI_HXX
# define VCSN_ALGORITHMS_BRZOZOWSKI_HXX

# include <vaucanson/algorithms/brzozowski.hh>

# include <vaucanson/algorithms/internal/build_pattern.hh>
# include <vaucanson/automata/concept/automata_base.hh>

# include <vaucanson/algorithms/krat_exp_constant_term.hh>
# include <vaucanson/algorithms/krat_exp_derivation.hh>
# include <vaucanson/algorithms/aci_canonical.hh>
# include <vaucanson/tools/usual_macros.hh>

namespace vcsn {

  using namespace algorithm_patterns;

  /**
   * This is the class that really computes Brzozowski.
   *
   * This class should be used  only in brzozowski() and should not be
   * instantiated from elsewhere.
   *
   * This   class   defines  the   methods   which   are  missing   to
   * IncAutomataConstructor  to   incrementally  build  an  automaton,
   * i.e. the function which must be applied on each state.
   *
   * @see brzozowski()
   */
  template <typename T_auto, typename Exp>
  struct BrzozowskiAlgo : public IncAutomataConstructor <
    BrzozowskiAlgo<T_auto, Exp>,
    T_auto,
    Exp >
  {
    AUTOMATON_TYPES(T_auto);

    BrzozowskiAlgo(const series_t& series, const Exp& exp):
      IncAutomataConstructor<BrzozowskiAlgo, T_auto, Exp>(series, exp)
    {}

    /// @bug FIXME: Optimize!
    void on_state(const Exp& e)
    {
      alphabet_t alpha = get()->series().monoid().alphabet();
      if (constant_term(e).first
	  != e.structure().semiring().zero(SELECT(semiring_elt_value_t)))
	set_final();
      for (alphabet_iterator i = alpha.begin(); i != alpha.end(); ++i)
	link_to(canonical(derivate(e, *i).first), *i);
    }
  };

  template<typename T_auto, typename Exp>
  T_auto*
  do_brzozowski(const T_auto& out, const Exp &kexp)
  {
    BrzozowskiAlgo<T_auto, Exp> brzozowski_algo(out.series(), canonical(kexp));
    brzozowski_algo.run();
    return brzozowski_algo.get();
  }

  template<typename A, typename T, typename Exp>
  void
  brzozowski(Element<A, T>& out, const Exp& kexp)
  {
    out = *do_brzozowski(out, kexp);
  }

} // vcsn

#endif // VCSN_ALGORITHMS_BRZOZOWSKI_HXX
