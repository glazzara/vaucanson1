// derivatives_automaton.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003, 2004 The Vaucanson Group.
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
// The Vaucanson Group consists of the following contributors:
//    * Jacques Sakarovitch <sakarovitch@enst.fr>
//    * Sylvain Lombardy <lombardy@liafa.jussieu.fr>
//    * Thomas Claveirole <thomas.claveirole@lrde.epita.fr>
//    * Loic Fosse <loic.fosse@lrde.epita.fr>
//    * Thanh-Hoc Nguyen <nguyen@enst.fr>
//    * Raphael Poss <raphael.poss@lrde.epita.fr>
//    * Yann Regis-Gianas <yann.regis-gianas@lrde.epita.fr>
//    * Maxime Rey <maxime.rey@lrde.epita.fr>
//    * Sarah O'Connor <sarah.o-connor@lrde.epita.fr>
//    * Louis-Noel Pouchet <louis-noel.pouchet@lrde.epita.fr>
//
#ifndef VCSN_ALGORITHMS_DERIVATIVES_AUTOMATON_HXX
# define VCSN_ALGORITHMS_DERIVATIVES_AUTOMATON_HXX

# include <vaucanson/algorithms/derivatives_automaton.hh>

# include <vaucanson/algorithms/internal/build_pattern.hh>
# include <vaucanson/algorithms/internal/partial_rat_exp.hh>
# include <vaucanson/algorithms/internal/partial_rat_exp_constant_term.hh>
# include <vaucanson/algorithms/internal/partial_rat_exp_derivation.hh>

# include <vaucanson/algorithms/krat_exp_realtime.hh>
# include <vaucanson/tools/usual_macros.hh>

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
       std::cout << "Deriv "				\
	         << e					\
		 << " by "				\
		 << l					\
		 << " ="				\
		 << std::endl;				\
       std::cout << s << std::endl;			\
       std::cout << std::endl;				\
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

    // Contructor -> initialize mother class and undefined attribute,
    // which indicate if the resulting automaton is valide
    DerivativesAlgo(const series_set_t& series, const Element<S, T>& exp):
      IncAutomataConstructor<DerivativesAlgo, T_auto, PartialExp<S, T> >
        (series, prat_exp_convert(exp)),
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
	set_final(series_set_elt_t (e.exp_structure(), c_term.first));

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
	  link_to(p_exp, s_elt);
	}
      }
    }

    bool undefined;
  };

  template<typename T_auto, typename S, typename T>
  T_auto*
  do_derivatives_automaton(const T_auto& out,
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
  derivatives_automaton(Element<A, T>& out, const Exp& kexp)
  {
    Element<A, T>*	result = do_derivatives_automaton(out, kexp);
    if (result != NULL)
      out = *result;
  }

  template<typename A, typename T, typename Exp>
  Element<A, T>
  derivatives_automaton(const Exp& kexp)
  {
    A			a_structure(kexp.structure());
    Element<A, T>	out (a_structure);
    Element<A, T>*	result = do_derivatives_automaton(out, kexp);
    if (result != NULL)
      out = *result;
    return out;
  }

} // vcsn

#endif // ! VCSN_ALGORITHMS_DERIVATIVES_AUTOMATON_HXX
