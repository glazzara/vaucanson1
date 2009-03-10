// thompson.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_THOMPSON_HXX
# define VCSN_ALGORITHMS_THOMPSON_HXX

# include <utility>

# include <vaucanson/algorithms/thompson.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {

  /*----------------.
  | ThompsonVisitor |
  `----------------*/
  // FIXME : from now, it is only working over LetterAutomaton

  template <class Auto_, class Monoid_, class Semiring_>
  class ThompsonVisitor :
      public rat::ConstNodeVisitor<Monoid_, Semiring_>
  {
    public :
      typedef Auto_					automaton_t;
      typedef typename automaton_t::hstate_t		hstate_t;
      typedef typename automaton_t::set_t		automata_set_t;
      typedef typename automaton_t::series_set_t	series_set_t;
      typedef typename automaton_t::series_set_elt_t	series_set_elt_t;
      typedef typename series_set_elt_t::semiring_elt_t	semiring_elt_t;
      typedef Monoid_					monoid_elt_value_t;
      typedef Semiring_					semiring_elt_value_t;
      typedef rat::Node<monoid_elt_value_t, semiring_elt_value_t> node_t;

    public :

      ThompsonVisitor(automaton_t &a)
        : auto_ (a)
      {}

      virtual
      ~ThompsonVisitor()
      {}

      virtual void
      product(const node_t* lhs, const node_t* rhs)
      {
        // Visit left tree
	lhs->accept(*this);
        // Store results
        std::pair<hstate_t, hstate_t>     left_ini_fin = ini_fin_;
        // Visit right tree
	rhs->accept(*this);
        // Create spontaneous link between
        // final of left automaton and initial of right automaton.
	auto_.add_spontaneous(left_ini_fin.second, ini_fin_.first);

        // Save new initial state.
        ini_fin_.first = left_ini_fin.first;
      }

      virtual void
      sum(const node_t* lhs, const node_t* rhs)
      {
	lhs->accept(*this);

        std::pair<hstate_t, hstate_t>     left_ini_fin = ini_fin_;
        hstate_t new_i = auto_.add_state();
        hstate_t new_f = auto_.add_state();

        auto_.add_spontaneous(new_i, left_ini_fin.first);
        auto_.add_spontaneous(left_ini_fin.second, new_f);

	rhs->accept(*this);

        auto_.add_spontaneous(new_i, ini_fin_.first);
        auto_.add_spontaneous(ini_fin_.second, new_f);

        ini_fin_.first = new_i;
        ini_fin_.second = new_f;
      }

      virtual void
      star(const node_t* node)
      {
	node->accept(*this);
	auto_.add_spontaneous(ini_fin_.second, ini_fin_.first);

        hstate_t new_i = auto_.add_state();
        hstate_t new_f = auto_.add_state();

        auto_.add_spontaneous(new_i, new_f);
        auto_.add_spontaneous(new_i, ini_fin_.first);
        auto_.add_spontaneous(ini_fin_.second, new_f);

        ini_fin_.first = new_i;
        ini_fin_.second = new_f;
      }

      virtual void
      left_weight(const semiring_elt_value_t& w, const node_t* node)
      {
	node->accept(*this);

	hstate_t new_i = auto_.add_state();
	hstate_t new_f = auto_.add_state();

        series_set_elt_t t = auto_.series().zero_;
        t.assoc(auto_.series().monoid().identity(SELECT(monoid_elt_value_t)), w);
        auto_.add_series_transition(new_i, ini_fin_.first, t);

        auto_.add_spontaneous(ini_fin_.second, new_f);

        ini_fin_.first = new_i;
	ini_fin_.second = new_f;
      }

      virtual void
      right_weight(const semiring_elt_value_t& w, const node_t* node)
      {
	node->accept(*this);

	hstate_t new_i = auto_.add_state();
	hstate_t new_f = auto_.add_state();

        auto_.add_spontaneous(new_i, ini_fin_.first);

        series_set_elt_t t = auto_.series().zero_;
        t.assoc(auto_.series().monoid().identity(SELECT(monoid_elt_value_t)), w);
        auto_.add_series_transition(ini_fin_.second, new_f, t);

        ini_fin_.first = new_i;
	ini_fin_.second = new_f;
      }

      virtual void
      constant(const monoid_elt_value_t& m)
      {
	ini_fin_.first = auto_.add_state();
	hstate_t link_state;

        typename monoid_elt_value_t::const_iterator i = m.begin();

        ini_fin_.second = auto_.add_state();
        auto_.add_letter_transition(ini_fin_.first, ini_fin_.second, *i);
        ++i;

	while (i != m.end())
	{
          link_state = auto_.add_state();
          auto_.add_spontaneous(ini_fin_.second, link_state);
	  ini_fin_.second = auto_.add_state();
	  auto_.add_letter_transition(link_state, ini_fin_.second, *i);
          ++i;
	}
      }

      virtual void
      zero()
      {
        ini_fin_.first = auto_.add_state();
	ini_fin_.second = auto_.add_state();
      }

      virtual void
      one()
      {
	ini_fin_.first = auto_.add_state();
	ini_fin_.second = auto_.add_state();
	auto_.add_spontaneous(ini_fin_.first, ini_fin_.second);
      }

      const automaton_t		&get_auto() const
      {
        auto_.clear_initial();
        auto_.clear_final();
        auto_.set_initial(ini_fin_.first);
        auto_.set_final(ini_fin_.second);
	return auto_;
      }

      // finalize is used to only set initial and final states of auto_
      // only once (to spare the multiple set and unset required elsewise).
      void
      finalize() const
      {
        auto_.set_initial(ini_fin_.first);
        auto_.set_final(ini_fin_.second);
      }

    private :
      automaton_t                       &auto_;
      std::pair<hstate_t, hstate_t>     ini_fin_;
  };

  template <typename A, typename auto_t,
	    typename Letter, typename Weight>
  void
  do_thompson_of(const AutomataBase<A>&,
		 auto_t& output,
		 const rat::exp<Letter, Weight>& kexp)
  {
    // You should provide an empty automaton as output.
    ThompsonVisitor<auto_t, Letter, Weight> visitor(output);
    // FIXME :
    // Static assert : Letter = monoid_elt_value_t,
    //		       Weight = semiring_elt_value_t
    kexp.accept(visitor);
    visitor.finalize();
  }

  template<typename A,	    typename T,
	   typename Letter, typename Weight>
  void
  thompson_of(Element<A, T>& out,
	      const rat::exp<Letter, Weight>& kexp)
  {
    do_thompson_of(out.structure(), out, kexp);
  }

  template <typename AutoType, typename S, typename K, typename T>
  Element<Automata<S, K>, AutoType>
  thompson_of(const Element<S, T>& exp)
  {
    Automata<S, K>			automata_set(exp.structure());
    Element<Automata<S, K>, AutoType>	automata(automata_set);

    thompson_of(automata, exp.value());
    return automata;
  }
} // vcsn

#endif // ! VCSN_ALGORITHMS_THOMPSON_HXX
