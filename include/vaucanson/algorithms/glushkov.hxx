// glushkov.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001, 2002, 2003 Sakarovitch, Lombardy, Poss, Rey and
// Regis-Gianas.
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

#ifndef VCSN_ALGORITHMS_GLUSHKOV_HXX
# define VCSN_ALGORITHMS_GLUSHKOV_HXX

# include <set>
# include <vaucanson/algorithms/glushkov.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/standard.hh>
# include <vaucanson/algebra/concrete/series/krat_exp_pattern.hh>

namespace vcsn {

  /*----------------.
  | GlushkovVisitor |
  `----------------*/
  template <class Exp_, 
	    class Auto_,
	    class Dispatch_>
  class GlushkovVisitor : 
    public GenericMatcher
  <
    GlushkovVisitor<Exp_, Auto_, Dispatch_>,
    Exp_,
    Auto_*,
    Dispatch_
    >      
  {
  public :
    typedef Auto_					automaton_t;
    typedef Auto_*					automaton_ptr_t;
    typedef typename automaton_t::series_t		series_t; 
    typedef typename automaton_t::series_elt_t		series_elt_t;
    typedef typename series_elt_t::weight_t		weight_t;
    typedef typename Exp_::monoid_value_t		monoid_value_t;
    typedef typename Exp_::weight_value_t		weight_value_t;
    typedef rat::Node<monoid_value_t, weight_value_t>   node_t;

    typedef GlushkovVisitor<Exp_, Auto_, Dispatch_>     this_class;
    typedef GenericMatcher<this_class, Exp_, Auto_*, Dispatch_> parent_class;
    typedef typename parent_class::return_type          return_type;

    DecBinaryOp(Product, Exp_, Exp_);
    DecBinaryOp(Sum, Exp_, Exp_);
    DecUnaryOp(Star, Exp_);
    DecBinaryOp(LeftWeight, weight_value_t, Exp_);
    DecBinaryOp(RightWeight, Exp_, weight_value_t);
    DecLeaf(Constant, monoid_value_t);
    DecFinalLeaf(Zero);
    DecFinalLeaf(One);

  public :

    GlushkovVisitor(const series_t& series) :
      series_(series)
    {}

    MATCH__(Product, lhs, rhs)
    {
      automaton_ptr_t tmp_  = match(rhs);
      automaton_ptr_t auto_ = match(lhs);
      standard_auto_in_concat(*auto_, *tmp_);
      delete (tmp_);
      return auto_;
    }
    END	
    
    MATCH__(Sum, lhs, rhs)
    {
      automaton_ptr_t tmp_  = match(rhs);
      automaton_ptr_t auto_ = match(lhs);
      standard_auto_in_union(*auto_, *tmp_);
      delete (tmp_);
      return auto_;
    }
    END

    MATCH_(Star, node)
    {
      automaton_ptr_t stared = match(node);
      standard_auto_in_star(*stared); 
      return stared;
    }
    END

    MATCH__(LeftWeight, w, node)
    {
      automaton_ptr_t auto_ = match(node);

      for (typename automaton_t::initial_iterator i = auto_->initial().begin();
	   i != auto_->initial().end();
	   ++i)
	auto_->set_initial(*i, weight_t(w) * auto_->get_initial(*i));
      return auto_;
    }
    END

    MATCH__(RightWeight, node, w)
    {
      automaton_ptr_t auto_ = match(node);

      for (typename automaton_t::initial_iterator i = auto_->initial().begin();
	   i != auto_->initial().end();
	   ++i)
	auto_->set_initial(*i, auto_->get_initial(*i) * weight_t(w));
      return auto_;
    }
    END

    MATCH_(Constant, m)
    {
      automaton_ptr_t auto_ = new automaton_t();
      auto_->create();
      auto_->series() = series_;
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
      return auto_;
    }
    END

    MATCH(Zero)
    {
      automaton_ptr_t auto_ = new automaton_t();
      auto_->create();
      auto_->series() = series_;
      return auto_;
    }
    END

    MATCH(One)
    {
      automaton_ptr_t auto_ = new automaton_t();
      auto_->create();
      auto_->series() = series_;
      hstate_t new_i = auto_->add_state();
      auto_->set_initial(new_i);
      auto_->set_final(new_i);
      return auto_;
    }
    END

  private:
    series_t series_;
  };

  template <typename A, 
	    typename Output,
	    typename Exp>
  void
  do_glushkov(const AutomataBase<A>&, 
	      Output& output, 
	      const Exp& kexp)
  {
    GlushkovVisitor<Exp, Output, DispatchFunction<Exp> > m(output.series()); 
    output = *m.match(kexp);
  }

  template<typename A,      
	   typename T, 
	   typename Exp>
  void
  glushkov(Element<A, T>& out, 
	   const Exp& kexp)
  {
    do_glushkov(out.set(), out, kexp);
  }
  
} // vcsn

#endif // VCSN_ALGORITHMS_GLUSHKOV_HXX
