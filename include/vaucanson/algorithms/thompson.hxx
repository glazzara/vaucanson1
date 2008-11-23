// thompson.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008 The Vaucanson Group.
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

# include <vaucanson/algorithms/thompson.hh>

# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/normalized.hh>
# include <vaucanson/misc/usual_macros.hh>

namespace vcsn {

  /*----------------.
  | ThompsonVisitor |
  `----------------*/
  // FIXME : Non optimal version.
  //	     There are too much construction of automaton.

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

      ThompsonVisitor(const series_set_t& s) : series_(s)
      {}

      virtual
      ~ThompsonVisitor()
      {}

      virtual void
      product(const node_t* lhs, const node_t* rhs)
      {
	automaton_t	*tmp_;
	rhs->accept(*this);
	tmp_ = auto_;
	lhs->accept(*this);
	concatenate_of_normalized_here(*auto_, *tmp_);
	delete(tmp_);
      }

      virtual void
      sum(const node_t* lhs, const node_t* rhs)
      {
	automaton_t	*tmp_;
	lhs->accept(*this);
	tmp_ = auto_;
	rhs->accept(*this);
	union_of_normalized_here(*auto_, *tmp_);
      }

      virtual void
      star(const node_t* node)
      {
	node->accept(*this);
	star_of_normalized_here(*auto_);
      }

      virtual void
      left_weight(const semiring_elt_value_t& w, const node_t* node)
      {
	node->accept(*this);

	AUTOMATON_TYPES(automaton_t);

	hstate_t new_i = auto_->add_state();
	hstate_t new_f = auto_->add_state();

	for_all_const_initial_states(i, *auto_)
	{
	  series_set_elt_t t = auto_->series().zero_;
	  t.assoc(auto_->series().monoid().identity(SELECT(monoid_elt_value_t)), w);
	  auto_->add_series_transition(new_i, *i, t);
	}
	for_all_const_final_states(f, *auto_)
	  auto_->add_spontaneous(*f, new_f);

	auto_->clear_initial();
	auto_->clear_final();

	auto_->set_initial(new_i);
	auto_->set_final(new_f);
      }

      virtual void
      right_weight(const semiring_elt_value_t& w, const node_t* node)
      {
	node->accept(*this);

	AUTOMATON_TYPES(automaton_t);

	hstate_t new_i = auto_->add_state();
	hstate_t new_f = auto_->add_state();

	for_all_const_initial_states(i, *auto_)
	  auto_->add_spontaneous(new_i, *i);
	for_all_const_final_states(f, *auto_)
	{
	  series_set_elt_t t = auto_->series().zero_;
	  t.assoc(auto_->series().monoid().identity(SELECT(monoid_elt_value_t)), w);
	  auto_->add_series_transition(*f, new_f, t);
	}

	auto_->clear_initial();
	auto_->clear_final();

	auto_->set_initial(new_i);
	auto_->set_final(new_f);
      }

      virtual void
      constant(const monoid_elt_value_t& m)
      {
	auto_ = new automaton_t(automata_set_t(series_));
	hstate_t new_i = auto_->add_state();
	hstate_t last = new_i;
	hstate_t new_f;
	for (typename monoid_elt_value_t::const_iterator i = m.begin();
	     i != m.end(); ++i)
	{
	  new_f = auto_->add_state();
	  auto_->add_letter_transition(last, new_f, *i);
	  last = new_f;
	}
	auto_->set_initial(new_i);
	auto_->set_final(new_f);
      }

      virtual void
      zero()
      {
	auto_ = new automaton_t(automata_set_t(series_));
	auto_->set_initial(auto_->add_state());
	auto_->set_final(auto_->add_state());
      }

      virtual void
      one()
      {
	auto_ = new automaton_t(automata_set_t(series_));
	hstate_t new_i = auto_->add_state();
	hstate_t new_f = auto_->add_state();
	auto_->set_initial(new_i);
	auto_->set_final(new_f);
	auto_->add_spontaneous(new_i, new_f);
      }

      const automaton_t		&get_auto() const
      {
	return *auto_;
      }

    private :
      automaton_t		*auto_;
      const series_set_t	&series_;
  };

  template <typename A, typename auto_t,
	    typename Letter, typename Weight>
  void
  do_thompson_of(const AutomataBase<A>&,
		 auto_t& output,
		 const rat::exp<Letter, Weight>& kexp)
  {
    ThompsonVisitor<auto_t, Letter, Weight> visitor(output.structure().series());

    // FIXME :
    // Static assert : Letter = monoid_elt_value_t,
    //		       Weight = semiring_elt_value_t
    kexp.accept(visitor);
    output = visitor.get_auto();
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
