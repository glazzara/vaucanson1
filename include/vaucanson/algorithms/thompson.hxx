// thompson.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001,2002,2003 The Vaucanson Group.
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
#ifndef VCSN_ALGORITHMS_THOMPSON_HXX
# define VCSN_ALGORITHMS_THOMPSON_HXX

# include <set>
# include <vaucanson/algorithms/thompson.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/normalized.hh>
# include <vaucanson/algebra/concrete/series/rat/exp.hh>

namespace vcsn {

  /*----------------.
  | ThompsonVisitor |
  `----------------*/
  // FIXME : Non optimal version.
  //         There are too much construction of automaton.

  // FIXME : from now, it is only working over LetterAutomaton

  template <class Auto_, class Monoid_, class Semiring_>
  class ThompsonVisitor : 
    public rat::ConstNodeVisitor<Monoid_, Semiring_>
  {
  public :
    typedef Auto_						automaton_t;
    typedef typename automaton_t::set_t				automata_set_t;
    typedef typename automaton_t::series_t			series_t; 
    typedef typename automaton_t::series_elt_t			series_elt_t;
    typedef typename series_elt_t::weight_t			weight_t;
    typedef Monoid_						monoid_value_t;
    typedef Semiring_						weight_value_t;
    typedef rat::Node<monoid_value_t, weight_value_t>           node_t;

  public :

    ThompsonVisitor(const series_t& s) : series_(s)
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
    left_weight(const weight_value_t& w, const node_t* node) 
    {
      node->accept(*this);

      for (typename automaton_t::initial_iterator i = auto_->initial().begin();
	   i != auto_->initial().end();
	   ++i)
	auto_->set_initial(*i, weight_t(w) * auto_->get_initial(*i));
    }
    
    virtual void 
    right_weight(const weight_value_t& w, const node_t* node)
    {
      node->accept(*this);

      for (typename automaton_t::initial_iterator i = auto_->initial().begin();
	   i != auto_->initial().end();
	   ++i)
	auto_->set_initial(*i, auto_->get_initial(*i) * weight_t(w));
    }

    virtual void 
    constant(const monoid_value_t& m)
    {
      auto_ = new automaton_t(automata_set_t(series_));
      hstate_t new_i = auto_->add_state();
      hstate_t last = new_i;
      hstate_t new_f;
      for (typename monoid_value_t::const_iterator i = m.begin();
	   i != m.end(); ++i)
	{
	  new_f = auto_->add_state();
	  auto_->add_letter_edge(last, new_f, *i);
	  last = new_f;
	}
      auto_->set_initial(new_i);
      auto_->set_final(new_f);
    }

    virtual void 
    zero()
    {
      auto_ = new automaton_t(automata_set_t(series_));
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
    const series_t	&series_;
  };

  template <typename A, typename auto_t,
	    typename Letter, typename Weight>
  void
  do_thompson_of(const AutomataBase<A>&, 
	         auto_t& output, 
	         const rat::exp<Letter, Weight>& kexp)
  {
    ThompsonVisitor<auto_t, Letter, Weight> visitor(output.set().series());
   
    // FIXME : 
    // Static assert : Letter = monoid_elt_value_t, 
    //                 Weight = weight_value_t
    kexp.accept(visitor);
    output = visitor.get_auto();    
  }

  template<typename A,      typename T, 
	   typename Letter, typename Weight>
  void
  thompson_of(Element<A, T>& out, 
	      const rat::exp<Letter, Weight>& kexp)
  {
    do_thompson_of(out.set(), out, kexp);
  }

  template <class AutoType, class S, class T>
  Element<Automata<S>, AutoType>
  thompson_of(const Element<S, T>& exp)
  {
    Automata<S>				automata_set(exp.set());
    Element<Automata<S>, AutoType>	automata(automata_set);
    
    thompson_of(automata, exp.value());
    return automata;
  }
} // vcsn

#endif // VCSN_ALGORITHMS_THOMPSON_HXX
