// nodes.hh
//
// $Id$
// VCSN_HEADER
#ifndef ALGEBRA_SERIES_CONCRETE_RAT_NODES_HH
# define ALGEBRA_SERIES_CONCRETE_RAT_NODES_HH

namespace vcsn {

  namespace rat {

    
    template<typename M_, typename W_>
    class Node;

    /*-----------------.
    | ConstNodeVisitor |
    `-----------------*/

    template<typename M_, typename W_>
    class ConstNodeVisitor
    {
    public:
      virtual ~ConstNodeVisitor() {}
      virtual void product(const Node<M_, W_>*, const Node<M_, W_>*) = 0;
      virtual void sum(const Node<M_, W_>*, const Node<M_, W_>*) = 0;
      virtual void star(const Node<M_, W_>*) = 0;
      virtual void left_weight(const W_&, const Node<M_, W_>*) = 0;
      virtual void right_weight(const W_&, const Node<M_, W_>*) = 0;
      virtual void constant(const M_&) = 0;
      virtual void zero() = 0;
      virtual void one() = 0;
    };

    template<typename M_, typename W_>
    class DefaultMutableNodeVisitor : public ConstNodeVisitor<M_, W_>
    {
    public:
      virtual void product( Node<M_, W_>* lhs,  Node<M_, W_>* rhs);
      virtual void sum( Node<M_, W_>* lhs,  Node<M_, W_>* rhs);
      virtual void star( Node<M_, W_>* n);
      virtual void left_weight( W_&,  Node<M_, W_>* n);
      virtual void right_weight( W_&,  Node<M_, W_>* n);
      virtual void constant( M_&);
      virtual void zero();
      virtual void one();
    };

    /*-----.
    | Node |
    `-----*/
    template<typename M_, typename W_>
    class Node
    {
    public:
      enum type 
	{ 	  	    
	  constant, 
	  lweight, 
	  rweight,
	  one,  
	  prod, 
	  star,
	  sum, 
	  zero
	};

      // Pure virtual methods
      virtual type		what() const = 0;
      virtual Node<M_, W_>*	clone() const = 0;
      virtual void		accept(ConstNodeVisitor<M_, W_> &) const = 0;
      virtual bool		operator!=(const Node<M_, W_>& other) const = 0;
      virtual bool		operator<(const Node<M_, W_>& other) const = 0;

      // Defined methods
      virtual			~Node();
      W_* &			c();
      W_ const * &		c() const;

      Node();

    /* protected */ public:
      const W_*		constant_term_;
    };


    /*-----.
    | Zero |
    `-----*/
    template<typename M_, typename W_>
    class Zero : public Node<M_, W_>
    {
    public:
      Zero();

      virtual Node<M_, W_>::type	
      what() const;
      virtual Node<M_, W_>*	
      clone() const;
      virtual void	       	
      accept(ConstNodeVisitor<M_, W_>& v) const;
      virtual bool		
      operator!=(const Node<M_, W_>& other) const;
      virtual bool		
      operator<(const Node<M_, W_>& other) const;
      virtual 
      ~Zero();
    };

    /*----.
    | One |
    `----*/
    template<typename M_, typename W_>
    class One : public Node<M_, W_>
    {
    public:
      One();
      virtual Node<M_, W_>::type 
      what() const;
      virtual Node<M_, W_>* 
      clone() const;
      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const;
      virtual bool 
      operator!=(const Node<M_, W_>& other) const;
      virtual bool 
      operator<(const Node<M_, W_>& other) const;
      virtual 
      ~One();
    };

    
    /*---------.
    | Constant |
    `---------*/
    template<typename M_, typename W_>
    class Constant : public Node<M_, W_>
    {
    public:
      Constant(const M_ &v);
      virtual Node<M_, W_>::type     what() const; 
      virtual Node<M_, W_>*          clone() const;
      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const;
      virtual bool 
      operator!=(const Node<M_, W_>& other) const;
      virtual bool 
      operator<(const Node<M_, W_>& other) const;
      virtual 
      ~Constant();

    /* protected */ public:
      M_	value_;
    };

    /*-------------.
    | LeftWeighted |
    `-------------*/
    template<typename M_, typename W_>
    class LeftWeighted : public Node<M_, W_>
    {

    public:
	
      LeftWeighted(const W_& w, const Node<M_, W_>& c);
      LeftWeighted(const W_& w, Node<M_, W_>* c);
      LeftWeighted(const W_& w);
      virtual Node<M_, W_>::type 
      what() const;
      virtual Node<M_, W_>* 
      clone() const;
      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const;
      virtual bool 
      operator!=(const Node<M_, W_>& other) const;
      virtual bool 
      operator<(const Node<M_, W_>& other) const;
      virtual 
      ~LeftWeighted();

    /* protected */ public:
      W_		weight_;
      Node<M_, W_>*	child_;
    };

    /*--------------.
    | RightWeighted |
    `--------------*/
    template<typename M_, typename W_>
    class RightWeighted : public Node<M_, W_>
    {
    public:
	
      RightWeighted(const W_& w, const Node<M_, W_>& c);
      RightWeighted(const W_& w, Node<M_, W_>* c);
      RightWeighted(const W_& w);
      virtual Node<M_, W_>::type 
      what() const; 
      virtual Node<M_, W_>* 
      clone() const;
      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const;
      virtual bool 
      operator!=(const Node<M_, W_>& other) const;
      virtual bool 
      operator<(const Node<M_, W_>& other) const;
      virtual 
      ~RightWeighted();
    /* protected */ public:

      W_		weight_;
      Node<M_, W_>*	child_;
    };

    /*-----.
    | Star |
    `-----*/
    template<typename M_, typename W_>
    class Star : public Node<M_, W_>
    {

    public:

      Star(const Node<M_, W_>& other);
      Star(Node<M_, W_>* other);
      virtual Node<M_, W_>::type 
      what() const;
      virtual Node<M_, W_>* 
      clone() const;
      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const;
      virtual bool 
      operator!=(const Node<M_, W_>& other) const;
      virtual bool 
      operator<(const Node<M_, W_>& other) const;
      virtual 
      ~Star();

    /* protected */ public:
	
      Node<M_, W_>*		child_;
    };

    /*--------.
    | Product |
    `--------*/
    template<typename M_, typename W_>
    class Product : public Node<M_, W_>
    { 

    public:

      Product(const Node<M_, W_>& left, const Node<M_, W_>& right);
      Product(Node<M_, W_>* left, Node<M_, W_>* right);
      virtual Node<M_, W_>::type 
      what() const;
      virtual Node<M_, W_>* 
      clone() const;
      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const;
      virtual bool 
      operator!=(const Node<M_, W_>& other) const;
      virtual bool 
      operator<(const Node<M_, W_>& other) const;
      virtual 
      ~Product();

    /* protected */ public:
	
      Node<M_, W_>*		left_;
      Node<M_, W_>*		right_;
    };

    /*----.
    | Sum |
    `----*/
    template<typename M_, typename W_>
    class Sum : public Node<M_, W_>
    { 
    public:
      Sum(const Node<M_, W_>& left, const Node<M_, W_>& right);
      Sum(Node<M_, W_>* left, Node<M_, W_>* right);
      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const;
      virtual Node<M_, W_>::type 
      what() const;
      virtual Node<M_, W_>* 
      clone() const;
      virtual bool 
      operator!=(const Node<M_, W_>& other) const;
      virtual bool 
      operator<(const Node<M_, W_>& other) const;
      virtual 
      ~Sum();
    /* protected */ public:

      Node<M_, W_>		*left_;
      Node<M_, W_>		*right_;
    };

  } // rat

} // vcsn

# include <vaucanson/algebra/concrete/series/rat/nodes.hxx>

#endif // ALGEBRA_SERIES_CONCRETE_RAT_NODES_HH
