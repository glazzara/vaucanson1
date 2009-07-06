// berry_sethi.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_BERRY_SETHI_HXX
# define VCSN_ALGORITHMS_BERRY_SETHI_HXX

# include <list>

# include <vaucanson/algorithms/berry_sethi.hh>

# include <vaucanson/algorithms/internal/build_pattern.hh>
# include <vaucanson/automata/concept/automata_base.hh>

# include <vaucanson/algorithms/krat_exp_constant_term.hh>
# include <vaucanson/algorithms/krat_exp_derivation.hh>
# include <vaucanson/algorithms/krat_exp_linearize.hh>
# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {

  using namespace algorithm_patterns;

  /**
   * Computes a linearized alphabet from a rational expression.
   *
   * This function  returns a  linearized alphabet corresponding  to a
   * rational expression, with an extra zero-letter in it.
   *
   * @param exp The expression to work on.
   *
   * @author Loic Fosse <loic@lrde.epita.fr>
   * @see linearize()
   */
  template <typename S, typename T>
  typename linearize_element<S, T>::alphabet_t
  linearized_alphabet(const Element<S, T>& exp)
  {
    typedef typename linearize_element<S, T>::alphabet_t	alphabet_t;
    typedef typename linearize_element<S, T>::letter_t		letter_t;

    alphabet_t result = linearize(exp).structure().monoid().alphabet();
    result.insert(letter_t(0, 0));
    return result;
  }

  /**
   * This function computes a continuation on linearized expressions.
   *
   * This include the case when letter is zero.
   *
   * @param exp The expression to work on.
   * @param l The letter used to compute the derivation.
   *
   * @author Loic Fosse <loic@lrde.epita.fr>
   */
  template <typename Exp, typename Letter>
  Exp
  linear_exp_continuation(const Exp& exp, const Letter& l)
  {
    typedef typename Exp::set_t::monoid_t::alphabet_t	alphabet_t;
    typedef typename alphabet_t::iterator		iterator;
    typedef typename Exp::value_t			value_t;

    if (l == Letter(0,0))
      return exp;

    alphabet_t		alpha = exp.structure().monoid().alphabet();
    Exp			zero = exp.structure().zero(SELECT(value_t));
    std::list<Exp>	exp_list;

    exp_list.push_back(exp);

    while (!exp_list.empty())
    {
      Exp	exp = exp_list.front();
      exp_list.pop_front();
      Exp	deriv = derivate(exp, l).first;

      if (deriv != zero)
	return deriv;
      else
	for (iterator i = alpha.begin(); i != alpha.end(); ++i)
	  if (*i != l)
	  {
	    deriv = derivate(exp, *i).first;
	    if (deriv != zero && deriv != exp)
	      exp_list.push_back(deriv);
	  }
    }
    return zero;
  }

  /**
   * This is the visitor that really computes Berry-Sethi.
   *
   * This class should be used  only in berry_sethi() and should not
   * be instanciated from elsewhere.
   *
   * It is derived from MathAutomataConstructor because we want to use
   * the mathematical definition of the Berry-Sethi automaton.
   *
   * It   defines  the   constructor  to   give  a   correct   set  to
   * MathAutomataConstructor constructor.   It also defines is_initial
   * and is_final for a labeled state, and delta function.
   *
   * @bug FIXME: Change the zero-letter.
   * @bug FIXME: Check efficiency.
   * @bug FIXME: Check results of derivation.
   *
   * @see berry_sethi()
   */
  template <typename T_auto, typename S, typename T>
  struct BerrySethiAlgo : public MathAutomataConstructor <
    BerrySethiAlgo<T_auto, S, T>,
    T_auto,
    typename linearize_element<S, T>::letter_t >
  {
  public:
    /// Type of the argument to provide to the constructor.
    typedef
    Element<S, T>					exp_t;
    /// Types from linearize_element.
    /** @{ */
    typedef typename linearize_element<S, T>::element_t	  linear_exp_t;
    typedef typename linearize_element<S, T>::alphabet_t  linear_alphabet_t;
    typedef typename linearize_element<S, T>::letter_t	  etiq_t;
    /** @} */
    // Common types.
    AUTOMATON_TYPES(T_auto);
    AUTOMATON_FREEMONOID_TYPES(T_auto);

    /**
     * @brief Default constructor.
     *
     * This is  the default  constructor for BerrySethiAlgo,  it calls
     * the  MathAutomataConstructor  constructor  with the  linearized
     * alphabet enriched with an extra letter as the set of states for
     * the resulting automaton.
     *
     * @see MathAutomataConstructor
     *
     * @bug FIXME: Is it necessary to give the series as a separate argument?
     */
    BerrySethiAlgo(const series_set_t& series, const exp_t& exp):
      MathAutomataConstructor <BerrySethiAlgo, T_auto, etiq_t>
	(series, linearized_alphabet(exp)),
      linear_exp(linearize(exp)),
      linear_alpha(linear_exp.structure().monoid().alphabet())
    {
      linear_alpha.insert(etiq_t(0, 0));
    }

    /// Whether a state is final or initial.
    /** @{ */
    bool is_initial(const etiq_t& e) const
    {
      return (e == etiq_t(0, 0));
    }

    bool is_final(const etiq_t& e) const
    {
      return constant_term(linear_exp_continuation(linear_exp, e)).first
	!= linear_exp.structure().semiring().zero(SELECT(semiring_elt_value_t));
    }
    /** @} */

    /// This is the delta function for the constructed automaton.
    std::set<etiq_t> delta(const etiq_t& e, const letter_t& l)
    {
      typedef typename linear_alphabet_t::iterator	iterator;
      std::set<etiq_t>	result;
      linear_exp_t	continuation_e = linear_exp_continuation(linear_exp, e);

      for (iterator i = linear_alpha.begin(); i != linear_alpha.end(); ++i)
	if (i->first == l 
	    && (derivation(continuation_e, *i)
		== linear_exp_continuation(linear_exp, *i)))
	  result.insert(*i);
      return result;
    }

  private:
    /// This is the derivation function, including zero.
    linear_exp_t	derivation(const linear_exp_t& exp, const etiq_t& e)
    {
      if (e == etiq_t(0, 0))
	return exp;
      else
	return derivate(exp, e).first;
    }

    /// A linearized version of the initial expression.
    linear_exp_t	linear_exp;
    /// A linearized alphabet of the initial expression.
    linear_alphabet_t	linear_alpha;
  };

  template<typename T_auto, typename S, typename T>
  T_auto*
  do_berry_sethi(const T_auto& out, const Element<S, T>& kexp)
  {
    BerrySethiAlgo<T_auto, S, T> berrysethi_algo(out.series(), kexp);
    berrysethi_algo.run();
    return berrysethi_algo.get();
  }

  template<typename A, typename T, typename Exp>
  void
  berry_sethi(Element<A, T>& out, const Exp& kexp)
  {
    BENCH_TASK_SCOPED("berry_sethi");
    Element<A, T>* tmp = do_berry_sethi(out, kexp);
    out = *tmp;
    delete tmp;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_BERRY_SETHI_HXX
