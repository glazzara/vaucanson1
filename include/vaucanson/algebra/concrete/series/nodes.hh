/****************************
 * <vaucanson/rat/nodes.hh> *
 ****************************/
// $Id$

/* this file is part of the Vaucanson project */
#ifndef RAT_NODES_HH
#define RAT_NODES_HH

namespace vcsn
{
  namespace rat
  {

      
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
      virtual void product( Node<M_, W_>* lhs,  Node<M_, W_>* rhs)
      {
	lhs->accept(*this);
	rhs->accept(*this);
      }

      virtual void sum( Node<M_, W_>* lhs,  Node<M_, W_>* rhs)
      {
	lhs->accept(*this);
	rhs->accept(*this);
      }

      virtual void star( Node<M_, W_>* n)
      {
	n->accept(*this);
      }

      virtual void left_weight( W_&,  Node<M_, W_>* n)
      {
	n->accept(*this);
      }

      virtual void right_weight( W_&,  Node<M_, W_>* n)
      {
	n->accept(*this);
      }

      virtual void constant( M_&)
      {}

      virtual void zero()
      {}

      virtual void one()
      {}
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
      virtual			~Node() 
      {
	delete constant_term_;
      }

      W_* &		c() { return constant_term_; }
      W_ const * &    c() const { return constant_term_; }

      Node()
	: constant_term_(0)
      {}

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
      Zero() {}

      virtual Node<M_, W_>::type	
      what() const 
      { 
	return Node<M_, W_>::zero; 
      }

      virtual Node<M_, W_>*	
      clone() const 
      { 
	Node<M_, W_>* p = new Zero<M_, W_>; 
	if (constant_term_)
	  p->constant_term_ = new W_(*constant_term_);
	return p;
      }

      virtual void	       	
      accept(ConstNodeVisitor<M_, W_>& v) const
      { 
	v.zero(); 
      }

      virtual bool		
      operator!=(const Node<M_, W_>& other) const
      { 
	return (dynamic_cast<const Zero<M_, W_>*>(&other) == 0); 
      }

      virtual bool		
      operator<(const Node<M_, W_>& other) const
      { 
	return (dynamic_cast<const Zero<M_, W_>*>(&other) == 0); 
      }

      virtual 
      ~Zero() 
      {}
    };

    /*----.
      | One |
      `----*/
    template<typename M_, typename W_>
    class One : public Node<M_, W_>
    {
    public:
      One() 
      {}

      virtual Node<M_, W_>::type 
      what() const 
      { 
	return Node<M_, W_>::one; 
      }

      virtual Node<M_, W_>* 
      clone() const 
      { 
	Node<M_, W_>* p = new One<M_, W_>; 
	if (constant_term_)
	  p->constant_term_ = new W_(*constant_term_);
	return p;
      }

      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const
      { 
	v.one(); 
      }

      virtual bool 
      operator!=(const Node<M_, W_>& other) const
      { 
	return (dynamic_cast<const One<M_, W_>*>(&other) == 0); 
      }

      virtual bool 
      operator<(const Node<M_, W_>& other) const
      { 
	return (dynamic_cast<const One<M_, W_>*>(&other) == 0);
      }

      virtual 
      ~One() 
      {}
    };

    
    /*---------.
      | Constant |
      `---------*/
    template<typename M_, typename W_>
    class Constant : public Node<M_, W_>
    {
    public:
      Constant(const M_ &v) : value_(v) 
      {}

      virtual Node<M_, W_>::type 
      what() const 
      { 
	return Node<M_, W_>::constant; 
      }

      virtual Node<M_, W_>* 
      clone() const 
      { 
	Node<M_, W_>* p = new Constant<M_, W_>(value_); 
	if (constant_term_)
	  p->constant_term_ = new W_(*constant_term_);
	return p;
      }

      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const
      { 
	v.constant(value_); 
      }

      virtual bool 
      operator!=(const Node<M_, W_>& other) const
      { 
	const Constant<M_, W_>* otherp =
	  dynamic_cast<const Constant<M_, W_>*>(&other);
	if(!otherp)
	  return true;
	return (value_ != otherp->value_);
      }

      virtual bool 
      operator<(const Node<M_, W_>& other) const
      { 
	const Constant<M_, W_>* otherp =
	  dynamic_cast<const Constant<M_, W_>*>(&other);
	if(!otherp)
	  return true;
	return (value_ < otherp->value_);
      }

      virtual 
      ~Constant() 
      {};

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
	
      LeftWeighted(const W_& w, const Node<M_, W_>& c)
	: weight_(w), child_(c.clone())
      { }

      LeftWeighted(const W_& w, Node<M_, W_>* c)
	: weight_(w), child_(c)
      { }

      LeftWeighted(const W_& w)
	: weight_(w), 
	  child_(new One<M_, W_>)
      { }


      virtual Node<M_, W_>::type 
      what() const 
      { 
	return Node<M_, W_>::lweight; 
      }

      virtual Node<M_, W_>* 
      clone() const 
      { 
	Node<M_, W_>* p = new LeftWeighted<M_, W_>(weight_, *child_); 
	if (constant_term_)
	  p->constant_term_ = new W_(*constant_term_);
	return p;
      }

      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const
      { 
	v.left_weight(weight_, child_); 
      }

      virtual bool 
      operator!=(const Node<M_, W_>& other) const
      { 
	const LeftWeighted<M_, W_>* otherp =
	  dynamic_cast<const LeftWeighted<M_, W_>*>(&other);
	if(!otherp || (weight_ != otherp->weight_))
	  return true;
	return (*child_ != *otherp->child_);
      }

      virtual bool 
      operator<(const Node<M_, W_>& other) const
      { 
	const LeftWeighted<M_, W_>* otherp =
	  dynamic_cast<const LeftWeighted<M_, W_>*>(&other);
	if(!otherp || (weight_ != otherp->weight_))
	  return true;
	return (*child_ < *otherp->child_);
      }

      virtual 
      ~LeftWeighted() 
      { 
	delete child_; 
      }

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
	
      RightWeighted(const W_& w, const Node<M_, W_>& c)
	: weight_(w), child_(c.clone())
      { }

      RightWeighted(const W_& w, Node<M_, W_>* c)
	: weight_(w), child_(c)
      { }


      RightWeighted(const W_& w)
	: weight_(w), 
	  child_(new One<M_, W_>)
      { }

      virtual Node<M_, W_>::type 
      what() const 
      { 
	return Node<M_, W_>::rweight; 
      }

      virtual Node<M_, W_>* 
      clone() const 
      { 
	Node<M_, W_>* p = new RightWeighted<M_, W_>(weight_, *child_); 
	if (constant_term_)
	  p->constant_term_ = new W_(*constant_term_);
	return p;
      }

      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const
      { 
	v.right_weight(weight_, child_); 
      }

      virtual bool 
      operator!=(const Node<M_, W_>& other) const
      { 
	const RightWeighted<M_, W_>* otherp =
	  dynamic_cast<const RightWeighted<M_, W_>*>(&other);
	if(!otherp || (weight_ != otherp->weight_))
	  return true;
	return (*child_ != *otherp->child_);
      }

      virtual bool 
      operator<(const Node<M_, W_>& other) const
      { 
	const RightWeighted<M_, W_>* otherp =
	  dynamic_cast<const RightWeighted<M_, W_>*>(&other);
	if(!otherp || (weight_ != otherp->weight_))
	  return true;
	return (*child_ < *otherp->child_);
      }

      virtual 
      ~RightWeighted() 
      { 
	delete child_; 
      }

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

      Star(const Node<M_, W_>& other)
	: child_(other.clone())
      { }

      Star(Node<M_, W_>* other)
	: child_(other)
      { }

      virtual Node<M_, W_>::type 
      what() const 
      { 
	return Node<M_, W_>::star; 
      }

      virtual Node<M_, W_>* 
      clone() const
      { 
	Node<M_, W_>* p = new Star<M_, W_>(*child_); 
	if (constant_term_)
	  p->constant_term_ = new W_(*constant_term_);
	return p;
      }

      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const
      { 
	v.star(child_); 
      }

      virtual bool 
      operator!=(const Node<M_, W_>& other) const
      { 
	const Star<M_, W_>* otherp =
	  dynamic_cast<const Star<M_, W_>*>(&other);
	if(!otherp)
	  return true;
	return (*child_ != *otherp->child_);
      }

      virtual bool 
      operator<(const Node<M_, W_>& other) const
      { 
	const Star<M_, W_>* otherp =
	  dynamic_cast<const Star<M_, W_>*>(&other);
	if(!otherp)
	  return true;
	return (*child_ < *otherp->child_);
      }

      virtual 
      ~Star() 
      { 
	delete child_; 
      }

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

      Product(const Node<M_, W_>& left, const Node<M_, W_>& right)
	: left_(left.clone()), right_(right.clone())
      { }

      Product(Node<M_, W_>* left, Node<M_, W_>* right)
	: left_(left), right_(right)
      { }
	  
      virtual Node<M_, W_>::type 
      what() const 
      { 
	return Node<M_, W_>::prod; 
      }

      virtual Node<M_, W_>* 
      clone() const
      { 
	Node<M_, W_>* p = new Product<M_, W_>(*left_, *right_);  
	if (constant_term_)
	  p->constant_term_ = new W_(*constant_term_);
	return p;
      }

      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const
      { 
	return v.product(left_, right_); 
      }

      virtual bool 
      operator!=(const Node<M_, W_>& other) const
      { 
	const Product<M_, W_>* otherp =
	  dynamic_cast<const Product<M_, W_>*>(&other);
	if(!otherp || (*left_ != *otherp->left_))
	  return true;
	return (*right_ != *otherp->right_);
      }

      virtual bool 
      operator<(const Node<M_, W_>& other) const
      { 
	const Product<M_, W_>* otherp =
	  dynamic_cast<const Product<M_, W_>*>(&other);
	if(!otherp || (*left_ < *otherp->left_))
	  return true;
	return (*right_ < *otherp->right_);
      }

      virtual 
      ~Product() 
      { 
	delete right_; 
	delete left_; 
      }

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
      Sum(const Node<M_, W_>& left, const Node<M_, W_>& right)
	: left_(left.clone()), right_(right.clone())
      { }
	
      Sum(Node<M_, W_>* left, Node<M_, W_>* right)
	: left_(left), right_(right)
      { }
  
      virtual void 
      accept(ConstNodeVisitor<M_, W_>& v) const
      { 
	return v.sum(left_, right_); 
      }

      virtual Node<M_, W_>::type 
      what() const 
      { 
	return Node<M_, W_>::sum; 
      }

      virtual Node<M_, W_>* 
      clone() const
      { 
	Node<M_, W_>* p = new Sum<M_, W_>(*left_, *right_); 
	if (constant_term_)
	  p->constant_term_ = new W_(*constant_term_);
	return p;
      }

      virtual bool 
      operator!=(const Node<M_, W_>& other) const
      { 
	const Sum<M_, W_>* otherp =
	  dynamic_cast<const Sum<M_, W_>*>(&other);
	if(!otherp)
	  return true;
	// X + Y and Y + X are equal
	return ((*left_ != *otherp->left_) || (*right_ != *otherp->right_))
	  && ((*left_ != *otherp->right_) || (*right_ != *otherp->left_));
      }

      virtual bool 
      operator<(const Node<M_, W_>& other) const
      { 
	const Sum<M_, W_>* otherp =
	  dynamic_cast<const Sum<M_, W_>*>(&other);
	if(!otherp)
	  return true;
	// X + Y and Y + X are equal
	return ((*left_ < *otherp->left_) || (*right_ < *otherp->right_))
	  && ((*left_ < *otherp->right_) || (*right_ < *otherp->left_));
      }

      virtual 
      ~Sum() 
      { 
	delete right_; 
	delete left_; 
      }

    /* protected */ public:

      Node<M_, W_>		*left_;
      Node<M_, W_>		*right_;
    };
  }
}



#endif
