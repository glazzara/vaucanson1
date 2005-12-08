// brzozowski.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005 The Vaucanson Group.
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
    AUTOMATON_FREEMONOID_TYPES(T_auto);

    BrzozowskiAlgo(const series_set_t& series, const Exp& exp):
      IncAutomataConstructor<BrzozowskiAlgo, T_auto, Exp>(series, exp)
    {}

    /// @bug FIXME: Optimize!
    void on_state(const Exp& e)
    {
      alphabet_t alpha = this->get()->series().monoid().alphabet();
      if (constant_term(e).first
	  != e.structure().semiring().zero(SELECT(semiring_elt_value_t)))
	this->set_final();
      for (alphabet_iterator i = alpha.begin(); i != alpha.end(); ++i)
	this->link_to(canonical(derivate(e, *i).first), *i);
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

#endif // ! VCSN_ALGORITHMS_BRZOZOWSKI_HXX
