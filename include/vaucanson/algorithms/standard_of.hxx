// determinize.hh: this file is part of the Vaucanson project.
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
#ifndef VCSN_ALGORITHM_STANDARD_OF_HXX
# define VCSN_ALGORITHM_STANDARD_OF_HXX

# include <string>
# include <stack>
# include <vaucanson/algorithms/standard_of.hh>
# include <vaucanson/misc/selectors.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algebra/concrete/series/rat/exp.hh>

namespace vcsn {

  // This is an improved version.
  // The automaton is created just once.
  // Moreover, this works also with multiplicities.

  template <class Auto_, class Monoid_, class Semiring_>
  class Standard_OfVisitor : 
    public rat::ConstNodeVisitor<Monoid_, Semiring_>
  {
  public :
    AUTOMATON_TYPES(Auto_);

    typedef Monoid_						monoid_value_t;
    typedef Semiring_						weight_value_t;
    typedef rat::Node<monoid_value_t, weight_value_t>           node_t;

  public :

    Standard_OfVisitor(const series_t& s) : series_(s) 
    {
      automata_set_t a_set(series_);
      auto_ = new automaton_t(a_set);
      top_initial = 0;
      top_final = 0;
      completed = false;

      w_0 = algebra::zero_as<weight_value_t>::of(series_.weights());
      w_1 = algebra::identity_as<weight_value_t>::of(series_.weights());
    }

    virtual
    ~Standard_OfVisitor()
    {}

    // Product
    virtual void 
    product(const node_t* lhs, const node_t* rhs) 
    {
      lhs->accept(*this);
      rhs->accept(*this);

      state_weight_pair_list_t& swpl = (*(final[top_final - 2]));
      for_each_(state_weight_pair_list_t, sw_p, swpl)
	{
	  hstate_t p = (*sw_p).first;
	  weight_t w = (*sw_p).second;
	  
	  state_serie_pair_list_t& sspl = (*(initial[top_initial - 1]));
	  for_each_(state_serie_pair_list_t, ss_p, sspl)
	    {
	      hstate_t q = (*ss_p).first;
	      series_elt_t s = (*ss_p).second;
	      s = w*s;
	      auto_->add_serie_edge(p, q, s);
	    }
	}

      weight_t r = w_stack.top(); // final() of lhs
      w_stack.pop();   
      weight_t l = w_stack.top(); // final() of rhs
      w_stack.pop();
      w_stack.push(l*r);

      if (l != w_0) // if final() of lhs != 0, we must add some edges
	{
	  state_serie_pair_list_t& sspl = (*(initial[top_initial - 1]));
	  for_each_(state_serie_pair_list_t, ss_p, sspl)
	    {
	      hstate_t q = (*ss_p).first;
	      series_elt_t s = (*ss_p).second;
	      s = l*s;
	      initial[top_initial - 2]->push_back(state_serie_pair_t(q, s));
	    }
	}

      if (r != w_0)
	{
	  state_weight_pair_list_t& swpl = (*(final[top_final - 2]));
	  for_each_(state_weight_pair_list_t, sw_p, swpl)
	    {
	      hstate_t q = (*sw_p).first;
	      weight_t w = (*sw_p).second;
	      w = w * r;
	      final[top_final - 1]->push_back(state_weight_pair_t(q, w));
	    }
	}
      state_weight_pair_list_t* to_delete = new state_weight_pair_list_t();
      to_delete = final[top_final - 2];
      final[top_final - 2] = final[top_final - 1];

      delete to_delete;
      delete initial[top_initial - 1];

      --top_initial;
      --top_final;
    }

    // Sum 
    virtual void 
    sum(const node_t* lhs, const node_t* rhs) 
    {
      lhs->accept(*this);
      rhs->accept(*this);

      state_serie_pair_list_t& sspl = (*(initial[top_initial - 1]));
      for_each_(state_serie_pair_list_t, ss_p, sspl)
	initial[top_initial - 2]->push_back(*ss_p);
      delete initial[top_initial - 1];

      state_weight_pair_list_t& swpl = (*(final[top_final - 1]));
      for_each_(state_weight_pair_list_t, sw_p, swpl)
	final[top_final - 2]->push_back(*sw_p);
      delete final[top_final - 1];

      --top_initial;
      --top_final;

      if (!w_stack.empty())
	{
	  weight_t l = w_stack.top();
	  w_stack.pop();
	  weight_t r = w_stack.top();
	  w_stack.pop();
	  w_stack.push(l + r);
	}      
    }
    
    // Star
    virtual void 
    star(const node_t* node)
    {
      node->accept(*this);
      assert(!w_stack.empty());
      weight_t k = w_stack.top();
      if (!k.starable())
	{
	  std::cerr<< "Star not defined." << std::endl;
	  return;
	}
      k.star();

      state_weight_pair_list_t& swpl = (*(final[top_final - 1]));
      for_each_(state_weight_pair_list_t, sw_p, swpl)
	{
	  hstate_t p = (*sw_p).first;
	  weight_t w = (*sw_p).second;
	  
	  state_serie_pair_list_t& sspl = (*(initial[top_initial - 1]));
	  for_each_(state_serie_pair_list_t, ss_p, sspl)
	    {
	      hstate_t q = (*ss_p).first;
	      series_elt_t s = (*ss_p).second;
	      s = w*k*s;
	      auto_->add_serie_edge(p, q, s);
	      (*ss_p).second = k*s; // Will it be ok ?
	    }
	  (*sw_p).second = w * k; // Will it be ok ?
	} 
      assert(!w_stack.empty());
      w_stack.pop();
      w_stack.push(k);      
    }

    // Left weight
    virtual void 
    left_weight(const weight_value_t& w, const node_t* node) 
    {
      node->accept(*this);
      if (w == w_1)
	return;
      if (!initial[top_initial - 1]->empty())
	{
	  state_serie_pair_list_t& sspl = (*(initial[top_initial - 1]));
	  for_each_(state_serie_pair_list_t, ss_p, sspl)
	    {
	      weight_t w_ = w;
	      (*ss_p).second = w_ * (*ss_p).second; // Will it be ok ? 
	    }
	}
      assert(!w_stack.empty());
      weight_t k = w_stack.top();
      w_stack.pop();
      w_stack.push(w * k);
    }
    
    // Right weight
    virtual void 
    right_weight(const weight_value_t& w, const node_t* node)
    {
      node->accept(*this);
      if (w == w_1)
	return;
      state_weight_pair_list_t& swpl = (*(final[top_final - 1]));
      for_each_(state_weight_pair_list_t, sw_p, swpl)
	(*sw_p).second =(*sw_p).second * w; // Will it be ok ? 
      assert(!w_stack.empty());
      weight_t k = w_stack.top();
      w_stack.pop();
      w_stack.push(k * w);
    }

    // Constant
    virtual void 
    constant(const monoid_value_t& m)
    {
      monoid_elt_t neutre = auto_->series().monoid().identity(SELECT(typename monoid_elt_t::value_t));
      if (top_initial == initial.size()) // we add a new element to the 'initial' vector
	initial.resize(top_initial + 1);
      if (top_final == final.size())
	final.resize(top_final + 1);
      initial[top_initial] = new state_serie_pair_list_t();
      final[top_final] = new state_weight_pair_list_t();

      if (m != neutre) // m != ""
	{
	  hstate_t from = auto_->add_state();
	  hstate_t from_const = from;
	  typename monoid_value_t::const_iterator i = m.begin();
	  letter_t a = *i; // if m is "abc", *i = 'a'
	  std::string str(1, a);
	  series_elt_t s;      
	  s.value_set(str, w_1.value()); 
	  initial[top_initial]->push_back(state_serie_pair_t(from_const, s));
	  while(++i != m.end())
	    {
	      hstate_t to = auto_->add_state();
	      auto_->add_letter_edge(from, to, *i);
	      from = to;
	    }
	  final[top_final]->push_back(state_weight_pair_t(from, w_1));
	}
      else // m == ""
	{
	  w_stack.push(w_1);
	  ++top_initial;
	  ++top_final;
	  return;
	}
      ++top_initial;
      ++top_final;

      w_stack.push(w_0);
    }

    virtual void 
    zero()
    {
      automata_set_t a_set(series_);
      auto_ = new automaton_t(a_set);
      completed = true;
    }
    
    virtual void 
    one()
    {
      automata_set_t a_set(series_);
      auto_ = new automaton_t(a_set);
      hstate_t new_i = auto_->add_state();
      //      hstate_t new_f = auto_->add_state();
      auto_->set_initial(new_i);
      auto_->set_final(new_i);
      //      auto_->add_spontaneous(new_i, new_f);
      completed = true;
    }
    
    const automaton_t		&get_auto() //const
    {
      if (completed)
	return *auto_; 

      hstate_t initial_state = auto_->add_state();
      auto_->set_initial(initial_state);
      if (w_stack.top() != w_0)
	auto_->set_final(initial_state, series_elt_t(w_stack.top()));
      state_weight_pair_list_t& swpl = (*(final[top_final - 1]));
      for_each_(state_weight_pair_list_t, sw_p, swpl)
	{
	  hstate_t p = (*sw_p).first;
	  weight_t w = (*sw_p).second;
	  auto_->set_final(p, series_elt_t(w));
	}
      state_serie_pair_list_t& sspl = (*(initial[top_initial - 1]));
      for_each_(state_serie_pair_list_t, ss_p, sspl)
	{
	  hstate_t q = (*ss_p).first;
	  series_elt_t s = (*ss_p).second;
	  auto_->add_serie_edge(initial_state, q, s);
	}
      completed = true;
      return *auto_;
    }
    
  private :
    automaton_t		*auto_;
    const series_t	&series_;
    
    //static const weight_t w_0, w_1 // why not ?
    weight_t  w_0, w_1;
    std::stack<weight_t>  w_stack; 
    // to contain intermediate weight value for calculating of weight_of_initial_state

    typedef std::pair<hstate_t, series_elt_t> state_serie_pair_t;
    typedef std::list<state_serie_pair_t> state_serie_pair_list_t;
    std::vector<state_serie_pair_list_t*> initial;

    typedef std::pair<hstate_t, weight_t> state_weight_pair_t;
    typedef std::list<state_weight_pair_t> state_weight_pair_list_t;
    std::vector<state_weight_pair_list_t*> final;

    unsigned top_initial, top_final; 
    bool completed;
  };

  //****************************************    
  template <typename A, typename auto_t,
	    typename Letter, typename Weight>
  void
  do_standard_of(const AutomataBase<A>&, 
		 auto_t& output, 
		 const rat::exp<Letter, Weight>& kexp)
  {
    Standard_OfVisitor<auto_t, Letter, Weight>	visitor(output.series());
      
    // FIXME : 
    // Static assert : Letter = monoid_elt_value_t, 
    //                 Weight = weight_value_t
    kexp.accept(visitor);
    output = visitor.get_auto();    
  }
  
  template<typename A,      typename T, 
	   typename Letter, typename Weight>
  void
  standard_of(Element<A, T>& out, 
	      const rat::exp<Letter, Weight>& kexp)
  {
    do_standard_of(out.set(), out, kexp);
  }
  
} // vcsn

#endif // VCSN_ALGORITHM_STANDARD_OF_HH
  
