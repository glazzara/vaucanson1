// depth_visitor.hxx
//
// $Id$
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2001-2002 Sakarovitch, Poss, Rey and Regis-Gianas.
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
    void 
    DepthVisitor<M_,W_>::product(const Node<M_, W_>* left_, 
				 const Node<M_, W_>* right_)
    { 
      sum_or_product(left_, right_); 
    }

    template<typename M_, typename W_>
    void 
    DepthVisitor<M_,W_>::sum(const Node<M_, W_>* left_, 
			     const Node<M_, W_>* right_)
    { 
      sum_or_product(left_, right_); 
    }

    template<typename M_, typename W_>
    void 
    DepthVisitor<M_,W_>::star(const Node<M_, W_>* node)
    { 
      weight_or_star(node); 
    }

    template<typename M_, typename W_>
    void 
    DepthVisitor<M_,W_>::left_weight(const W_& w, const Node<M_, W_>* node)
    { 
      weight_or_star(node); 	
    }

    template<typename M_, typename W_>
    void 
    DepthVisitor<M_,W_>::right_weight(const W_& w, const Node<M_, W_>* node)
    { 
      weight_or_star(node); 
    }

    template<typename M_, typename W_>
    void 
    DepthVisitor<M_,W_>::constant(const M_& m)
    { 
      d = 0; 
    }

    template<typename M_, typename W_>
    void DepthVisitor<M_,W_>::zero()
    { 
      d = 0; 
    }

    template<typename M_, typename W_>
    void DepthVisitor<M_,W_>::one()
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
