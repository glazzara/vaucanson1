// dump_visitor.hh
//
//
// $Id$
// VCSN_HEADER

#ifndef RAT_DUMP_VISITOR_HH
#define RAT_DUMP_VISITOR_HH


#include <vaucanson/algebra/concrete/series/nodes.hh>
#include <iostream>

namespace vcsn
{
  namespace rat
  {

    template<typename M_, typename W_>
    class DumpVisitor : public ConstNodeVisitor<M_, W_>
    {
    public:
      DumpVisitor(std::ostream& o,
		  const char *zero = "0",
		  const char *one = "1") 
	: o_(o),
	  z_(zero),
	  i_(one)
      {}

      virtual void 
      product(const Node<M_, W_>* left_, const Node<M_, W_>* right_)
      { 
	o_ << "(";
	left_->accept(*this);
	o_ << ".";
	right_->accept(*this);
	o_ << ")";
      }

      virtual void 
      sum(const Node<M_, W_>* left_, const Node<M_, W_>* right_)
      { 
	o_ << "(";
	left_->accept(*this);
	o_ << "+";
	right_->accept(*this);
	o_ << ")";
      }

      virtual void 
      star(const Node<M_, W_>* node)
      { 
	//	  o_ << "(";
	node->accept(*this);
	o_ << "*"; // << ")";
      }

      virtual void 
      left_weight(const W_& w, const Node<M_, W_>* node)
      { 
	o_ << "(" << w << " ";
	node->accept(*this);
	o_ << ")";
      }

      virtual void 
      right_weight(const W_& w, const Node<M_, W_>* node)
      { 
	o_ << "(";
	node->accept(*this);
	o_ << " " << w << ")";
      }

      virtual void 
      constant(const M_& m)
      { 
	o_ << m; 
      }

      virtual void zero()
      { 
	o_ << z_; 
      }

      virtual void one()
      { 
	o_ << i_; 
      }

    protected:
      std::ostream& o_;
      const char *z_;
      const char *i_;
    };
      



  }
}


#endif
