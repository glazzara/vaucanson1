// krat_exp_print.hxx

#ifndef VCSN_ALGORITHMS_KRAT_EXP_PRINT_HXX
# define VCSN_ALGORITHMS_KRAT_EXP_PRINT_HXX

# include <vaucanson/algorithms/krat_exp_print.hh>
# include <vaucanson/algebra/implementation/series/rat/exp.hh>

namespace vcsn {
  
  enum node_types{
    NODE_CONSTANT, 
    NODE_LWEIGHT, 
    NODE_RWEIGHT,
    NODE_ONE,  
    NODE_PROD, 
    NODE_STAR,
    NODE_SUM, 
    NODE_ZERO
  };

  enum print_modes{ 
    MODE_NONE, //  a+b+c, a.b.c 
    MODE_ADD,  //  (a+b)+c
    MODE_MUL,  //  (a.b).c
    MODE_ALL   //  (a+b)+c, (a.b).c
  };

  /*---------------.
  | PrintVisitor   |
  `----------------*/
  template <class Monoid_, class Semiring_>
  class PrintVisitor : 
    public rat::ConstNodeVisitor<Monoid_, Semiring_>
  {
  public :

    typedef Monoid_						monoid_value_t;
    typedef Semiring_						weight_value_t;
    typedef rat::Node<monoid_value_t, weight_value_t>           node_t;
    typedef unsigned print_mode_t;

  public :

    PrintVisitor(const print_mode_t& pm = 0, const char* zero = "0", const char* one = "1") 
      : print_mode_(pm), z_(zero), i_(one)
    {
    }

    virtual
    ~PrintVisitor()
    {
      cout << endl; // flush
    }

    // PRODUCT
    virtual void 
    product(const node_t* lhs, const node_t* rhs) 
    {      
      unsigned node_type_lhs = lhs->what();
      unsigned node_type_rhs = rhs->what();
      switch(node_type_lhs)
	{
	case NODE_SUM:
	  cout << "(";
	  lhs->accept(*this);
	  cout << ")";
	  break;
	case NODE_PROD:
	  if ((print_mode_ == MODE_NONE)||(print_mode_ == MODE_ADD))
	    lhs->accept(*this);
	  else
	    {
	      cout << "(";
	      lhs->accept(*this);
	      cout << ")";
	    }
	  break;
	default: 
	  lhs->accept(*this);
	  break;
	}

      cout << ".";

      switch(node_type_rhs)
	{
	case NODE_SUM:
	  cout << "(";
	  rhs->accept(*this);
	  cout << ")";
	  break;
	case NODE_PROD:
	  if ((print_mode_ == MODE_NONE)||(print_mode_ == MODE_ADD))
	    rhs->accept(*this);
	  else
	    {
	      cout << "(";
	      rhs->accept(*this);
	      cout << ")";
	    }
	  break;
	default: 
	  rhs->accept(*this);
	  break;
	}
    }

    // SUM
    virtual void 
    sum(const node_t* lhs, const node_t* rhs) 
    {
      unsigned node_type_lhs = lhs->what();
      unsigned node_type_rhs = rhs->what();
      if ((node_type_lhs != NODE_SUM) || (print_mode_ == MODE_NONE) || (print_mode_ == MODE_MUL))
	{
	  lhs->accept(*this);
	}
      else
	{
	  cout << "(";
	  lhs->accept(*this);
	  cout << ")";
	}      
    
      cout << " + ";
      
      if ((node_type_rhs != NODE_SUM) || (print_mode_ == MODE_NONE) || (print_mode_ == MODE_MUL))
	{
	  rhs->accept(*this);
	}
      else
	{
	  cout << "(";
	  rhs->accept(*this);
	  cout << ")";
	}
    }
    
    virtual void 
    star(const node_t* node)
    {
      cout << "(";
      node->accept(*this);
      cout << ")*";
    }

    virtual void 
    left_weight(const weight_value_t& w, const node_t* node) 
    {
      cout << w;
      node->accept(*this);
    }
    
    virtual void 
    right_weight(const weight_value_t& w, const node_t* node)
    {
      node->accept(*this);
      cout << w;
    }

    virtual void 
    constant(const monoid_value_t& m)
    {
      cout << m;
    }
      
    virtual void 
    zero()
    {
      cout << z_;
    }
    
    virtual void 
    one()
    {
      cout << i_;
    }
    
  private :
    print_mode_t print_mode_;

    const char* z_;
    const char* i_;
  };
  
  /************************************************************/
  
  template<typename Letter, typename Weight>
  void
  krat_exp_print(const rat::exp<Letter, Weight>& kexp, const unsigned& mode = 0)
  {
    PrintVisitor<Letter, Weight> p(mode); 
    kexp.accept(p);                       
    return;
  }
} // vcsn
  
#endif // VCSN_ALGORITHMS_KRAT_EXP_PRINT_HXX
  
