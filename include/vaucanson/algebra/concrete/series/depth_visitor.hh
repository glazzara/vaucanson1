// depth_visitor.hh
//
//
// $Id$
// VCSN_HEADER

#ifndef RAT_DEPTH_VISITOR_HH
#define RAT_DEPTH_VISITOR_HH


#include <vaucanson/algebra/concrete/series/nodes.hh>
#include <algorithm>

namespace vcsn
{
  namespace rat
  {

    template<typename M_, typename W_>
    class DepthVisitor : public ConstNodeVisitor<M_, W_>
    {
    protected:
      void 
      sum_or_product(const Node<M_, W_>* left_, const Node<M_, W_>* right_)
      { 
	left_->accept(*this);
	size_t left_depth = d;
	right_->accept(*this);
	d = 1 + std::max(left_depth, d);
      }

      void 
      weight_or_star(const Node<M_, W_>* node)
      {
	node->accept(*this);
	++d;
      }

    public:
      virtual void 
      product(const Node<M_, W_>* left_, const Node<M_, W_>* right_)
      { 
	sum_or_product(left_, right_); 
      }

      virtual void 
      sum(const Node<M_, W_>* left_, const Node<M_, W_>* right_)
      { 
	sum_or_product(left_, right_); 
      }

      virtual void 
      star(const Node<M_, W_>* node)
      { 
	weight_or_star(node); 
      }

      virtual void 
      left_weight(const W_& w, const Node<M_, W_>* node)
      { 
	weight_or_star(node); 	
      }

      virtual void 
      right_weight(const W_& w, const Node<M_, W_>* node)
      { 
	weight_or_star(node); 
      }

      virtual void 
      constant(const M_& m)
      { 
	d = 0; 
      }

      virtual void zero()
      { 
	d = 0; 
      }

      virtual void one()
      { 
	d = 0; 
      }

      size_t get() const 
      { 
	return d; 
      } 

    protected:
      size_t		d;
    };

  }
}


#endif
