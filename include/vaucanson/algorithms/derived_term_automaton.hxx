// derived_term_automaton.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2008, 2011 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_DERIVED_TERM_AUTOMATON_HXX
# define VCSN_ALGORITHMS_DERIVED_TERM_AUTOMATON_HXX

# include <vaucanson/algorithms/derived_term_automaton.hh>

# include <vaucanson/algorithms/internal/build_pattern.hh>
# include <vaucanson/algorithms/internal/partial_rat_exp.hh>
# include <vaucanson/algorithms/internal/partial_rat_exp_constant_term.hh>
# include <vaucanson/algorithms/internal/partial_rat_exp_derivation.hh>

# include <vaucanson/algorithms/krat_exp_realtime.hh>
# include <vaucanson/misc/usual_macros.hh>
# include <vaucanson/algorithms/initial_derivation.hh>

# ifdef DEBUG

namespace std
{
  template <typename T>
  std::ostream& operator << (std::ostream& o, const std::list<T>& l)
  {
    typename std::list<T>::const_iterator	i = l.begin();

    o << '{';
    if (i != l.end())
    {
      o << *i;
      for (i++; i != l.end(); ++i)
	o << ", " << *i;
    }
    return o << '}';
  }
}

#  define DERIVATES_TRACE_DEBUG(undef, e, l, s)		\
     if (!undef)					\
     {							\
       std::cerr << "Deriv "				\
		 << e					\
		 << " by "				\
		 << l					\
		 << " ="				\
		 << std::endl;				\
       std::cerr << s << std::endl;			\
       std::cerr << std::endl;				\
     }

# else

#  define DERIVATES_TRACE_DEBUG(undef, e, l, s)

# endif

namespace vcsn {

  using namespace algorithm_patterns;

  // In order to avoid re-calculation, the algorithm building
  // derivatives automaton is implemented in a incremental way
  template <typename T_auto, typename S, typename T>
  struct DerivativesAlgo : public IncAutomataConstructor <
    DerivativesAlgo<T_auto, S, T>,
    T_auto,
    PartialExp<S, T> >
  {
    typedef PartialExp<S, T>				exp_t;
    typedef std::list<exp_t>				exp_list_t;
    typedef typename exp_list_t::iterator		exp_list_iterator;
    AUTOMATON_TYPES(T_auto);
    AUTOMATON_FREEMONOID_TYPES(T_auto);

    // Contructor -> initialize mother class and undefined attributes,
    // which indicate if the resulting automaton is valid
    DerivativesAlgo(const series_set_t& series, const Element<S, T>& exp):
      IncAutomataConstructor<DerivativesAlgo, T_auto, PartialExp<S, T> >
	(series, prat_exp_convert(exp)),
      undefined(false)
    {}

    // List Contructor -> initialize mother class and undefined attributes,
    // which indicate if the resulting automaton is valid.
    // This is used for the broken_derived_term_automaton algorithm.
    DerivativesAlgo(const series_set_t& series,
		    const std::list<Element<S, T> >& listexp):
      IncAutomataConstructor<DerivativesAlgo, T_auto, PartialExp<S, T> >
	(series, prat_exp_convert(listexp)),
       undefined(false)
     {}

    // Function applied on each state
    void on_state(const PartialExp<S, T>& e)
    {
      alphabet_t alpha = this->get()->series().monoid().alphabet();

      // Test the constant term of current expression
      // If it is not zero, it is a final state
      std::pair<semiring_elt_t, bool>	c_term = constant_term(e);
      if (!c_term.second)
	undefined = true;
      if (c_term.first !=
	  e.exp_structure().semiring().zero(SELECT(semiring_elt_value_t)))
	this->set_final(series_set_elt_t (e.exp_structure(), c_term.first));

      // Create links between current state and states corresponding to
      // partial derivatives of current expression
      for (alphabet_iterator a = alpha.begin(); a != alpha.end(); ++a)
      {
	std::pair<std::list<PartialExp<S, T> >, bool>
	  s = prat_exp_derivate(e, *a);
	if (!s.second)
	  undefined = true;
	DERIVATES_TRACE_DEBUG(undefined, e, *a, s.first);
	for (exp_list_iterator i = s.first.begin(); i != s.first.end(); ++i)
	{
	  PartialExp<S, T> p_exp = *i;
	  series_set_elt_t s_elt (e.exp_structure(),
			      monoid_elt_t(e.exp_structure().monoid(), *a));
	  s_elt = p_exp.begin().semiring_elt() * s_elt;
	  p_exp.begin().semiring_elt() =
	    e.exp_structure().semiring().identity(SELECT(semiring_elt_value_t));
	  this->link_to(p_exp, s_elt);
	}
      }
    }

    bool undefined;
  };

  template<typename T_auto, typename S, typename T>
  T_auto*
  do_derived_term_automaton(const T_auto& out,
			   const Element<S, T>& kexp)
  {
    Element<S, T>			exp = realtime(kexp);
    DerivativesAlgo<T_auto, S, T>	derivatives_algo(out.series(), exp);
    derivatives_algo.run();
    if (derivatives_algo.undefined)
    {
      delete derivatives_algo.get();
      return NULL;
    }
    else
      return derivatives_algo.get();
  }

  template<typename A, typename T, typename Exp>
  void
  derived_term_automaton(Element<A, T>& out, const Exp& kexp)
  {
    BENCH_TASK_SCOPED("derived_term_automaton");
    Element<A, T>* res = do_derived_term_automaton(out, kexp);
    if (res)
      out = *res;
  }

  template<typename A, typename T, typename Exp>
  Element<A, T>
  derived_term_automaton(const Exp& kexp)
  {
    A			a_structure(kexp.structure());
    Element<A, T>	out (a_structure);
    derived_term_automaton (out, kexp);
    return out;
  }

  // broken_derived_term_automaton implementation
  template<typename T_auto, typename S, typename T>
  T_auto*
  do_broken_derived_term_automaton(const T_auto& out,
			   const Element<S, T>& kexp)
  {
    Element<S, T>			exp = realtime(kexp);
    KRatExpInitialDerivation< S, T, algebra::DispatchFunction<T> >
      matcher(exp);
    std::list< Element<S, T> > listexp = matcher.match(exp.value());
    DerivativesAlgo<T_auto, S, T> derivatives_algo(out.series(),
						   listexp);
    derivatives_algo.run();
    if (derivatives_algo.undefined)
    {
      delete derivatives_algo.get();
      return NULL;
    }
    else
      return derivatives_algo.get();
  }

  template<typename A, typename T, typename Exp>
  void
  broken_derived_term_automaton(Element<A, T>& out, const Exp& kexp)
  {
    Element<A, T>*	result = do_broken_derived_term_automaton(out, kexp);
    if (result != NULL)
      out = *result;
  }

  template<typename A, typename T, typename Exp>
  Element<A, T>
  broken_derived_term_automaton(const Exp& kexp)
  {
    A			a_structure(kexp.structure());
    Element<A, T>	out (a_structure);
    Element<A, T>*	result = do_broken_derived_term_automaton(out, kexp);
    if (result != NULL)
      out = *result;
    return out;
  }



} // vcsn

#endif // ! VCSN_ALGORITHMS_DERIVED_TERM_AUTOMATON_HXX
