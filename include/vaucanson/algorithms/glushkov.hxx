// glushkov.hxx
//
// $Id$
// VCSN_HEADER
#ifndef VCSN_ALGORITHM_GLUSHKOV_HXX
# define VCSN_ALGORITHM_GLUSHKOV_HXX

# include <set>
# include <vaucanson/algorithms/glushkov.hh>
# include <vaucanson/automata/concept/automata_base.hh>
# include <vaucanson/algorithms/standard.hh>
# include <vaucanson/algebra/concrete/series/rat/exp.hh>

namespace vcsn {

  /*----------------.
  | GlushkovVisitor |
  `----------------*/
  // FIXME : Non optimal version.
  //         There are too much construction of automaton.
  // FIXME : this implementation is not generic at all and needs a generic
  // visitor pattern for all kexp. (now, it is only adaptable to rat::exp).
  // FIXME : from now, it is only working over LetterAutomaton

  template <class Auto_, class Monoid_, class Semiring_>
  class GlushkovVisitor : 
    public rat::ConstNodeVisitor<Monoid_, Semiring_>
  {
  public :
    typedef Auto_						automaton_t;
    typedef typename automaton_t::series_t			series_t; 
    typedef typename automaton_t::series_elt_t			series_elt_t;
    typedef typename series_elt_t::weight_t			weight_t;
    typedef Monoid_						monoid_value_t;
    typedef Semiring_						weight_value_t;
    typedef rat::Node<monoid_value_t, weight_value_t>           node_t;

  public :

    GlushkovVisitor(const series_t& s) : series_(s)
    {}

    virtual
    ~GlushkovVisitor()
    {}

    virtual void 
    product(const node_t* lhs, const node_t* rhs) 
    {
      automaton_t	*tmp_;
      rhs->accept(*this);
      tmp_ = auto_;
      lhs->accept(*this);
      standard_auto_in_concat(*auto_, *tmp_);
      delete(tmp_);
    }

    virtual void 
    sum(const node_t* lhs, const node_t* rhs) 
    {
      automaton_t	*tmp_;
      lhs->accept(*this);
      tmp_ = auto_;
      rhs->accept(*this);
      standard_auto_in_union(*auto_, *tmp_);
    }

    virtual void 
    star(const node_t* node)
    {
      node->accept(*this);
      standard_auto_in_star(*auto_);
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
      auto_ = new automaton_t();
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
    }

    virtual void 
    zero()
    {
      auto_ = new automaton_t();
      auto_->create();
      auto_->series() = series_;
    }

    virtual void 
    one()
    {
      auto_ = new automaton_t();
      auto_->create();
      auto_->series() = series_;
      hstate_t new_i = auto_->add_state();
      auto_->set_initial(new_i);
      auto_->set_final(new_i);
    }

    const automaton_t		&get_auto() const
    {
      return *auto_;
    }
    
  private :
    automaton_t		*auto_;
    series_t		series_;
  };

  template <typename A, typename auto_t,
	    typename Letter, typename Weight>
  void
  do_glushkov(const AutomataBase<A>& a_set, 
	      auto_t& output, 
	      const rat::exp<Letter, Weight>& kexp)
  {
    GlushkovVisitor<auto_t, Letter, Weight>	visitor(output.series());
   
    // FIXME : 
    // Static assert : Letter = monoid_elt_value_t, 
    //                 Weight = weight_value_t
 
    kexp.accept(visitor);
    output = visitor.get_auto();    
  }

  template<typename A,      typename T, 
	   typename Letter, typename Weight>
  void
  glushkov(Element<A, T>& out, 
	   const rat::exp<Letter, Weight>& kexp)
  {
    do_glushkov(out.set(), out, kexp);
  }
  
} // vcsn

#endif // VCSN_ALGORITHM_GLUSHKOV_HH
