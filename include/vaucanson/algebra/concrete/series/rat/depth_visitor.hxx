// depth_visitor.hxx
//
// $Id$
// VCSN_HEADER
#ifndef RAT_DEPTH_VISITOR_HXX
# define RAT_DEPTH_VISITOR_HXX

# include <algorithm>
# include <vaucanson/algebra/concrete/series/rat/depth_visitor.hh>
# include <vaucanson/algebra/concrete/series/rat/nodes.hh>

namespace vcsn {
  
  namespace rat {
    
    template<typename M_, typename W_>
    void 
    DepthVisitor<M_,W_>::sum_or_product(const Node<M_, W_>* left_, 
					const Node<M_, W_>* right_)
    { 
      left_->accept(*this);
      size_t left_depth = d;
      right_->accept(*this);
      d = 1 + std::max(left_depth, d);
    }

    template<typename M_, typename W_>
    void 
    DepthVisitor<M_,W_>::weight_or_star(const Node<M_, W_>* node)
    {
      node->accept(*this);
      ++d;
    }
    
    template<typename M_, typename W_>
    virtual void 
    DepthVisitor<M_,W_>::product(const Node<M_, W_>* left_, 
				 const Node<M_, W_>* right_)
    { 
      sum_or_product(left_, right_); 
    }

    template<typename M_, typename W_>
    virtual void 
    DepthVisitor<M_,W_>::sum(const Node<M_, W_>* left_, 
			     const Node<M_, W_>* right_)
    { 
      sum_or_product(left_, right_); 
    }

    template<typename M_, typename W_>
    virtual void 
    DepthVisitor<M_,W_>::star(const Node<M_, W_>* node)
    { 
      weight_or_star(node); 
    }

    template<typename M_, typename W_>
    virtual void 
    DepthVisitor<M_,W_>::left_weight(const W_& w, const Node<M_, W_>* node)
    { 
      weight_or_star(node); 	
    }

    template<typename M_, typename W_>
    virtual void 
    DepthVisitor<M_,W_>::right_weight(const W_& w, const Node<M_, W_>* node)
    { 
      weight_or_star(node); 
    }

    template<typename M_, typename W_>
    virtual void 
    DepthVisitor<M_,W_>::constant(const M_& m)
    { 
      d = 0; 
    }

    template<typename M_, typename W_>
    virtual void DepthVisitor<M_,W_>::zero()
    { 
      d = 0; 
    }

    template<typename M_, typename W_>
    virtual void DepthVisitor<M_,W_>::one()
    { 
      d = 0; 
    }

    template<typename M_, typename W_>
    size_t DepthVisitor<M_,W_>::get() const 
    { 
      return d; 
    } 

  } // rat

} // vcsn

#endif // RAT_DEPTH_VISITOR_HXX
